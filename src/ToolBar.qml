import QtQuick
import QtQuick.Controls
import Qt.labs.platform
Rectangle {
    id: main
    color: palette.window
    property int radius: 10
    property int margin: 5
    MenuItemGroup {
        items: filter.items
        exclusive: false
    }
    Menu {
        id: filter
        MenuItem {
            text: "Show unistalled"
            checked: true
        }
        Menu {
            id: platform
            title: "Platform"
            MenuItem {
                text: "Windows"
            }
            MenuItem {
                text: "MacOS"
            }
        }
    }
    Row {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: parent.margin
        RoundButton {
            text: "New Game"
            radius: parent.parent.radius
            flat: true
        }
    }
    Row {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: parent.margin
        Button {
            icon.source: "/Users/leftfrog/Documents/Bluise/res/filter.png"
            icon.color: palette.buttonText
            width: 40
            height: 40
            icon.width: 60
            icon.height: 60
            // flat: true
            // radius: parent.parent.radius
            onClicked: filter.open()
        }
        Button {
            width: 40
            height: 40
            icon.width: 60
            icon.height: 60
            icon.source: "/Users/leftfrog/Documents/Bluise/res/sort.png"
            icon.color: palette.buttonText
            // flat: true
            // radius: parent.parent.radius
        }
    }
}