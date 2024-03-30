import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle {
    width: 390
    height: 234
    color: palette.base
    visible:true

    Rectangle {
    width: parent.width
    height: parent.height
    objectName: "MainRect"
    radius: 10
    property int useful_height: height/18*4;
    property int margin: (height/18)/2
    property bool disabled: true
    color: palette.midlight
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
    // MultiEffect {
    //     objectName: "effect"
    //     anchors.fill: img
    //     source: img
    //     saturation: parent.disabled ? -1.0 : 0
    // }
    Button {
        id: bt1
        signal editClicked()
        objectName: "edit_button"
        height: parent.useful_height - parent.margin
        width: height
        x: parent.width - parent.margin/2 - width
        y :parent.height - parent.margin/2 - height
        icon.cache: true
        icon.source: "../res/settings.png"
        icon.color: palette.dark 
        icon.width: 2*width
        icon.height: 2*height
        onClicked: editClicked();
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
        icon.color: palette.dark 
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

