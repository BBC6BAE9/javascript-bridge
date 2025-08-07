//
//  ContentView.swift
//  Demo
//
//  Created by hong on 8/7/25.
//

import SwiftUI
import HWJavaScriptBridge

struct ContentView: View {
    
    let url = URL(string: "https://www.qq.com/")
    
    var body: some View {
        WebView(url: url)
    }
}

#Preview {
    ContentView()
}
