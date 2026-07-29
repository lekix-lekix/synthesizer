import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Item {
    id: rootItem
    property var engine: null; // -> access to c++ qt wrapper

    anchors.centerIn: parent

    Rectangle {
        id: vca
        width: 150
        height: 500
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.centerIn: parent


        MultiEffect {
            source: vca
            anchors.fill: vca

            shadowEnabled: true
            shadowBlur: 0.8
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 2
            shadowColor: "#30000000"
        }

        MouseArea {
            anchors.fill: parent        // couvre tout le rectangle
            pressAndHoldInterval: 100

            cursorShape: CablesSingleton.currentCursor;

            property bool dragging: false
            property real startX: 0
            property real startY: 0

            onPressAndHold: {
                dragging = true
                vca.anchors.centerIn = undefined
            }

            onPositionChanged: function(mouse) {
                if (dragging) {
                    vca.x += mouse.x - startX
                    vca.y += mouse.y - startY
                }
            }

            onReleased: {
                dragging = false
            }
        }

        Text {
            id: title
            text: "VCA"
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }

        Knob {
            engine: rootItem.engine;
            anchors.centerIn: parent
            targetProperty: "gain";
            height: 100;
            width: 100;
        }

        Rectangle {
            id: connectors;
            width: parent.width * 0.75;
            height: parent.height / 4;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 40;
            border.width: 2;
            radius: 10;
            border.color: "black";

            Jack {
                label: "CV IN";
                labelPos: "top"
                engine: rootItem.engine
                port: "gainCVIn"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 6
            }

            Rectangle {
                width: parent.width * 0.75;
                height: 1;
                border.width: 1;
                border.color: "black";
                anchors.verticalCenter: parent.verticalCenter;
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            Jack {
                label: "IN"
                labelPos: "top"
                engine: rootItem.engine
                port: "audioInput"
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.margins: 6
            }

            Jack {
                label: "OUT"
                labelPos: "top"
                engine: rootItem.engine
                port: "audioOutput"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 6
            }
        }
    }
}
