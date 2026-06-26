import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    property var engine: null; // -> access to c++ qt wrapper

    Rectangle {
        id: env
        width: 150
        height: 500
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
            z: 100;
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
            height: parent.height * 0.30
            anchors.centerIn: parent

            RowLayout {
                anchors.fill: parent
                spacing: 5
                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 5

                        VSlider {
                            from: 0
                            to: 1000;
                            value: {engine ? engine.attack : 0}
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            onValueChanged: {if (engine) engine.attack = value}
                        }

                        Text {
                            text: "A";
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 5

                        VSlider {
                            from: 0
                            to: 2000;
                            value: {engine ? engine.decay : 0}
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            onValueChanged: {if (engine) engine.decay = value}
                        }

                        Text {
                            text: "D";
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 5

                        VSlider {
                            from: 0
                            to: 1;
                            value: {engine ? engine.sustain : 0}
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            onValueChanged: {if (engine) engine.sustain = value}
                        }

                        Text {
                            text: "S";
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 5

                        VSlider {
                            from: 0
                            to: 2000;
                            value: {engine ? engine.release : 0}
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter
                            onValueChanged: {if (engine) engine.release = value }
                        }
                        Text {
                            text: "R";
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }

        Rectangle {
            id: connectors
            width: parent.width * 0.75
            height: parent.height / 8
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            Jack {
                label: "GATE"
                anchors.left: parent.left
                anchors.margins: 6;
            }

            Rectangle {
                height: parent.height;
                width: 1;
                border.color: "black";
                border.width: 1;
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            Jack {
                label: "CV OUT"
                anchors.right: parent.right;
                anchors.margins: 6;
            }
        }
    }
}