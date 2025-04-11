import SwiftUI

@main
struct DemoDiceApp: App {
    @State private var maxDiceRoll: Int = 20
    @State private var showCustom: Bool = false
    
    var body: some Scene {
        WindowGroup {
            ContentView(
                maxDiceRoll: $maxDiceRoll,
                showCustom: $showCustom
            )
        }
        .commands {
            MenuCommands(
                maxDiceRoll: $maxDiceRoll,
                showCustom: $showCustom
            )
        }
    }
}
