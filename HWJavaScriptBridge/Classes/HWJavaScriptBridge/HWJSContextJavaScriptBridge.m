//
//  HNJavaScriptBridgeBase.m
//  JSBridge
//
//  Created hong on 2022/4/20.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import "HWJSContextJavaScriptBridge.h"

@implementation HWJSContextJavaScriptBridge

- (instancetype)initWithJSContext:(JSContext *)jsContext{
    if (self = [super init]) {
        [self setUpWithJSContext:jsContext];
        self.messageHandlers = [NSMutableDictionary dictionary];
        self.responseCallbacks = [NSMutableDictionary dictionary];
    }
    return self;
}

- (void)setUpWithJSContext:(JSContext *)ctx{
    self.ctx = ctx;
    __weak __typeof(self)weakSelf = self;
    ctx[@"handleHoneMessageFromJS"] = ^(NSString *s){
        [weakSelf log:@"RECIEVE" json:s];
        [weakSelf handleHoneMessageFromJS:s];
    };
    // 注入 HoneJSCoreNativeBridge，方便 JS 统一调用
    [ctx evaluateScript:@"var HoneJSCoreNativeBridge = { callHandler: handleHoneMessageFromJS }"];
    
    ctx.exceptionHandler = ^(JSContext *context, JSValue *exception) {
        NSLog(@"loadJSCoreBundle caught error=%@", exception);
    };
    NSString *script = [self javaScriptBridge];
    [self.ctx evaluateScript:script];
}

#pragma mark - Override
- (void)evaluateJavascript:(NSString *)javascriptCommand {
    [super evaluateJavascript:javascriptCommand];
    [self.ctx evaluateScript:javascriptCommand];
}

@end
