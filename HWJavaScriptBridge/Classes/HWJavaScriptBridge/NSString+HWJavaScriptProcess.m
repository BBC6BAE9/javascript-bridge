//
//  NSString+JavaScriptProcess.m
//  HNPreRenderiOS
//
//  Createdby ihenryhuangon 2022/4/27.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import "NSString+HWJavaScriptProcess.h"

@implementation NSString (JavaScriptProcess)

- (NSString *)processStringFromJavaScript{
    NSString *messageJSON = self;
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\\" withString:@"\\\\"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\'" withString:@"\\\'"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\r" withString:@"\\r"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\f" withString:@"\\f"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\u2028" withString:@"\\u2028"];
       messageJSON = [messageJSON stringByReplacingOccurrencesOfString:@"\u2029" withString:@"\\u2029"];
       return messageJSON;
}

@end
