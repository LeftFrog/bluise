import QtQuick
import QtQuick.Controls
Rectangle {
    color: palette.window
    property int radius: 10
    property int margin: 5
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
        RoundButton {
            icon.source: "/Users/leftfrog/Documents/Bluise/res/filter.png"
            icon.color: palette.buttonText
            flat: true
            radius: parent.parent.radius
        }
        RoundButton {
            icon.source: "/Users/leftfrog/Documents/Bluise/res/sort.png"
            icon.color: palette.buttonText
            flat: true
            radius: parent.parent.radius
        }
    }
}