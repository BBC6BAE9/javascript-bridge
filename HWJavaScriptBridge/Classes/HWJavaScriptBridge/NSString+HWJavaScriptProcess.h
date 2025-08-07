//
//  NSString+JavaScriptProcess.h
//  HNPreRenderiOS
//
//  Createdby ihenryhuangon 2022/4/27.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (JavaScriptProcess)

/// 处理JavaScript的JSON字符串的编码问题
- (NSString *)processStringFromJavaScript;

@end

NS_ASSUME_NONNULL_END
