import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Module {
    id: vca
    engine: vcaEngine; // -> access to c++ qt wrapper
    title: "VCA"

    Text {
        id: title
        text: "VCA"
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Knob {
        engine: vca.engine;
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -25
        targetProperty: "gain";
        height: 100;
        width: 100;
    }

    Rectangle {
        id: connectors;
        width: parent.width * 0.85;
        height: parent.height * 0.30;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 40;
        border.width: 2;
        radius: 10;
        border.color: "black";

        GridLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            columns: 2

            ColumnLayout {
                Layout.row: 0
                Layout.column: 0
                Layout.preferredWidth: 50   // same value on all 3 ColumnLayouts
                Layout.alignment: Qt.AlignHCenter
                Jack {
                    Layout.alignment: Qt.AlignHCenter
                    engine: vca.engine
                    port: "gainCVIn"
                }
                Text {
                    text: "CV IN";
                    Layout.alignment: Qt.AlignCenter
                }
            }
            ColumnLayout {
                Layout.row: 1
                Layout.column: 0
                Layout.preferredWidth: 50   // same value on all 3 ColumnLayouts
                // Layout.bottomMargin: 10
                transform: Translate { y: -20 }
                Jack {
                    Layout.alignment: Qt.AlignHCenter
                    engine: vca.engine
                    port: "audioInput"
                }
                Text {
                    text: "IN";
                    Layout.alignment: Qt.AlignCenter
                }
            }
            ColumnLayout {
                Layout.row: 1
                Layout.column: 1
                Layout.preferredWidth: 50   // same value on all 3 ColumnLayouts
                transform: Translate { y: -20 }
                Jack {
                    Layout.alignment: Qt.AlignHCenter
                    engine: vca.engine
                    port: "audioOutput"
                }
                Text {
                    text: "OUT";
                    Layout.alignment: Qt.AlignCenter
                }

            }
        }
    }
}

