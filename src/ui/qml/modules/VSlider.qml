import QtQuick
import QtQuick.Controls

// VSlider.qml
Slider {
    id: root
    orientation: Qt.Vertical
    property color trackColor: "black"
    property color fillColor: "#00bcd4"
    property color handleColor: "white"
    property string label: "";

    // handle: Rectangle {
    //     border.color: "black";
    //     border.width: 1;
    //     width: 5;
    //     height
    // }


    // background: Rectangle {
    //     width: 4
    //     height: 100;
    //     radius: 2
    //     color: "black"

    //     // Rectangle {
    //     //     width: parent.width
    //     //     height: root.visualPosition * parent.height
    //     //     anchors.bottom: parent.bottom
    //     //     radius: 2
    //     //     color: root.fillColor
    //     // }
    // }

    // handle: Rectangle {
    //     // x: root.leftPadding + root.availableWidth / 2 - width / 2
    //     // y: root.topPadding + root.visualPosition * (root.availableHeight - height)
    //     width: 24
    //     // height: 24
    //     // radius: 12
    //     // color: root.pressed ? root.fillColor : root.handleColor
    //     border.color: "black"
    //     border.width: 2
    // }

}