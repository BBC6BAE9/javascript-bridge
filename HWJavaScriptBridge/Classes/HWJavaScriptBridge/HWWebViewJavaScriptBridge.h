//
//  HNWebViewBridge.h
//  JSBridge
//
//  Created by hong on 2022/4/24.
//  Copyright © 2022 Fooman. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>
#import "HWBaseJavaScriptBridge.h"

NS_ASSUME_NONNULL_BEGIN

/// JavaScript bridge implementation for WKWebView.
/// 
/// This class provides a bridge between WKWebView and native Objective-C code,
/// enabling bidirectional communication with JavaScript running in web pages.
/// 
/// ## Overview
/// 
/// `HWWebViewJavaScriptBridge` extends `HWBaseJavaScriptBridge` to provide
/// WKWebView-specific JavaScript execution capabilities. It automatically injects
/// the necessary JavaScript bridge code into web pages and handles communication
/// through WKWebView's message handling system.
/// 
/// ## Usage
/// 
/// ```objective-c
/// // Create WKWebView
/// WKWebView *webView = [[WKWebView alloc] initWithFrame:self.view.bounds];
/// [self.view addSubview:webView];
/// 
/// // Initialize bridge
/// HWWebViewJavaScriptBridge *bridge = [[HWWebViewJavaScriptBridge alloc] initWithWebView:webView];
/// self.bridge = bridge;
/// 
/// // Register handlers
/// [bridge registerHandler:@"getUserInfo" handler:^(id data, HWJBResponseCallback responseCallback) {
///     NSDictionary *userInfo = @{@"name": @"John", @"email": @"john@example.com"};
///     responseCallback(userInfo);
/// }];
/// 
/// // Load web content
/// [webView loadHTMLString:@"<html><body><h1>Bridge Test</h1></body></html>" baseURL:nil];
/// ```
/// 
/// ## JavaScript Integration
/// 
/// The bridge automatically injects JavaScript code that provides the following global object:
/// 
/// ```javascript
/// // Call native methods
/// WebViewJavascriptBridge.callHandler('getUserInfo', {}, function(response) {
///     console.log('User info:', response);
/// });
/// 
/// // Register handlers for native calls
/// WebViewJavascriptBridge.registerHandler('showAlert', function(data, responseCallback) {
///     alert(data.message);
///     responseCallback({ success: true });
/// });
/// ```
@interface HWWebViewJavaScriptBridge : HWBaseJavaScriptBridge

/// Initializes the bridge with a WKWebView instance.
/// 
/// This method sets up the bridge for communication with the specified WKWebView.
/// It automatically configures the necessary message handlers and injects the
/// JavaScript bridge code into the web view.
/// 
/// - Parameter webview: The WKWebView instance to bridge with.
/// - Returns: An initialized bridge instance.
/// 
/// ## Example
/// 
/// ```objective-c
/// WKWebView *webView = [[WKWebView alloc] initWithFrame:self.view.bounds];
/// HWWebViewJavaScriptBridge *bridge = [[HWWebViewJavaScriptBridge alloc] initWithWebView:webView];
/// ```
- (instancetype)initWithWebView:(WKWebView *)webview;

@end

NS_ASSUME_NONNULL_END
