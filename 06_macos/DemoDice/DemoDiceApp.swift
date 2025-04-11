import SwiftUI

@main
struct DemoDiceApp: App {
    @State private var maxDiceRoll: Int = 20
    
    var body: some Scene {
        WindowGroup {
            ContentView(maxDiceRoll: $maxDiceRoll)
        }
        .commands {
            MenuCommands(maxDiceRoll: $maxDiceRoll)
        }
    }
}
