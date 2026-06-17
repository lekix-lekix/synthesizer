import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    property var engine: null; // -> access to c++ qt wrapper

    Rectangle {
        id: env
        width: 150
        height: 500
        // width: 100;
        // height: 200;
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.centerIn: parent

        Text {
            id: title
            text: "ENV"
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }

        MultiEffect {
            source: env
            anchors.fill: env

            shadowEnabled: true
            shadowBlur: 0.8
            shadowVerticalOffset: 4
            shadowHorizontalOffset: 2
            shadowColor: "#30000000"
        }

        MouseArea {
            anchors.fill: parent        // couvre tout le rectangle
            pressAndHoldInterval: 100

            property bool dragging: false
            property real startX: 0
            property real startY: 0

            onPressAndHold: {
                dragging = true
                env.anchors.centerIn = undefined
            }

            onPositionChanged: function(mouse) {
                if (dragging) {
                    env.x += mouse.x - startX
                    env.y += mouse.y - startY
                }
            }

            onReleased: {
                dragging = false
            }
        }

        Rectangle {
            width: parent.width * 0.5
            height: parent.height * 0.5
            VSlider {
                label: "A"
            }
            VSlider {
                label: "D"
            }
            VSlider {
                label: "S"
            }
            VSlider {
                label: "R"
            }
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
                label: "TRIGGER";
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 6
            }

            Jack {
                label: "CV OUT"
                anchors.top: parent.top
                anchors.right: parent.right
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
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.margins: 6
            }

            Jack {
                label: "OUT"
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 6
            }
        }
    }
}
