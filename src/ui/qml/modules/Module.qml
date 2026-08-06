import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
// import Q
import synth 1.0

Item {
    property var engine: null; // -> access to c++ qt wrapper
    property string title: "";

    id: rootItem
    anchors.centerIn: parent

    default property alias content: module.data

    Component.onCompleted: console.log("QML World instance:", World);

    RectangularShadow {
        id: shadow
        width: World.gridUnit
        height: World.gridUnit * 3
        scale: World.zoom
        anchors.fill: module
        visible: false

        color: "black"
        radius: 10
        blur: 8
        spread: 5
        opacity: 0.5

        Behavior on offset.x {
            NumberAnimation {
                duration: 300
                easing.type: Easing.OutCubic
            }
        }
        Behavior on offset.y {
            NumberAnimation {
                duration: 300
                easing.type: Easing.OutCubic
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 300
                easing.type: Easing.OutCubic
            }
        }
    }

    Rectangle {
        width: World.gridUnit
        height: World.gridUnit * 3
        scale: World.zoom
        anchors.centerIn: module
        anchors.horizontalCenterOffset: -7
        anchors.verticalCenterOffset: 7
        opacity: 0.6
        border.color: "black"
        border.width: 1
        color: "black"
        radius: 10

        transform: Translate {
            id: blackUnder
            x: 0
            y: 0
        }
    }

    Rectangle {
        id: module
        width: World.gridUnit
        height: World.gridUnit * 3
        scale: World.zoom
        radius: 10
        border.color: "black"
        border.width: 2

        property bool currentlySnapping: false;
        property bool panMoving: false;
        property real offset: 5;

        transform: Translate {
            id: liftOffset
            x: 0
            y: 0
        }

        Behavior on x {
            enabled: !module.panMoving
            NumberAnimation { duration: 100; easing.type: Easing.InOutCubic }
        }

        Behavior on y {
            enabled: !module.panMoving
            NumberAnimation { duration: 100; easing.type: Easing.InOutCubic }
        }

        MultiEffect {
            source: module
            anchors.fill: module

            shadowEnabled: true
            shadowBlur: 0.8
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 4
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
            property real lastGridX: 0
            property real lastGridY: 0

            onPressed: function(mouse) {
                startX = mouse.x;
                startY = mouse.y;
                const pxStartPos = mouseArea.mapToItem(null, mouse.x, mouse.y);
                const startPos = World.pxToCoord(pxStartPos);
                lastGridX = Math.floor(startPos.x);
                lastGridY = Math.floor(startPos.y);
            }

            onPressAndHold: {
                if (module.currentlySnapping) return ;
                dragging = true
                liftAnimUp.start();
                shadow.visible = true;
                shadow.opacity = 0.5
                shadow.offset = {x: -15, y: 15}
            }

            onReleased: {
                if (module.currentlySnapping) return ;
                dragging = false;
                shadow.offset = {x: 0, y: 0};
                shadow.opacity = 0;
                liftAnimDown.start();
            }

            ParallelAnimation {
                id: liftAnimUp
                NumberAnimation { target: liftOffset; property: "x"; to: 10; duration: 600; easing.type: Easing.OutElastic }
                NumberAnimation { target: liftOffset; property: "y"; to: -10; duration: 600; easing.type: Easing.OutElastic }
                NumberAnimation { target: blackUnder; property: "x"; to: -10; duration: 600; easing.type: Easing.OutElastic }
                NumberAnimation { target: blackUnder; property: "y"; to: 10; duration: 600; easing.type: Easing.OutElastic }
            }

            ParallelAnimation {
                id: liftAnimDown
                NumberAnimation { target: liftOffset; property: "x"; to: -5; duration: 800; easing.type: Easing.OutElastic }
                NumberAnimation { target: liftOffset; property: "y"; to: 5; duration: 800; easing.type: Easing.OutElastic }
                NumberAnimation { target: blackUnder; property: "x"; to: -5; duration: 800; easing.type: Easing.OutElastic }
                NumberAnimation { target: blackUnder; property: "y"; to: 5; duration: 800; easing.type: Easing.OutElastic }
            }

            onPositionChanged: function(mouse) {
                if (!dragging) return;
                const currPxPos = mouseArea.mapToItem(null, mouse.x, mouse.y);
                const currPos = World.pxToCoord(currPxPos);
                const gridX = Math.floor(currPos.x);
                const gridY = Math.floor(currPos.y);

                if (gridX !== lastGridX || gridY !== lastGridY) {
                    lastGridX = gridX;
                    lastGridY = gridY;
                    if (!module.currentlySnapping) {
                        module.currentlySnapping = true;
                        mouseArea.snapModuleToGrid(gridX, gridY);
                    }
                }
            }

            Connections {
                target: World
                function onPanChanged() {
                    mouseArea.moveGridModule(); }
            }

            Connections {
                target: World
                function onZoomChanged() {
                    mouseArea.moveGridModule();
                }
            }

            function moveGridModule() {
                module.panMoving = true;
                const pxPos = module.mapToItem(null, 0, 0);
                const relativePos = World.pxToCoord({x: pxPos.x, y: pxPos.y});
                const newRelativePos = {x: Math.round(relativePos.x), y: Math.round(relativePos.y)};
                const newPxPos = World.coordToPx({x: newRelativePos.x, y: newRelativePos.y});
                const newPos = module.parent.mapFromItem(null, newPxPos.x, newPxPos.y);
                module.x = newPos.x + (module.offset * World.zoom);
                module.y = newPos.y - (module.offset * World.zoom);
                module.panMoving = false;
            }

            function snapModuleToGrid(gridX, gridY) {
                const newPxPos = World.coordToPx({x: gridX < 0 ? 0 : gridX, y: gridY < 0 ? 0 : gridY});
                const newPos = module.parent.mapFromItem(null, newPxPos.x, newPxPos.y);
                module.x = newPos.x + module.offset
                module.y = newPos.y - module.offset
                module.currentlySnapping = false;
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
