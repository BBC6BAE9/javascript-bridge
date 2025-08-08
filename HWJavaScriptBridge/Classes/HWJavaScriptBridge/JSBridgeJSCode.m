//
//  JSBridgeJSCode.m
//  HWJavaScriptBridge
//
//  Created by hong on 2022/6/5.
//  Copyright © 2022 Fooman. All rights reserved.
//

#import "JSBridgeJSCode.h"

/// 获取JSBridge的代码
/// JS代码会被clang扫描出警告，进行忽略
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-pp-token"

// NOCC:CCN(设计如此:此处是JS代码，不参与Objective - C的代码检查)
NSString * honeJSBridgeJS() {
#define __hone_js_func__(x) #x
   
    // BEGIN preprocessorJSCode
    static NSString * preprocessorJSCode = @__hone_js_func__(
        (function() {
            'use strict';
            
            // 回调管理
            var callbacks = {};
            var handlers = {};
            var callbackId = 0;
            
            function generateId() {
                return 'cb_' + (++callbackId) + '_' + Date.now();
            }
            
            // 核心功能1: 发送消息到Native，接收回调数据
            function invoke(method, params, callback) {
                var id = generateId();
                if (callback) {
                    callbacks[id] = callback;
                }
                
                var message = {
                    method: method,
                    params: params,
                    callbackId: id
                };
                
                // 调用Native方法
                if (window.HoneJSCoreNativeBridge && window.HoneJSCoreNativeBridge.callHandler) {
                    window.HoneJSCoreNativeBridge.callHandler(JSON.stringify(message));
                }
            }
            
            // 核心功能2: 监听Native消息，返回数据
            function on(method, handler) {
                handlers[method] = handler;
            }
            
            // 处理Native发来的消息
            function handleMessage(messageStr) {
                try {
                    var message = JSON.parse(messageStr);
                    
                    // 处理回调消息 (JS调用Native的回调)
                    if (message.callbackId && callbacks[message.callbackId]) {
                        var callback = callbacks[message.callbackId];
                        delete callbacks[message.callbackId];
                        callback(message.data);
                        return;
                    }
                    
                    // 处理Native主动调用JS
                    if (message.method && handlers[message.method]) {
                        var handler = handlers[message.method];
                        var result = handler(message.params);
                        
                        // 如果Native需要回调，发送结果
                        if (message.responseId) {
                            var responseMessage = {
                                responseId: message.responseId,
                                data: result
                            };
                            if (window.HoneJSCoreNativeBridge && window.HoneJSCoreNativeBridge.callHandler) {
                                window.HoneJSCoreNativeBridge.callHandler(JSON.stringify(responseMessage));
                            }
                        }
                    }
                } catch (e) {
                    console.error('JSBridge message parse error:', e);
                }
            }
            
            // 导出接口
            return {
                invoke: invoke,
                on: on,
                handleMessage: handleMessage
            };
        })()
    ); // END preprocessorJSCode
    
#undef __hone_js_func__
    return preprocessorJSCode;
};
#pragma clang diagnostic pop
