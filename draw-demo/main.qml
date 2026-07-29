import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import DrawDemo 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: "DrawArea demo"

    DrawArea {
        id: canvas
        anchors.fill: parent
        anchors.margins: 10

        MouseArea {
            anchors.fill: parent
            onPressed: canvas.startStroke(mouseX, mouseY)
            onPositionChanged: canvas.addPoint(mouseX, mouseY)
        }
    }

    Button {
        text: "Clear"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        onClicked: canvas.clear()
    }
}