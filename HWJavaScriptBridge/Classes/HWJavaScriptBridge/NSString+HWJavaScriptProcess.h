//
//  NSString+JavaScriptProcess.h
//  HNPreRenderiOS
//
//  Createdby hongon 2022/4/27.
//  Copyright © 2022 Fooman. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Category for processing JavaScript-related string operations.
/// 
/// This category provides utility methods for handling strings that come from
/// JavaScript, particularly for dealing with encoding issues and JSON processing.
/// 
/// ## Overview
/// 
/// The `NSString+HWJavaScriptProcess` category extends NSString with methods
/// specifically designed to handle strings that originate from JavaScript execution,
/// helping to resolve common encoding and formatting issues.
@interface NSString (JavaScriptProcess)

/// Processes a string received from JavaScript to handle encoding issues.
/// 
/// This method handles common encoding problems that can occur when strings
/// are passed from JavaScript to native Objective-C code, particularly with
/// JSON strings and special characters.
/// 
/// - Returns: A processed string with resolved encoding issues.
/// 
/// ## Example
/// 
/// ```objective-c
/// NSString *jsString = @"{\"name\":\"John\\nDoe\",\"message\":\"Hello\\nWorld\"}";
/// NSString *processed = [jsString processStringFromJavaScript];
/// // processed will have proper line breaks and encoding
/// ```
- (NSString *)processStringFromJavaScript;

@end

NS_ASSUME_NONNULL_END
