import SwiftUI

@main
struct DemoDiceApp: App {
    @AppStorage("maxDiceRoll") private var maxDiceRoll: Int = 20
    @State private var showingCustomDice = false
    
    private func showCustomDice() {
        withAnimation(.easeOut(duration: 0.3)) {
            showingCustomDice = true
        }
    }
    
    var body: some Scene {
        WindowGroup {
            #if os(macOS)
            StackNavigationView(
                showingSubview: $showingCustomDice,
                rootView: {
                    DiceView(maxDiceRoll: $maxDiceRoll)
                    .toolbar {
                        ToolbarItem {
                            Button(action: showCustomDice, label: {
                                Label("Customize", systemImage: "gear")
                            })
                        }
                    }
                },
                subView: { CustomDiceView(maxDiceRoll: $maxDiceRoll) }
            )
            #else
            NavigationView {
                DiceView(maxDiceRoll: $maxDiceRoll)
                .toolbar {
                    NavigationLink {
                        CustomDiceView(maxDiceRoll: $maxDiceRoll)
                    } label: {
                        Label("Customize", systemImage: "gear")
                    }
                }
                CustomDiceView(maxDiceRoll: $maxDiceRoll)
            }
            .navigationViewStyle(.stack)
            #endif
        }
        .commands {
            MenuCommands(maxDiceRoll: $maxDiceRoll, showCustomDiceView: showCustomDice)
        }
    }
}
