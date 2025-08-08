//
//  HNBaseBridge.m
//  JSBridge
//
//  Created by hong on 2022/4/24.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import "HWBaseJavaScriptBridge.h"
#import "NSString+HWJavaScriptProcess.h"
#import "JSBridgeJSCode.h"

@implementation HWBaseJavaScriptBridge{
    long _uniqueId; // 自增唯一的客户端调用JS回调的id
}

- (instancetype)init{
    if (self = [super init]) {
        self.messageHandlers = [NSMutableDictionary dictionary];
        self.responseCallbacks = [NSMutableDictionary dictionary];
    }
    return self;
}

#pragma mark - public
- (void)registerHandler:(NSString *)handlerName handler:(__nullable HNJBHandler)handler{
    self.messageHandlers[handlerName] = [handler copy];
}

- (void)callHandler:(NSString *)handlerName data:(id)data responseCallback:(HWJBResponseCallback)responseCallback{
    [self sendData:data responseCallback:responseCallback handlerName:handlerName];
}

- (void)sendData:(id)data responseCallback:(HWJBResponseCallback)responseCallback handlerName:(NSString*)handlerName {
    NSMutableDictionary* message = [NSMutableDictionary dictionary];
    if (data) {
        message[@"data"] = data;
    }
    if (responseCallback) {
        NSString* callbackId = [NSString stringWithFormat:@"objc_cb_%ld", ++_uniqueId];
        self.responseCallbacks[callbackId] = [responseCallback copy];
        message[@"callbackId"] = callbackId;
    }
    if (handlerName) {
        message[@"handlerName"] = handlerName;
    }
    [self dispatchMessage:message];
}

- (void)dispatchMessage:(HNJBMessage*)message {
    NSString *messageJSON = [self serializeMessage:message pretty:NO];
    [self log:@"SEND" json:messageJSON];
    
    // 处理JavaScript的json消息的编码问题
    messageJSON = [messageJSON processStringFromJavaScript];

    NSString* javascriptCommand = [NSString stringWithFormat:@"HoneJSCoreJSBridge.handleHoneMessageFromNative('%@');", messageJSON];
    
    if ([[NSThread currentThread] isMainThread]) {
        [self evaluateJavascript:javascriptCommand];
    } else {
        dispatch_sync(dispatch_get_main_queue(), ^{
            [self evaluateJavascript:javascriptCommand];
        });
    }
}

- (void)handleHoneMessageFromJS:(NSString *)message {
    NSDictionary *messageDic = [self deserializeMessageJSON:message];
    NSString* responseId = messageDic[@"responseId"];
    if (responseId) {
        HWJBResponseCallback responseCallback = self.responseCallbacks[responseId];
        responseCallback(messageDic[@"responseData"]);
        [self.responseCallbacks removeObjectForKey:responseId];
    }else{
        HWJBResponseCallback responseCallback = NULL;
        NSString* callbackId = messageDic[@"callbackId"];
        if (callbackId) {
            responseCallback = ^(id responseData) {
                if (responseData == nil) {
                    responseData = [NSNull null];
                }
                HNJBMessage* msg = @{ @"responseId":callbackId, @"responseData":responseData };
                [self dispatchMessage:msg];
            };
        } else {
            responseCallback = ^(id ignoreResponseData) {
                // Do nothing
            };
        }
        HNJBHandler handler = self.messageHandlers[messageDic[@"handlerName"]];
        if (!handler) {
            NSLog(@"HNJBNoHandlerException, No handler for message from JS: %@", message);
            return;
        }
        handler(messageDic[@"data"], responseCallback);
    }
}

- (void)evaluateJavascript:(NSString *)javascriptCommand {
    
}

- (void)log:(NSString *)action json:(id)json {
//    NSLog(@"[☕️ Native] %@: %@", action, json);
}

#pragma mark - private
/// JavaScriptBridge的代码
- (NSString*)javaScriptBridge {
    return honeJSBridgeJS();
}

- (NSString *)serializeMessage:(id)message pretty:(BOOL)pretty{
    return [[NSString alloc] initWithData:[NSJSONSerialization dataWithJSONObject:message options:(NSJSONWritingOptions)(pretty ? NSJSONWritingPrettyPrinted : 0) error:nil] encoding:NSUTF8StringEncoding];
}

- (NSDictionary *)deserializeMessageJSON:(NSString *)messageJSON {
    return [NSJSONSerialization JSONObjectWithData:[messageJSON dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingAllowFragments error:nil];
}

- (void)dealloc{
    NSLog(@"Bridge正常释放");
}

@end
