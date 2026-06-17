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

    background: Rectangle {
        x: root.leftPadding + root.availableWidth / 2 - width / 2
        y: root.topPadding
        width: 4
        height: root.availableHeight
        radius: 2
        color: root.trackColor

        Rectangle {
            width: parent.width
            height: root.visualPosition * parent.height
            anchors.bottom: parent.bottom
            radius: 2
            color: root.fillColor
        }
    }

    handle: Rectangle {
        x: root.leftPadding + root.availableWidth / 2 - width / 2
        y: root.topPadding + root.visualPosition * (root.availableHeight - height)
        width: 24
        height: 24
        radius: 12
        color: root.pressed ? root.fillColor : root.handleColor
        border.color: root.trackColor
        border.width: 2
    }

}