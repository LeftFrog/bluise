import QtQuick
import QtQuick.Controls

Rectangle {
    width: 390
    height: 234
    color: palette.window
    visible:true

    Rectangle {
    width: parent.width
    height: parent.height
    objectName: "MainRect"
    radius: 10
    property int useful_height: height/18*4;
    property int margin: (height/18)/2
    color: palette.light
    property alias img_source: img.source

    Image {
        id: img
        width: parent.width
        height: parent.height / 18 * 13
        x: 0
        y: 0 + parent.height / 18
        source: "../res/header.jpg"
        smooth: true
        visible:true
    }

    Button {
        id: bt1
        height: parent.useful_height - parent.margin
        width: height
        x: parent.width - parent.margin/2 - width
        y :parent.height - parent.margin/2 - height
        icon.cache: true
        icon.source: "../res/settings.png"
        icon.color: "#d1d1d1"
        icon.width: 2*width
        icon.height: 2*height
    }
    Button {
        signal playClicked()
        objectName: "play_button"
        height: bt1.height
        width: bt1.width
        x: bt1.x - width
        y: bt1.y
        icon.cache: true
        icon.source: "../res/play.png"
        icon.color: "#d1d1d1"
        icon.width: 2*width
        icon.height: 2*height
        onClicked: playClicked();
    }

    Text {
        objectName: "Name"
        id: name
        text: "LOL"
        font.family: "Apple Braille"
        font.pointSize: (parent.useful_height - 2*parent.margin) * (2/3)
        color: palette.windowText
        height: bt1.height
        x: parent.margin
        y: bt1.y + (parent.useful_height - 2*parent.margin) / 3
    }
}
}

