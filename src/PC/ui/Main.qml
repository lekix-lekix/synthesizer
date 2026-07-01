import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "cables.js" as Cables

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
        property var cables: [];

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

        onPaint: {
            const ctx = getContext("2d");
            // if (cableCanvas.start === true) {
                // Cables.buildCables(Cables.modules);
            cableCanvas.start = false;
            // }
            // Cables.cables.forEach((c, i) => {
            //     const p1 = Cables.jackPos(Cables.modules[0], Cables.modules[0].jacks[i], 'right');
            //     const p2 = Cables.jackPos(Cables.modules[1], Cables.modules[1].jacks[i], 'left');
            //     c.pinEnd(0, p1.x, p1.y);
            //     c.pinEnd(1, p2.x, p2.y);
            //     c.update();
            // });
            ctx.clearRect(0, 0, width, height);
            mainContainer.cables.forEach(c => {
                c.update();
                c.draw(ctx)
            });
            // console.log(mainContainer.cables);
            // Cables.modules.forEach((m) => Cables.drawModule(m, ctx));

            requestAnimationFrame(() => cableCanvas.requestPaint())
        }
    }
}
