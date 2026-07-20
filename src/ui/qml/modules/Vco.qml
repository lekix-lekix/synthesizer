import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: rootItem
    property var engine: null; // -> access to c++ qt wrapper

    anchors.centerIn: parent

    Rectangle {
        id: vco
        width: 150
        height: 500
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.centerIn: parent


        MultiEffect {
            source: vco
            anchors.fill: vco

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
                vco.anchors.centerIn = undefined
            }

            onPositionChanged: function(mouse) {
                if (dragging) {
                    vco.x += mouse.x - startX
                    vco.y += mouse.y - startY
                }
            }

            onReleased: {
                dragging = false
            }
        }

        Text {
            id: title
            text: "VCO"
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }

        Knob {
            label: "freq";
            width: 100;
            height: 100;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -50;
            engine: rootItem.engine
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
            anchors.verticalCenterOffset: 100

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
                                color: engine && engine.wave === waveType ? "green" : "transparent";
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
                        anchors.fill: parent   // ✅ OK
                        onClicked: engine.toggleWave()
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
                engine: rootItem.engine
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
                engine: rootItem.engine
                anchors.verticalCenter: parent.verticalCenter

                Knob {
                    width: 25
                    height: 25
                    value: 0
                    engine: rootItem.engine
                    targetProperty: "freqCVInAmount";
                    anchors.centerIn: parent;
                    anchors.verticalCenterOffset: -parent.height
                }
            }
        }
    }
}
