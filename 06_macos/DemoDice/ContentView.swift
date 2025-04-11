import SwiftUI

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
        #if os(macOS)
        .navigationTitle("Demo Dice - D\(maxDiceRoll)")
        #endif
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
        .navigationTitle("Set custom dice")
    }
}
struct CustomDiceView_Previews: PreviewProvider {
    static var previews: some View {
        CustomDiceView(maxDiceRoll: .constant(20))
    }
}
