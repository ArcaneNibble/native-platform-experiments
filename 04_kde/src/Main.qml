import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

import com.arcanenibble.demodice 1.0

Kirigami.ApplicationWindow {
    id: root

    width: 400
    height: 400

    Kirigami.PromptDialog {
        id: customDiceDialog
        title: i18nc("@title:window", "Set Custom Dice")
        standardButtons: Kirigami.Dialog.Ok | Kirigami.Dialog.Cancel

        Controls.TextField {
            id: nameField
            validator: IntValidator { bottom: 1 }
            onAccepted: customDiceDialog.onAccepted()
        }

        Component.onCompleted: {
            const button = standardButton(Kirigami.Dialog.Ok);
            button.enabled = Qt.binding( () => nameField.acceptableInput );
            nameField.forceActiveFocus();
        }
        onAccepted: {
            if (!nameField.acceptableInput) return;
            setMaxRoll(parseInt(nameField.text, 10));
            nameField.text = "";
            close();
        }

    }

    globalDrawer: Kirigami.GlobalDrawer {
        isMenu: true
        actions: [
            Kirigami.Action {
                text: i18n("Dice Type")
                icon.name: "edit-entry-symbolic"
                Kirigami.Action {
                    id: d4
                    checkable: true
                    text: i18n("D4")
                    shortcut: "Ctrl+1"
                    onTriggered: setMaxRoll(4);
                }
                Kirigami.Action {
                    id: d6
                    checkable: true
                    text: i18n("D6")
                    shortcut: "Ctrl+2"
                    onTriggered: setMaxRoll(6);
                }
                Kirigami.Action {
                    id: d8
                    checkable: true
                    text: i18n("D8")
                    shortcut: "Ctrl+3"
                    onTriggered: setMaxRoll(8);
                }
                Kirigami.Action {
                    id: d10
                    checkable: true
                    text: i18n("D10")
                    shortcut: "Ctrl+4"
                    onTriggered: setMaxRoll(10);
                }
                Kirigami.Action {
                    id: d12
                    checkable: true
                    text: i18n("D12")
                    shortcut: "Ctrl+5"
                    onTriggered: setMaxRoll(12);
                }
                Kirigami.Action {
                    id: d20
                    checkable: true
                    text: i18n("D20")
                    shortcut: "Ctrl+6"
                    onTriggered: setMaxRoll(20);
                }
                Kirigami.Action {
                    text: i18n("Custom...")
                    shortcut: "Ctrl+7"
                    onTriggered: customDiceDialog.open();
                }
            },
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "application-exit-symbolic"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            },
            Kirigami.Action {
                text: i18n("About")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push(aboutPage)
            }
        ]
    }

    // Update title and checkboxes on load
    Component.onCompleted: setMaxRoll(Backend.maxRoll);

    function setMaxRoll(n) {
        d4.checked = n == 4;
        d6.checked = n == 6;
        d8.checked = n == 8;
        d10.checked = n == 10;
        d12.checked = n == 12;
        d20.checked = n == 20;
        root.title = i18nc("@title:window", "D%1", n);
        Backend.maxRoll = n;
    }

    pageStack.initialPage: Kirigami.Page {
        Controls.Button {
            anchors.centerIn: parent
            width: 150
            height: 150

            text: i18n("Roll!")
            onClicked: text = Backend.roll()
        }
    }

    Component {
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: About
        }
    }
}
