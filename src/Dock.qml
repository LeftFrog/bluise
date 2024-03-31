import QtQuick
import QtQuick.Controls
import Qt.labs.platform


Rectangle {
    id: main
    width: 1280
    height: 50
    color: palette.midlight
    signal checked(text: string)
    RoundButton {
        objectName: "sort"
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 10
        // x: parent.width - 40
        // y: 10
        width: 30
        height: 30
        radius: 10
        flat: true
        icon.source: "/Users/leftfrog/Documents/Bluise/res/sort.png"
        icon.color: palette.dark
        onClicked: menu.open()
    }
    RoundButton {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 50
        // x: parent.width - 40
        // y: 10
        width: 30
        height: 30
        radius: 10
        flat: true
        icon.source: "/Users/leftfrog/Documents/Bluise/res/sort.png"
        icon.color: palette.dark
        onClicked: filters.open()
    }
    Menu {
        id: filters
        MenuItemGroup {
            id: group2
            items: filters.items
        }
        MenuItem {
            text: "Show uninstalled"
            checkable: true
        }
    }
    Menu {
        objectName: "sortMenu"
        id: menu
        MenuItemGroup {
            objectName: "menuItemGroup"
            items: menu.items
            onTriggered: function (item) { main.checked(item.text) }
        }
        MenuItem {
            text: "Name"
            checkable: true
            checked: true
        }
        MenuItem {
            text: "Release Year"
            checkable: true
        }
    }
    RoundButton {
        objectName: "addButton"
        signal addClicked()
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        width: 30
        height: 30
        radius: 10
        flat: true
        icon.source: "/Users/leftfrog/Documents/Bluise/res/plus.png"
        icon.color: palette.dark
        onClicked: addClicked();
    }
}