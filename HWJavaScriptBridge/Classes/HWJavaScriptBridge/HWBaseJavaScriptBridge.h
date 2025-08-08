//
//  HNBaseBridge.h
//  JSBridge
//
//  Created by hong on 2022/4/24.
//  Copyright © 2022 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <JavaScriptCore/JavaScriptCore.h>
NS_ASSUME_NONNULL_BEGIN

typedef void (^HWJBResponseCallback)(id responseData);
typedef void (^HNJBHandler)(id data, HWJBResponseCallback responseCallback);

typedef NSDictionary HNJBMessage;

/// JS  /  Native 双工通信桥
@interface HWBaseJavaScriptBridge : NSObject

/// Native调用JS的回调存储
@property (strong, nonatomic) NSMutableDictionary* responseCallbacks;

/// JS调用Native的回调存储
@property (strong, nonatomic) NSMutableDictionary* messageHandlers;

/// 需要注入的javaScript bridge代码
- (NSString*)javaScriptBridge;

/// 监听js的方法调用，并响应
/// @param handlerName 监听的方法名称
/// @param handler 处理回调
- (void)registerHandler:(NSString *)handlerName handler:(__nullable HNJBHandler)handler;

/// 客户端调用JS代码并得到JS的响应
/// @param handlerName js的方法名称
/// @param data 调用参数
/// @param responseCallback 回调
- (void)callHandler:(NSString *)handlerName data:(id)data responseCallback:(HWJBResponseCallback)responseCallback;

/// 子类实现如何执行javaScript方法的函数
/// @param javascriptCommand javaScript代码
- (void)evaluateJavascript:(NSString *)javascriptCommand;

/// 单工通信：JS向Native发送消息消息
/// @param message 消息
- (void)handleHoneMessageFromJS:(NSString *)message;

/// 打印log
- (void)log:(NSString *)action json:(id)json;

@end

NS_ASSUME_NONNULL_END
