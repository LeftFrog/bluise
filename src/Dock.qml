import QtQuick
import QtQuick.Controls
import Qt.labs.platform


Rectangle {
    width: 1280
    height: 50
    color: palette.midlight
    RoundButton {
        x: parent.width - 40
        y: 10
        width: 30
        height: 30
        radius: 10
        flat: true
        icon.source: "/Users/leftfrog/Documents/Bluise/res/sort.png"
        icon.color: palette.dark
        onClicked: menu.open()
    }
    RoundButton {
        objectName: "addButton"
        signal addClicked()
        x: 10
        y: 10
        width: 30
        height: 30
        radius: 10
        flat: true
        icon.source: "/Users/leftfrog/Documents/Bluise/res/plus.png"
        icon.color: palette.dark
        onClicked: addClicked();
    }
    Menu {
        id: menu
        MenuItem {
            text: "Name"
        }
        MenuItem {
            text: "Date added"
        }
        MenuItem {
            text: "Minecraft"
        }
    }
}