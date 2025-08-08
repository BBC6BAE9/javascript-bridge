//
//  HNWebViewBridge.m
//  JSBridge
//
//  Created by hong on 2022/4/24.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import "HWWebViewJavaScriptBridge.h"
#import "JSBridgeJSCode.h"

/// 代理：解决addScriptMessageHandler导致的循环饮用问题
@interface WeakProxy : NSProxy

/// 初始化方法
/// @param object 实例
+ (instancetype)weakProxy:(id)object;

/// 实例
@property (nonatomic, weak) id object;

@end

@implementation WeakProxy

+ (instancetype)weakProxy:(id)object {
    return [[WeakProxy alloc] initWithObject:object];
}

- (instancetype)initWithObject:(id)object {
    self.object = object;
    return self;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel {
    return [self.object methodSignatureForSelector:sel];
}

- (void)forwardInvocation:(NSInvocation *)invocation {
    [invocation invokeWithTarget:self.object];
}

@end

@interface HWWebViewJavaScriptBridge()<WKScriptMessageHandler>

@end

@implementation HWWebViewJavaScriptBridge{
    __weak WKWebView* _webView;
}

- (instancetype)initWithWebView:(WKWebView *)webview{
    if (self = [super init]) {
        [self injectJSBridge:webview];
    }
    return self;
}

- (void)injectJSBridge:(WKWebView *)webView{
    _webView = webView;
    [_webView.configuration.userContentController addScriptMessageHandler:(id<WKScriptMessageHandler>)[WeakProxy weakProxy:self] name:@"handleHoneMessageFromJS"];
    
    // 注入 Native Bridge，统一调用接口
    NSString *nativeBridgeStr = @"var HoneJSCoreNativeBridge = { callHandler: function(message) { window.webkit.messageHandlers.handleHoneMessageFromJS.postMessage(message); } };";
    WKUserScript *nativeBridgeScript = [[WKUserScript alloc] initWithSource:nativeBridgeStr injectionTime:WKUserScriptInjectionTimeAtDocumentEnd forMainFrameOnly:YES];
    [_webView.configuration.userContentController addUserScript: nativeBridgeScript];
    
    // 注入 JSBridge
    NSString *jspath = [[NSBundle mainBundle]pathForResource:@"honejsbridge" ofType:@"js"];
    NSString *str = honeJSBridgeJS();
    //注入时机是在webview加载状态WKUserScriptInjectionTimeAtDocumentStart、WKUserScriptInjectionTimeAtDocumentEnd
    WKUserScript *userScript = [[WKUserScript alloc] initWithSource:str injectionTime:WKUserScriptInjectionTimeAtDocumentEnd forMainFrameOnly:YES];
    [_webView.configuration.userContentController addUserScript:userScript];
    
}

- (void)userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message {
    if ([message.name isEqualToString:@"handleHoneMessageFromJS"]) {
        NSString *s = message.body;
        [self handleHoneMessageFromJS:s];
    }
}

#pragma mark - Override
- (void)evaluateJavascript:(NSString *)javascriptCommand {
    [_webView evaluateJavaScript:javascriptCommand completionHandler:nil];
}

@end
