import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes
import "../js/cables.js" as CablesJS
import synth 1.0

Window {
    property int windowWidth: 1440
    property int windowHeight: 1024

    id: rootWindow
    width: windowWidth
    height: windowHeight
    visible: true
    title: qsTr("Cutee Synth")

    onWidthChanged: {
        windowWidth = width;
        /*cableCanvas.width = */gridCanvas.width = width;
    }
    onHeightChanged: {
        windowHeight = height;
        /*cableCanvas.height = */gridCanvas.height = height;
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
        id: gridCanvas
        width: rootWindow.width
        height: rootWindow.height
        anchors.fill: parent
        z: -1;

        property int wheelAcc: 0;
        property var gridPaint: {gridCanvas.setGridBool(true);};

        MouseArea {
            id: gridMouseArea
            width: parent.width
            height: parent.height

            property int initPosX: 0;
            property int initPosY: 0;
            property bool initPos: false;

            onPressed: function(mouse) {
                initPosX = mouse.x;
                initPosY = mouse.y;
            }

            onPositionChanged: function(mouse) {
                gridCanvas.setPan({x: mouse.x, y: mouse.y}, {x: initPosX, y: initPosY});
                initPosX = mouse.x;
                initPosY = mouse.y;
            }

            onWheel: (event) => {
                console.log(event.angleDelta.y);
                gridCanvas.wheelAcc += event.angleDelta.y;
                if (gridCanvas.wheelAcc > 120 || gridCanvas.wheelAcc < -120) {
                    if (event.angleDelta.y < 0) gridCanvas.zoomOut();
                    else gridCanvas.zoomIn();
                    gridCanvas.wheelAcc = 0;
                }
            }
        }
    }

    DrawArea {
        id: cableCanvas
        width: rootWindow.windowWidth
        height: rootWindow.windowHeight
        anchors.fill: parent
        anchors.margins: 10
        z: 0

        property var cables: CablesSingleton.cables
        property var canvas: CanvasSingleton.canvas

        function update() {
            cables.forEach(cable => {
                if (!cable || !cable.source || !cable.target) {
                    console.log("skipping invalid cable this frame");
                    return; // just skips this one cable, forEach continues to the next
                }
                const sourcePos = cable.source.mapToItem(cableCanvas, cable.source.width / 2, cable.source.height / 2);
                cable.pinEnd(0, sourcePos.x, sourcePos.y);
                const targetPos = cable.target.mapToItem(cableCanvas, cable.target.width / 2, cable.target.height / 2);
                cable.pinEnd(1, targetPos.x, targetPos.y);
                cable.update();
            });
            cableCanvas.setCables(cables);
        }
    }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: {
            gridCanvas.update();
            cableCanvas.update();
        }
    }
}
