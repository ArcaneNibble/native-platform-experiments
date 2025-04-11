import SwiftUI

struct MenuCommands: Commands {
    @Binding var maxDiceRoll: Int
    
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
    
    var body: some Commands {
        CommandMenu("Dice") {
            Toggle("D4", isOn: isD4).keyboardShortcut("1", modifiers: .command)
            Toggle("D6", isOn: isD6).keyboardShortcut("2", modifiers: .command)
            Toggle("D8", isOn: isD8).keyboardShortcut("3", modifiers: .command)
            Toggle("D10", isOn: isD10).keyboardShortcut("4", modifiers: .command)
            Toggle("D12", isOn: isD12).keyboardShortcut("5", modifiers: .command)
            Toggle("D20", isOn: isD20).keyboardShortcut("6", modifiers: .command)
        }
    }
}

struct ContentView: View {
    @State private var currentDiceRoll: Int = -1
    @Binding var maxDiceRoll: Int
    
    var body: some View {
        VStack {
            Button {
                currentDiceRoll = Int.random(in: 1...maxDiceRoll)
            } label: {
                Text(currentDiceRoll == -1 ? "Roll!" : String(currentDiceRoll))
                    .font(.largeTitle)
                    .frame(width: 100, height: 100)
                    .foregroundColor(.white)
                    .background(.gray)
                    .cornerRadius(8)
            }
            .buttonStyle(.plain)
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView(maxDiceRoll: .constant(20))
    }
}
