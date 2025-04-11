import SwiftUI

struct MenuCommands: Commands {
    @Binding var maxDiceRoll: Int
    var showCustomDiceView: () -> ()
    
    private var isD4: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 4},
            set: { if $0 { maxDiceRoll = 4 } }
        )
    }
    private var isD6: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 6},
            set: { if $0 { maxDiceRoll = 6 } }
        )
    }
    private var isD8: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 8},
            set: { if $0 { maxDiceRoll = 8 } }
        )
    }
    private var isD10: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 10},
            set: { if $0 { maxDiceRoll = 10 } }
        )
    }
    private var isD12: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 12},
            set: { if $0 { maxDiceRoll = 12 } }
        )
    }
    private var isD20: Binding<Bool> {
        Binding(
            get: { return maxDiceRoll == 20},
            set: { if $0 { maxDiceRoll = 20 } }
        )
    }
    
    private var isCustom: Binding<Bool> {
        Binding(
            get: {
                if maxDiceRoll == 4 { return false }
                if maxDiceRoll == 6 { return false }
                if maxDiceRoll == 8 { return false }
                if maxDiceRoll == 10 { return false }
                if maxDiceRoll == 12 { return false }
                if maxDiceRoll == 20 { return false }
                return true
            }, set: {_ in
                showCustomDiceView()
            }
        )
    }
    
    var body: some Commands {
        CommandMenu("Dice") {
            Toggle("D4", isOn: isD4).keyboardShortcut("1", modifiers: .command)
            Toggle("D6", isOn: isD6).keyboardShortcut("2", modifiers: .command)
            Toggle("D8", isOn: isD8).keyboardShortcut("3", modifiers: .command)
            Toggle("D10", isOn: isD10).keyboardShortcut("4", modifiers: .command)
            Toggle("D12", isOn: isD12).keyboardShortcut("5", modifiers: .command)
            Toggle("D20", isOn: isD20).keyboardShortcut("6", modifiers: .command)
            Toggle("Custom...", isOn: isCustom).keyboardShortcut("7", modifiers: .command)
        }
    }
}

struct DiceView: View {
    @State private var currentDiceRoll: Int = -1
    @Binding var maxDiceRoll: Int
    
    var body: some View {
        VStack {
            Button {
                currentDiceRoll = Int.random(in: 1...maxDiceRoll)
            } label: {
                Text(currentDiceRoll == -1 ? "Roll!" : String(currentDiceRoll))
                    .font(.largeTitle)
                    .frame(width: 300, height: 300)
                    .foregroundColor(.white)
                    .background(.gray)
                    .cornerRadius(8)
            }
            .buttonStyle(.plain)
        }
        .padding()
    }
}
struct DiceView_Previews: PreviewProvider {
    static var previews: some View {
        DiceView(maxDiceRoll: .constant(20))
    }
}

struct CustomDiceView: View {
    @Binding var maxDiceRoll: Int

    var body: some View {
        Form {
            Section(header: Text("Max dice roll")) {
                HStack {
                    TextField("",
                              value: $maxDiceRoll,
                              formatter: NumberFormatter())
                    #if os(iOS)
                    .keyboardType(.decimalPad)
                    #endif
                    Stepper("",
                            value: $maxDiceRoll,
                            in: 1...Int.max)
                    .labelsHidden()
                }
            }
        }
        .padding()
    }
}
struct CustomDiceView_Previews: PreviewProvider {
    static var previews: some View {
        CustomDiceView(maxDiceRoll: .constant(20))
    }
}

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
