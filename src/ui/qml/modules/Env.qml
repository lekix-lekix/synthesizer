import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Module {
    id: env
    engine: envEngine
    title: "ENV"

    Text {
        id: title
        text: "ENV"
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        z: 100;
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.5
        anchors.centerIn: parent
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        // border.color: "black"
        // border.width: 2

        GridLayout {
            // anchors.fill: parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            rowSpacing: 20
            // columnSpacing: 5

            ColumnLayout {
                // spacing:
                Knob {
                    Layout.alignment: Qt.AlignHCenter
                    engine: env.engine
                    targetProperty: "attack"
                    width: 50
                    height: 50
                }
                Text { text: "A"; Layout.alignment: Qt.AlignHCenter }
            }

            ColumnLayout {
                // spacing:
                Knob {
                    Layout.alignment: Qt.AlignHCenter
                    engine: env.engine
                    targetProperty: "decay"
                    width: 50
                    height: 50
                }
                Text { text: "D"; Layout.alignment: Qt.AlignHCenter }
            }

            ColumnLayout {
                // spacing:
                Knob {
                    Layout.alignment: Qt.AlignHCenter
                    engine: env.engine
                    targetProperty: "sustain"
                    width: 50
                    height: 50
                }
                Text { text: "S"; Layout.alignment: Qt.AlignHCenter }
            }

            ColumnLayout {
                // spacing:
                Knob {
                    Layout.alignment: Qt.AlignHCenter
                    engine: env.engine
                    targetProperty: "release"
                    width: 50
                    height: 50
                }
                Text { text: "R"; Layout.alignment: Qt.AlignHCenter }
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
            label: "GATE" // -> add gateIn
            labelPos: "top"
            engine: env.engine
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
            labelPos: "top"
            engine: env.engine
            port: "cvOut"
            anchors.right: parent.right;
            anchors.margins: 6;
        }
    }
}