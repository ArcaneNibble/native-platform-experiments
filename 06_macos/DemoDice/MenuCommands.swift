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
