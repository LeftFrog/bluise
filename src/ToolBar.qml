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
            text: "lol"
            flat: true
            radius: parent.parent.radius
        }
        RoundButton {
            text: "ok"
            flat: true
            radius: parent.parent.radius
        }
    }
}