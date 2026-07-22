import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../js/cables.js" as CablesJS
import synth

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
        cableCanvas.width = width;
    }
    onHeightChanged: {
        windowHeight = height;
        cableCanvas.height = height;
    }

    Item {
        id: mainContainer
        objectName: "mainContainer"
        anchors.fill: parent

        property var synth: null;

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

    Canvas {
        id: cableCanvas
        width: rootWindow.width
        height: rootWindow.height
        renderStrategy: Canvas.Cooperative

        property bool start: true;
        property var cables: CablesSingleton.cables
        property var canvas: CanvasSingleton.canvas

        property int minX: 0;
        property int maxX: 0;
        property int minY: 0;
        property int maxY: 0;

        onPaint: {
            const ctx = getContext("2d");
            CanvasSingleton.ctx = ctx;
            cableCanvas.start = false;
            // const minx = cables.reduce((min, c) => (c.points[0] < min ? c.points[0] : min), c.);
            if (cables.length) {
                ctx.clearRect(0, 0, width, height);
            }
            cables.forEach(cable => {
                if (cable.points[0].x < cableCanvas.minX || cableCanvas.minX === 0) minX = cable.points[0].x;
                if (cable.points[cable.points.length - 1].x > cableCanvas.maxX || cableCanvas.maxX === 0) cableCanvas.maxX = cable.points[cable.points.length - 1].x;
                if (cable.points[0].y < cableCanvas.minY || cableCanvas.minY === 0) cableCanvas.minY = cable.points[0].y;
                if (cable.points[cable.points.length - 1].y < cableCanvas.maxY || cableCanvas.maxY === 0) cableCanvas.maxY = cable.points[cable.points.length - 1].y;

                ctx.strokeStyle = "red";
                ctx.beginPath(); // Start a new path
                ctx.rect(minX, minY, maxX - minX, maxY - minY); // Add a rectangle to the current path
                ctx.stroke(); // Render the path
                console.log(minX, minY, maxX, maxY);

                const sourcePos = cable.source.mapToItem(null, cable.source.width / 2, cable.source.height / 2);
                cable.pinEnd(0, sourcePos.x, sourcePos.y);
                const targetPos = cable.target.mapToItem(null, cable.target.width / 2, cable.target.height / 2);
                cable.pinEnd(1, targetPos.x, targetPos.y);
                cable.update();
                cable.draw(ctx)
            });
        }
    }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: cableCanvas.requestPaint()
    }
}
