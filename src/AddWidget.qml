import QtQuick
import QtQuick.Controls


Rectangle {
    width: 50
    height: width
    color: palette.window
    visible: true
    Rectangle {
        id: mainRect
        width: 50  //parent.width
        height: 50 // parent.height
        radius: 30
        color: palette.midlight
        // property bool hovered: mouse.hovered
        property bool visibleButtons: false
        // state: "mainState"
        // onHoveredChanged: state = (hovered) ? "hoveredState" : "mainState"
        // 
        //         states: [
        //             State {
        //                 name: "mainState"
        //                 PropertyChanges {
        //                     target: mainRect
        //                     width: 50
        //                     visibleButtons: false
        //                 }
        //             },
        //             State {
        //                 name: "hoveredState"
        //                 PropertyChanges {
        //                     target: mainRect
        //                     width: 150
        //                     visibleButtons: true
        //                 }
        //             }
        //         ]
        //         transitions: [
        //             Transition {
        //                 from: "mainState"
        //                 to: "hoveredState"
        //                 PropertyAnimation {
        //                     target: mainRect
        //                     properties: "width"
        //                     easing.type: Easing.OutCirc
        //                     duration: 200
        //                 }
        //             },
        //             Transition {
        //                 from: "hoveredState"
        //                 to: "mainState"
        //                 PropertyAnimation {
        //                     target: mainRect
        //                     properties: "width"
        //                     easing.type: Easing.OutCircle
        //                     duration: 200
        //                 }
        //             }
        //         ]
        HoverHandler {
            id: mouse
            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
        }
        RoundButton {
            width: 50 // parent.width
            height: 50 // parent.height
            radius: parent.radius
            flat: true
            icon.cache: true
            icon.source: "/Users/leftfrog/Projects/add_widget/plus.png"
            icon.color: palette.dark // "#404040"
        }
        RoundButton {
            width: 50 // parent.width
            height: 50 // parent.height
            x: 50
            radius: parent.radius
            flat: true
            visible: parent.visibleButtons
            icon.cache: true
            icon.source: "/Users/leftfrog/Projects/add_widget/plus.png"
            icon.color: palette.dark // "#404040"
        }
        RoundButton {
            width: 50 // parent.width
            height: 50 // parent.height
            x: 100
            radius: parent.radius
            flat: true
            visible: parent.visibleButtons
            icon.cache: true
            icon.source: "/Users/leftfrog/Projects/add_widget/plus.png"
            icon.color: palette.dark // "#404040"
        }
    }
}
