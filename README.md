# HWJavaScriptBridge

[![Version](https://img.shields.io/cocoapods/v/HWJavaScriptBridge.svg?style=flat)](https://cocoapods.org/pods/HWJavaScriptBridge)
[![License](https://img.shields.io/cocoapods/l/HWJavaScriptBridge.svg?style=flat)](https://cocoapods.org/pods/HWJavaScriptBridge)
[![Platform](https://img.shields.io/cocoapods/p/HWJavaScriptBridge.svg?style=flat)](https://cocoapods.org/pods/HWJavaScriptBridge)

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

![bridge](./bridge.png)

## Requirements

iOS 6.0+

## Installation

### CocoaPods

HWJavaScriptBridge is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'HWJavaScriptBridge'
```

### Swift Package Manager

You can also use Swift Package Manager to install HWJavaScriptBridge. Add the following dependency to your `Package.swift`:

```swift
dependencies: [
    .package(url: "https://github.com/bbc6bae9/HWJavaScriptBridge.git", from: "1.0.0")
]
```

Or add it directly in Xcode:
1. Go to File → Add Package Dependencies
2. Enter the repository URL: `https://github.com/bbc6bae9/HWJavaScriptBridge.git`
3. Select the version you want to use

## Usage

### For  WKWebView
```objective-c
 HWWebViewJavaScriptBridge *bridge = [[HWWebViewJavaScriptBridge alloc] initWithWebView:self.webView];
    self.bridge = bridge;
    [bridge registerHandler:@"invoke" handler:^(id  _Nonnull data, HWJBResponseCallback  _Nonnull responseCallback) {
        NSDictionary *clientData = @{
            @"code":@(0),
            @"msg":@"success",
            @"data":@{@"company":@"Fooman"}
        };
        responseCallback(clientData);
    }];
```
```objective-c
 [self.bridge callHandler:@"dispatchEvent" data:@{@"func": @"preRender"} responseCallback:^(id  _Nonnull responseData) {
        NSLog(@"[preRender] callback =%@", responseData);
    }];
```
### For  JSContext

```objective-c
    JSVirtualMachine *vm = [[JSVirtualMachine alloc] init];
    JSContext *ctx = [[JSContext alloc] initWithVirtualMachine:vm];
    self.ctx  = ctx;
    HWJSContextJavaScriptBridge *bridge = [[HWJSContextJavaScriptBridge alloc] initWithJSContext:ctx];
    self.bridge = bridge;
    
    // 监听JS调用的postMessage方法
    [bridge registerHandler:@"invoke" handler:^(id  _Nonnull data, HWJBResponseCallback  _Nonnull responseCallback) {
        NSDictionary *clientData = @{
            @"code":@(0),
            @"msg":@"success",
            @"data":@{@"company":@"Fooman"}
        };
        responseCallback(clientData);
    }];
```

```objective-c
 // 客户端主动调用JS，并得到JS的回应
    NSDictionary *data = @{
        @"func":@"preRender",
        @"params":@{
            @"url":@"https://m.film.qq.com"
        }
    };
    [self.bridge callHandler:@"dispatchEvent" data:data responseCallback:^(id responseData) {
        NSLog(@"[preRender] recieve callback data=%@", responseData);
    }];
```



## Author

bbc6bae9, bbc6bae9@gmail.com

## License

HWJavaScriptBridge is available under the MIT license. See the LICENSE file for more info.
