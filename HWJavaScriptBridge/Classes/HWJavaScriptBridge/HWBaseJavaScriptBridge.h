//
//  HNBaseBridge.h
//  JSBridge
//
//  Created by hong on 2022/4/24.
//  Copyright © 2022 Fooman. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <JavaScriptCore/JavaScriptCore.h>
NS_ASSUME_NONNULL_BEGIN

/// Callback block for JavaScript bridge responses.
/// 
/// This block is called when a response is received from JavaScript.
/// 
/// - Parameter responseData: The response data from JavaScript, typically an NSDictionary or NSArray.
typedef void (^HWJBResponseCallback)(id responseData);

/// Handler block for JavaScript bridge method calls.
/// 
/// This block is called when JavaScript invokes a native method.
/// 
/// - Parameter data: The data passed from JavaScript, typically an NSDictionary or NSArray.
/// - Parameter responseCallback: The callback block to send a response back to JavaScript.
typedef void (^HWJBHandler)(id data, HWJBResponseCallback responseCallback);

/// Message type for JavaScript bridge communication.
/// 
/// Messages are typically NSDictionary objects containing method names and parameters.
typedef NSDictionary HNJBMessage;

/// Base class for JavaScript bridge implementations.
/// 
/// This class provides the core functionality for bidirectional communication between
/// JavaScript and native Objective-C code. It supports both WKWebView and JSContext environments.
/// 
/// ## Overview
/// 
/// `HWBaseJavaScriptBridge` is an abstract base class that defines the interface and common
/// functionality for JavaScript bridge implementations. It manages message handlers,
/// response callbacks, and provides the foundation for JavaScript injection.
/// 
/// ## Usage
/// 
/// ```objective-c
/// // Create a concrete bridge implementation
/// HWWebViewJavaScriptBridge *bridge = [[HWWebViewJavaScriptBridge alloc] initWithWebView:webView];
/// 
/// // Register a handler for JavaScript calls
/// [bridge registerHandler:@"getUserInfo" handler:^(id data, HWJBResponseCallback responseCallback) {
///     NSDictionary *userInfo = @{@"name": @"John", @"email": @"john@example.com"};
///     responseCallback(userInfo);
/// }];
/// 
/// // Call JavaScript from native code
/// [bridge callHandler:@"showAlert" data:@{@"message": @"Hello!"} responseCallback:^(id responseData) {
///     NSLog(@"Alert shown: %@", responseData);
/// }];
/// ```
/// 
/// ## Subclassing
/// 
/// Subclasses must implement the `evaluateJavascript:` method to provide the specific
/// mechanism for executing JavaScript code in their environment.
@interface HWBaseJavaScriptBridge : NSObject

/// Storage for native-to-JavaScript response callbacks.
/// 
/// This dictionary stores callback blocks that are waiting for responses from JavaScript.
/// The keys are unique identifiers for each callback.
@property (strong, nonatomic) NSMutableDictionary* responseCallbacks;

/// Storage for JavaScript-to-native message handlers.
/// 
/// This dictionary stores handler blocks that are registered to handle calls from JavaScript.
/// The keys are the handler names that JavaScript can call.
@property (strong, nonatomic) NSMutableDictionary* messageHandlers;

/// Returns the JavaScript bridge code that needs to be injected.
/// 
/// This method returns the JavaScript code that should be injected into the web page
/// or JSContext to enable bridge communication.
/// 
/// - Returns: A string containing the JavaScript bridge code.
- (NSString*)javaScriptBridge;

/// Registers a handler for JavaScript method calls.
/// 
/// This method allows you to register a handler that will be called when JavaScript
/// invokes a method with the specified name.
/// 
/// - Parameter handlerName: The name of the handler that JavaScript will call.
/// - Parameter handler: The block that will be executed when the handler is called.
/// 
/// ## Example
/// 
/// ```objective-c
/// [bridge registerHandler:@"getUserInfo" handler:^(id data, HWJBResponseCallback responseCallback) {
///     NSDictionary *userInfo = @{
///         @"name": @"John Doe",
///         @"email": @"john@example.com"
///     };
///     responseCallback(userInfo);
/// }];
/// ```
- (void)registerHandler:(NSString *)handlerName handler:(__nullable HWJBHandler)handler;

/// Calls a JavaScript method and receives a response.
/// 
/// This method allows native code to call JavaScript methods and receive responses
/// through the provided callback block.
/// 
/// - Parameter handlerName: The name of the JavaScript method to call.
/// - Parameter data: The data to pass to the JavaScript method.
/// - Parameter responseCallback: The callback block that will receive the response from JavaScript.
/// 
/// ## Example
/// 
/// ```objective-c
/// [bridge callHandler:@"showAlert" data:@{@"message": @"Hello World!"} responseCallback:^(id responseData) {
///     NSLog(@"JavaScript responded: %@", responseData);
/// }];
/// ```
- (void)callHandler:(NSString *)handlerName data:(id)data responseCallback:(HWJBResponseCallback)responseCallback;

/// Evaluates JavaScript code in the current environment.
/// 
/// This is an abstract method that subclasses must implement to provide the specific
/// mechanism for executing JavaScript code in their environment (WKWebView or JSContext).
/// 
/// - Parameter javascriptCommand: The JavaScript code to execute.
/// 
/// ## Subclassing Notes
/// 
/// - In `HWWebViewJavaScriptBridge`, this method calls `evaluateJavaScript:completionHandler:` on the WKWebView.
/// - In `HWJSContextJavaScriptBridge`, this method calls `evaluateScript:` on the JSContext.
- (void)evaluateJavascript:(NSString *)javascriptCommand;

/// Handles messages sent from JavaScript to native code.
/// 
/// This method processes incoming messages from JavaScript and routes them to the
/// appropriate registered handlers.
/// 
/// - Parameter message: The message string from JavaScript, typically JSON-encoded.
- (void)handleHoneMessageFromJS:(NSString *)message;

/// Logs bridge activity for debugging purposes.
/// 
/// This method provides logging functionality to help debug bridge communication.
/// 
/// - Parameter action: A string describing the action being logged.
/// - Parameter json: The data associated with the action.
- (void)log:(NSString *)action json:(id)json;

@end

NS_ASSUME_NONNULL_END
