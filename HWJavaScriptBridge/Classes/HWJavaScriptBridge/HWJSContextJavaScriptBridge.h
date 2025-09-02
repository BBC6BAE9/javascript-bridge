//
//  HNJavaScriptBridgeBase.h
//  JSBridge
//
//  Created hong on 2022/4/20.
//  Copyright © 2022 Fooman. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "HWBaseJavaScriptBridge.h"

NS_ASSUME_NONNULL_BEGIN

/// JavaScript bridge implementation for JSContext.
/// 
/// This class provides a bridge between JSContext and native Objective-C code,
/// enabling bidirectional communication with JavaScript running in a JavaScriptCore context.
/// 
/// ## Overview
/// 
/// `HWJSContextJavaScriptBridge` extends `HWBaseJavaScriptBridge` to provide
/// JSContext-specific JavaScript execution capabilities. It works with JavaScriptCore
/// to enable communication between native code and JavaScript code running in a JSContext.
/// 
/// ## Usage
/// 
/// ```objective-c
/// // Create JSContext
/// JSVirtualMachine *vm = [[JSVirtualMachine alloc] init];
/// JSContext *ctx = [[JSContext alloc] initWithVirtualMachine:vm];
/// 
/// // Initialize bridge
/// HWJSContextJavaScriptBridge *bridge = [[HWJSContextJavaScriptBridge alloc] initWithJSContext:ctx];
/// self.bridge = bridge;
/// 
/// // Register handlers
/// [bridge registerHandler:@"calculateSum" handler:^(id data, HWJBResponseCallback responseCallback) {
///     NSArray *numbers = data[@"numbers"];
///     NSNumber *sum = [numbers valueForKeyPath:@"@sum.self"];
///     responseCallback(@{@"sum": sum});
/// }];
/// 
/// // Execute JavaScript code
/// [ctx evaluateScript:@"function multiply(a, b) { return a * b; }"];
/// ```
/// 
/// ## JavaScript Integration
/// 
/// The bridge provides JavaScript functions for communication:
/// 
/// ```javascript
/// // Call native methods
/// WebViewJavascriptBridge.callHandler('calculateSum', {
///     numbers: [1, 2, 3, 4, 5]
/// }, function(response) {
///     console.log('Sum:', response.sum);
/// });
/// 
/// // Register handlers for native calls
/// WebViewJavascriptBridge.registerHandler('formatDate', function(data, responseCallback) {
///     const date = new Date(data.timestamp);
///     responseCallback({ formatted: date.toLocaleDateString() });
/// });
/// ```
@interface HWJSContextJavaScriptBridge : HWBaseJavaScriptBridge

/// Initializes the bridge with a JSContext instance.
/// 
/// This method sets up the bridge for communication with the specified JSContext.
/// It configures the JavaScript environment and injects the necessary bridge code.
/// 
/// - Parameter jsContext: The JSContext instance to bridge with.
/// - Returns: An initialized bridge instance.
/// 
/// ## Example
/// 
/// ```objective-c
/// JSVirtualMachine *vm = [[JSVirtualMachine alloc] init];
/// JSContext *ctx = [[JSContext alloc] initWithVirtualMachine:vm];
/// HWJSContextJavaScriptBridge *bridge = [[HWJSContextJavaScriptBridge alloc] initWithJSContext:ctx];
/// ```
- (instancetype)initWithJSContext:(JSContext *)jsContext;

@end

NS_ASSUME_NONNULL_END
