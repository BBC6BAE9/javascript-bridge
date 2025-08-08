//
//  HNJavaScriptBridgeBase.h
//  JSBridge
//
//  Created hong on 2022/4/20.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "HWBaseJavaScriptBridge.h"

NS_ASSUME_NONNULL_BEGIN

/// JSContext环境下通信桥
@interface HWJSContextJavaScriptBridge : HWBaseJavaScriptBridge

/// JSContext
@property(nonatomic, strong) JSContext *ctx;

/// 初始化
/// @param jsContext JSContext
- (instancetype)initWithJSContext:(JSContext *)jsContext;

@end

NS_ASSUME_NONNULL_END
