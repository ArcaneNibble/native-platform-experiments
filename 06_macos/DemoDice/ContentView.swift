import SwiftUI

struct DiceView: View {
    @State private var currentDiceRoll: Int = -1
    @Binding var maxDiceRoll: Int
    
    var body: some View {
        VStack {
            Button {
                currentDiceRoll = Int.random(in: 1...maxDiceRoll)
            } label: {
                Text(LocalizedStringKey(currentDiceRoll == -1 ? "Roll!" : String(currentDiceRoll)))
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
        .navigationTitle("Demo Dice - D\(Int64(maxDiceRoll))")
        #endif
    }
}
struct DiceView_Previews: PreviewProvider {
    static var previews: some View {
        DiceView(maxDiceRoll: .constant(20))
    }
}

// https://stackoverflow.com/questions/72636810/swiftui-numeric-textfield-maximum-and-minimum-values
class CustomRangeFormatter : Formatter {
    override func string(for obj: Any?) -> String? {
        guard let number = obj as? Int else {
            return nil
        }
        return String(number)
    }
    override func getObjectValue(_ obj: AutoreleasingUnsafeMutablePointer<AnyObject?>?, for string: String, errorDescription error: AutoreleasingUnsafeMutablePointer<NSString?>?) -> Bool {

        guard var number = Int(string) else {
            return false
        }
        
        if number < 1 {
            number = 1
        }
        obj?.pointee = number as AnyObject
        
        return true
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
                              formatter: CustomRangeFormatter())
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
