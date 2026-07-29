import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import "../js/cables.js" as CablesJS
import synth 1.0

Window {
    property int windowWidth: 1280
    property int windowHeight: 960

    id: rootWindow
    width: windowWidth
    height: windowHeight
    visible: true
    title: qsTr("Cutee Synth")

    onWidthChanged: {
        windowWidth = width;
        canvas.width = width;
    }
    onHeightChanged: {
        windowHeight = height;
        canvas.height = height;
    }

    Item {
        id: mainContainer
        objectName: "mainContainer"
        anchors.fill: parent

        property var synth: null;

        HoverHandler {
            cursorShape: CablesSingleton.currentCursor
        }

        Button {
            id: moduleButton
            width: 50
            height: 50
            anchors.margins: 5
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked: menu.open()
            background: Rectangle {
                border.color: "grey"
                border.width: 1
                radius: 5
                color: parent.down ? "#bbbbbb" :
                    (parent.hovered ? "#d6d6d6" : "#f6f6f6")
            }

            Rectangle {
                width: 2
                height: parent.height / 3;
                anchors.centerIn: parent
                border.width: 2
                border.color: "black"
            }

            Rectangle {
                height: 2
                width: parent.width / 3;
                anchors.centerIn: parent
                border.width: 2
                border.color: "black"
            }
        }

        ModulesMenu {
            id: menu
            x: moduleButton.x
            y: moduleButton.y
        }

        Drawer {
            height: parent.height
            width: parent.width / 4
        }
    }

    DrawArea {
        id: canvas
        width: rootWindow.width
        height: rootWindow.height
        anchors.fill: parent
        anchors.margins: 10

        property var cables: CablesSingleton.cables
        property var canvas: CanvasSingleton.canvas
        property int i: 0;

        function update() {
            cables.forEach(cable => {
                if (!cable || !cable.source || !cable.target) {
                    console.log("skipping invalid cable this frame");
                    return; // just skips this one cable, forEach continues to the next
                }
                const sourcePos = cable.source.mapToItem(canvas, cable.source.width / 2, cable.source.height / 2);
                // console.log(sourcePos);
                cable.pinEnd(0, sourcePos.x, sourcePos.y);
                const targetPos = cable.target.mapToItem(canvas, cable.target.width / 2, cable.target.height / 2);
                // console.log(targetPos);
                cable.pinEnd(1, targetPos.x, targetPos.y);
                cable.update();
            });
            canvas.setCables(cables);
        }
    }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: { canvas.update(); }
    }
}
