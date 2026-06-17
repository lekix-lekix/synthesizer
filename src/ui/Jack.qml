import QtQuick

Item {
    id: root
    property string label: ""

    width: 40
    height: 50

    Text {
        text: root.label
        font.pointSize: 8
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        width: 30
        height: 30
        radius: width / 2
        border.color: "black"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
