import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import synth 1.0

Module {
    id: vco
    engine: vcoEngine
    title: "VCO"

    Knob {
        label: "freq";
        width: parent.width * 0.5;
        height: parent.width * 0.5;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -50;
        engine: vco.engine
        targetProperty: "freq";
    }

    Rectangle {
        id: wavesContainer
        width: parent.width * 0.75
        height: parent.height / 6        // un peu plus haut pour avoir de la place
        border.width: 2
        border.color: "black"
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 50

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            width: parent.width
            height: parent.height
            spacing: 4

            // Les 4 formes d'onde
            RowLayout {
                width: parent.width
                height: parent.height
                Repeater {
                    model: ["sine", "square", "saw", "triangle"]
                    ColumnLayout {
                        width: parent.width
                        height: parent.height
                        property string waveType: modelData

                        Canvas {
                            width: parent.width / 6
                            height: parent.height / 6
                            Layout.alignment: Qt.AlignHCenter
                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.strokeStyle = "black"
                                ctx.lineWidth = 1.5
                                ctx.beginPath()
                                if (waveType === "sine") {
                                    for (var x = 0; x < width; x++) {
                                        var y = height/2 - Math.sin(x / width * Math.PI * 2) * height/2 * 0.8
                                        x === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y)
                                    }
                                } else if (waveType === "square") {
                                    ctx.moveTo(0, 2)
                                    ctx.lineTo(width/2, 2)
                                    ctx.lineTo(width/2, height-2)
                                    ctx.lineTo(width, height-2)
                                } else if (waveType === "saw") {
                                    ctx.moveTo(0, height-2)
                                    ctx.lineTo(width-2, 2)
                                    ctx.lineTo(width-2, height-2)
                                } else if (waveType === "triangle") {
                                    ctx.moveTo(0, height/2)
                                    ctx.lineTo(width/4, 2)
                                    ctx.lineTo(width*3/4, height-2)
                                    ctx.lineTo(width, height/2)
                                }
                                ctx.stroke();
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            height: 10
                            radius: 5
                            border.color: "black"
                            border.width: 2
                            color: vco.engine && vco.engine.wave === waveType ? "green" : "transparent";
                        }
                    }
                }
            }
            Rectangle {
                id: underButton
                Layout.preferredWidth: parent.width * 0.50
                Layout.preferredHeight: parent.height * 0.25
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

                radius: 5
                border.color: "black"
                border.width: 2

                MouseArea {
                    hoverEnabled: true;
                    cursorShape: CablesSingleton.currentCursor
                    onEntered: { CablesSingleton.currentCursor = Qt.PointingHandCursor; }
                    onExited: {
                        if (!pressed)
                            CablesSingleton.currentCursor = Qt.ArrowCursor;
                    }

                    anchors.fill: parent   // ✅ OK
                    onClicked: vco.engine.toggleWave()
                }
            }
        }
    }

    Rectangle {
        id: jacksContainer
        width: parent.width * 0.75
        height: parent.height / 8
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        Jack {
            label: "OUT"
            labelPos: "bot";
            port: "audioOutput"
            anchors.right: parent.right
            engine: vco.engine
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            height: parent.height;
            width: 1;
            border.color: "black";
            border.width: 1;
            anchors.horizontalCenter: parent.horizontalCenter;
        }

        Jack {
            label: "CV IN"
            labelPos: "bot"
            port: "freqCVIn"
            anchors.left: parent.left;
            engine: vco.engine
            anchors.verticalCenter: parent.verticalCenter

            Knob {
                width: 25
                height: 25
                value: 0
                engine: vco.engine
                targetProperty: "freqCVInAmount";
                anchors.centerIn: parent;
                anchors.verticalCenterOffset: -parent.height * 1.2
            }
        }
    }
}
