// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "HWJavaScriptBridge",
    platforms: [
        .iOS(.v9),
        .macOS(.v10_13)
    ],
    products: [
        .library(
            name: "HWJavaScriptBridge",
            targets: ["HWJavaScriptBridge"]),
    ],
    targets: [
        .target(
            name: "HWJavaScriptBridge",
            path: "HWJavaScriptBridge/Classes",
            publicHeadersPath: "."
        )
    ]
) 
