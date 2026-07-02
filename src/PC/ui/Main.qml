import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "cables.js" as CablesJS

Window {
    property int windowWidth: 1280
    property int windowHeight: 960

    id: rootWindow
    width: windowWidth
    height: windowHeight
    visible: true
    title: qsTr("Hello World")

    Item {
        id: mainContainer
        objectName: "mainContainer"
        anchors.fill: parent

        property var synth: null;

        Button {
            id: moduleButton
            width: 50
            height: 50
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked: menu.open()
        }

        ModulesMenu {
            id: menu
        }

        Drawer {
            height: parent.height
            width: parent.width / 4
        }
    }

    Canvas {
        id: cableCanvas
        width: rootWindow.windowWidth
        height: rootWindow.windowHeight

        property bool start: true;
        property var cables: CablesSingleton.cables
        property var canvas: CanvasSingleton.canvas

        onPaint: {
            const ctx = getContext("2d");
            CanvasSingleton.ctx = ctx;
            cableCanvas.start = false;
            ctx.clearRect(0, 0, width, height);
            cables.forEach(c => {
                const sourcePos = c.source.mapToItem(null, c.source.width / 2, c.source.height / 2);
                const targetPos = c.target.mapToItem(null, c.target.width / 2, c.target.height / 2);
                c.pinEnd(0, sourcePos.x, sourcePos.y);
                c.pinEnd(1, targetPos.x, targetPos.y);
                c.update();
                c.draw(ctx)
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
