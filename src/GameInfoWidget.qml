import QtQuick
import QtQuick.Controls

Rectangle {
    signal playClicked();
    signal settingsClicked();
    width: 800
    height: 100
    color: palette.midlight
    property alias iconSource: setting
    property alias nameText: name.text
    Column {
        objectName: "column"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 5
        Label {
            id: name
            text: "Game"
            font.pointSize: 22
            font.family: "Andale Mono"
            anchors.leftMargin: 7
            anchors.left: parent.left
        }
        Row {
            objectName: "row"
            Button {
                signal playClicked();
                objectName: "play"
                width: 100
                height: 40
                text: "Play"
                onClicked: playClicked();
            }
            Button {
                signal settingsClicked();
                objectName: "settings"
                id: setting
                width: 40
                height: 40
                icon.source: "/Users/leftfrog/Documents/Bluise/res/down.png"
                icon.width: 50
                icon.height: 50
                onClicked: settingsClicked();
            }
        }
    }
}