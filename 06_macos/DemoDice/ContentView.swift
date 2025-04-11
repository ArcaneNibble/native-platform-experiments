import SwiftUI

struct ContentView: View {
    @State private var currentDiceRoll: Int = -1;
    
    var body: some View {
        VStack {
            Button {
                currentDiceRoll = Int.random(in: 0...20)
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
        ContentView()
    }
}
