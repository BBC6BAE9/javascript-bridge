//
//  WebView.swift
//  Pencil
//
//  Created by hong on 2025/8/6.
//
import SwiftUI
import WebKit

#if os(iOS)
typealias WebViewRepresentable = UIViewRepresentable
#elseif os(macOS)
typealias WebViewRepresentable = NSViewRepresentable
#endif

public struct WebView: WebViewRepresentable {
    public init(url: URL) {
        self.url = url
        self.configuration = { _ in }
    }

    public init(
        url: URL? = nil,
        configuration: @escaping (WKWebView) -> Void = { _ in }) {
        self.url = url
        self.configuration = configuration
    }

    private let url: URL?
    private let configuration: (WKWebView) -> Void

#if os(iOS)
public func makeUIView(context: Context) -> WKWebView {
    makeView()
}

public func updateUIView(_ uiView: WKWebView, context: Context) {}
#endif
    
#if os(macOS)
public func makeNSView(context: Context) -> WKWebView {
    makeView()
}

public func updateNSView(_ view: WKWebView, context: Context) {}
#endif
}

private extension WebView {
    
    func makeView() -> WKWebView {
        let config = WKWebViewConfiguration()
        
        // macOS特定配置
        #if os(macOS)
        config.preferences.javaScriptEnabled = true
        config.preferences.javaScriptCanOpenWindowsAutomatically = true
        #endif
        
        let view = WKWebView(frame: .zero, configuration: config)
        
        // 设置代理以处理加载错误
        view.navigationDelegate = WebViewDelegate.shared
        
        configuration(view)
        tryLoad(url, into: view)
        return view
    }

    func tryLoad(_ url: URL?, into view: WKWebView) {
        guard let url = url else {
            print("WebView: URL is nil")
            return
        }
        
        print("WebView: Loading URL: \(url)")
        let request = URLRequest(url: url)
        view.load(request)
    }
}

// 添加WebView代理来处理加载状态和错误
class WebViewDelegate: NSObject, WKNavigationDelegate {
    static let shared = WebViewDelegate()
    
    func webView(_ webView: WKWebView, didStartProvisionalNavigation navigation: WKNavigation!) {
        print("WebView: Started loading")
    }
    
    func webView(_ webView: WKWebView, didFinish navigation: WKNavigation!) {
        print("WebView: Finished loading")
    }
    
    func webView(_ webView: WKWebView, didFail navigation: WKNavigation!, withError error: Error) {
        print("WebView: Failed to load with error: \(error.localizedDescription)")
    }
    
    func webView(_ webView: WKWebView, didFailProvisionalNavigation navigation: WKNavigation!, withError error: Error) {
        print("WebView: Failed provisional navigation with error: \(error.localizedDescription)")
    }
}
