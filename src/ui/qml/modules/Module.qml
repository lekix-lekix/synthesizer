import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Item {
    property var engine: null; // -> access to c++ qt wrapper
    property string title: "";

    id: rootItem
    anchors.centerIn: parent

    default property alias content: module.data

    Component.onCompleted: console.log("QML World instance:", World);

    Rectangle {
        id: module
        width: CablesSingleton.unit;
        height: CablesSingleton.unit * 3;
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.centerIn: parent

        Rectangle {
            id: shadow3d
            z: module.z - 1
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -5
            anchors.verticalCenterOffset: 5

            border.color: "black"
            border.width: 1
            radius: 10
            color: "black"

            MultiEffect {
                source: shadow3d
                anchors.fill: shadow3d

                shadowEnabled: true
                shadowBlur: 0.8
                shadowVerticalOffset: 4
                shadowHorizontalOffset: 2
                shadowColor: "#30000000"
            }
        }

        MultiEffect {
            source: module
            anchors.fill: module

            shadowEnabled: true
            shadowBlur: 0.8
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 2
            shadowColor: "#30000000"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent        // couvre tout le rectangle
            pressAndHoldInterval: 100

            cursorShape: CablesSingleton.currentCursor

            property bool dragging: false
            property real startX: 0
            property real startY: 0

            onPressed: function(mouse) {
                startX = mouse.x;
                startY = mouse.y;
            }

            onPressAndHold: {
                dragging = true
                module.anchors.centerIn = undefined
            }

            onPositionChanged: function(mouse) {
                if (dragging) {
                    module.x += mouse.x - startX
                    module.y += mouse.y - startY
                    const pos = module.mapToItem(null, 0, 0);
                }
            }

            onReleased: {
                dragging = false;
                mouseArea.snapToGrid();
            }

            Connections {
                target: World
                function onPanChanged() { mouseArea.snapToGrid(); }
            }

            function snapToGrid() {
                // console.log(World.pan);
                const pxPos = module.mapToItem(null, 0, 0);
                // console.log("pxPos: ", pxPos.x, pxPos.y);
                const relativePos = World.pxToCoord({x: pxPos.x, y: pxPos.y});
                // console.log("relativePos : ", relativePos.x, relativePos.y);
                const newRelativePos = {x: Math.round(relativePos.x), y: Math.round(relativePos.y)};
                // console.log("new pos = ", newRelativePos.x, newRelativePos.y);
                const newPxPos = World.coordToPx({x: newRelativePos.x, y: newRelativePos.y});
                const newPos = module.parent.mapFromItem(null, newPxPos.x, newPxPos.y);
                module.x = newPos.x;
                module.y = newPos.y;
            }
        }

        Text {
            id: title
            text: rootItem.title
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }
    }
}
