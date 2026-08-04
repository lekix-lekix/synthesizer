import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Module {
    id: mixer4
    engine: mixer4Engine
    title: "MIXER"

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
                        to: 1;
                        value: {mixer4.engine ? mixer4.engine.gain0 : 1}
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: {if (mixer4.engine) mixer4.engine.gain0 = value}
                    }

                    Text {
                        text: "1";
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
                        value: {mixer4.engine ? mixer4.engine.gain1 : 1}
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: {if (mixer4.engine) mixer4.engine.gain1 = value}
                    }

                    Text {
                        text: "2";
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
                        value: {mixer4.engine ? mixer4.engine.gain2 : 1}
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: {if (mixer4.engine) mixer4.engine.gain2 = value}
                    }

                    Text {
                        text: "3";
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
                        value: {mixer4.engine ? mixer4.engine.gain3 : 1}
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onValueChanged: {if (mixer4.engine) mixer4.engine.gain3 = value}
                    }
                    Text {
                        text: "4";
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

        GridLayout {
            width: parent.width
            columns: 4
            columnSpacing: 10

            Jack { Layout.fillWidth: true; engine: mixer4.engine; port: "audioInput0"; label: "1" }
            Jack { Layout.fillWidth: true; engine: mixer4.engine; port: "audioInput1"; label: "2" }
            Jack { Layout.fillWidth: true; engine: mixer4.engine; port: "audioInput2"; label: "3" }
            Jack { Layout.fillWidth: true; engine: mixer4.engine; port: "audioInput3"; label: "4" }
        }
    }
}
