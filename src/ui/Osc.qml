import QtQuick
import QtQuick.Layouts

Item {
    property var engine: null; // -> access to c++ qt wrapper

    Rectangle {
        id: vco
        width: 150
        height: 500
        radius: 10
        border.color: "black"
        border.width: 2
        anchors.centerIn: parent

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

            onPositionChanged: {
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

        Rectangle {
            id: freqButtonContainer
            width: 120
            height: 120
            radius: 60          // cercle parfait
            border.color: "black"
            border.width: 2
            anchors.centerIn: parent

            Text {
                text: "FREQ"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 8
            }

            Rectangle {
                id: freqButton
                width: parent.width * 0.6
                height: parent.height * 0.6
                radius: width / 2
                color: "black"
                border.color: "black"
                border.width: 2
                anchors.centerIn: parent

                property real valeur: 0.5           // 0.0 à 1.0

                property real octaves: 4                        // octaves de chaque côté
                property real freqMin: 440 / Math.pow(2, octaves)   // ≈ 13.75 Hz
                property real freqMax: 440 * Math.pow(2, octaves)   // ≈ 14 080 Hz
                property real freq: freqMin * Math.pow(freqMax / freqMin, valeur)

                // Affiche la fréquence lisiblement
                property string freqLabel: freq < 1000
                    ? Math.round(freq) + " Hz"
                    : (freq / 1000).toFixed(2) + " kHz"

                Rectangle {
                    id: barre
                    width: 3
                    height: parent.height / 2    // va du centre jusqu'au bord
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top      // commence en haut
                    transformOrigin: Item.Bottom // tourne depuis le bas (= centre du cercle)
                    rotation: freqButton.valeur * 270 - 135
                }

                MouseArea {
                    anchors.fill: parent
                    onPositionChanged: {
                        const cx = freqButton.width / 2
                        const cy = freqButton.height / 2
                        const angle = Math.atan2(mouse.y - cy, mouse.x - cx)
                        let   degrees = angle * (180 / Math.PI) + 90

                        // atan2 saute de +180 à -180 en bas
                        // on ramène tout entre 0 et 360
                        if (degrees < 0) degrees = degrees + 360

                        // maintenant :
                        // 0° = 12h, 90° = 3h, 180° = 6h, 270° = 9h
                        // zone valide : 0° à 135° (droite) et 225° à 360° (gauche)
                        // zone morte : 135° à 225° (bas)

                        if (degrees > 135 && degrees < 225) {
                            // dans la zone morte → bloque au plus proche
                            if (degrees < 180) {
                                freqButton.valeur = 1.0   // colle à droite
                            } else {
                                freqButton.valeur = 0.0   // colle à gauche
                            }
                        } else {
                            // zone valide
                            if (degrees >= 225) degrees = degrees - 360  // -135° à 0°
                            // degrees est maintenant entre -135 et +135
                            freqButton.valeur = (degrees + 135) / 270
                        }
                        engine.freq = freqButton.freq;
                        console.log(engine.freq);
                    }
                    onDoubleClicked: freqButton.valeur = 0.5;
                }
            }

            Text {
                text: freqButton.freqLabel
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
            }

        }

        Rectangle {
            id: wavesContainer
            width: parent.width * 0.75
            height: parent.height / 10;
            border.width: 2;
            border.color: black;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: parent.height / 4;

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                Repeater {
                    model: 4
                    Rectangle {
                        Layout.fillWidth: true    // chaque rond prend la même place
                        height: 30
                        radius: 15
                        border.color: "black"
                        border.width: 2
                    }
                }
            }
        }

        Rectangle {
            id: jacksContainer
            width: parent.width * 0.75
            height: parent.height / 8
            border.color: "black"
            border.width: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            // Jack 1V/OCT à gauche
            Rectangle {
                id: vPerOct
                width: parent.width / 2
                height: parent.height
                anchors.left: parent.left

                Text {
                    text: "1V/OCT"
                    font.pointSize: 8
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Rectangle {
                    width: height
                    height: parent.height * 0.5
                    radius: width / 2       // cercle
                    border.color: "black"
                    border.width: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            // Séparateur
            Rectangle {
                width: 1
                height: parent.height * 0.7
                color: "black"
                anchors.centerIn: parent
            }

            // Jack OUT à droite
            Rectangle {
                id: jackOut
                width: parent.width / 2
                height: parent.height
                anchors.right: parent.right

                Text {
                    text: "OUT"
                    font.pointSize: 8
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Rectangle {
                    width: height
                    height: parent.height * 0.5
                    radius: width / 2       // cercle
                    border.color: "black"
                    border.width: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
