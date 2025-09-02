//
//  JSBridgeJSCode.h
//  HWJavaScriptBridge
//
//  Created by hong on 8/8/25.
//

#import <Foundation/Foundation.h>

/// Returns the JavaScript bridge code that needs to be injected.
/// 
/// This function provides the JavaScript code that should be injected into web pages
/// or JSContext to enable bridge communication between JavaScript and native code.
/// 
/// - Returns: A string containing the complete JavaScript bridge implementation code.
/// 
/// ## Example
/// 
/// ```objective-c
/// NSString *jsCode = honeJSBridgeJS();
/// [webView evaluateJavaScript:jsCode completionHandler:nil];
/// ```
NSString * honeJSBridgeJS(void);
