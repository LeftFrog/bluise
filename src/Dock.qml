import QtQuick
import QtQuick.Controls
import Qt.labs.platform


Rectangle {
    width: 1280
    height: 50
    color: palette.midlight
    RoundButton {
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
    Menu {
        id: menu
        MenuItemGroup {
            signal checked(text: string)
            items: menu.items
            onTriggered: function (item) { checked(item.text) }
        }
        MenuItem {
            text: "Name"
            checkable: true
            checked: true
        }
        MenuItem {
            text: "Date added"
            checkable: true
        }
    }
}