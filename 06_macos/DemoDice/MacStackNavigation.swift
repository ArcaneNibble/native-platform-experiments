import SwiftUI

// Steal this stack navigation https://medium.com/better-programming/stack-navigation-on-macos-41a40d8ec3a4
struct StackNavigationView<RootContent, SubContent>: View where RootContent: View, SubContent: View {
    @Binding var showingSubview: Bool
    let rootView: () -> RootContent
    let subView: () -> SubContent
    
    init(
        showingSubview: Binding<Bool>,
        @ViewBuilder rootView: @escaping () -> RootContent,
        @ViewBuilder subView: @escaping () -> SubContent) {
        self._showingSubview = showingSubview
        self.rootView = rootView
        self.subView = subView
    }
    
    var body: some View {
        VStack {
            if !showingSubview {
                rootView()
            } else {
                StackNavigationSubview(isVisible: $showingSubview) {
                    subView()
                }
                .transition(.move(edge: .trailing))
            }
        }
    }
}
private struct StackNavigationSubview<Content>: View where Content: View {
    @Binding var isVisible: Bool
    let contentView: () -> Content
    
    var body: some View {
        VStack {
            contentView()
        }
        .toolbar {
            ToolbarItem(placement: .navigation) {
                Button(action: {
                    withAnimation(.easeOut(duration: 0.3)) {
                        isVisible = false
                    }
                }, label: {
                    Label("back", systemImage: "chevron.left")
                })
            }
        }
    }
}
