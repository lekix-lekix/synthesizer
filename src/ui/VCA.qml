import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    property var engine: null; // -> access to c++ qt wrapper

    Rectangle {
        id: vca
        width: 150
        height: 500
        // width: 100;
        // height: 200;
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

        Rectangle {
            id: gainButtonContainer
            width: parent.width * 0.5;
            height: width;
            radius: 60          // cercle parfait
            border.color: "black"
            border.width: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -parent.height * 0.1

            Rectangle {
                id: gainButton
                width: parent.width * 0.6
                height: parent.height * 0.6
                radius: width / 2
                color: "black"
                border.color: "black"
                border.width: 2
                anchors.centerIn: parent

                property real value: 0.5           // 0.0 à 1.0

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
                    rotation: gainButton.value * 270 - 135
                }

                MouseArea {
                    anchors.fill: parent
                    onPositionChanged: function(mouse) {
                        const cx = gainButton.width / 2
                        const cy = gainButton.height / 2
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
                                gainButton.value = 1.0   // colle à droite
                            } else {
                                gainButton.value = 0.0   // colle à gauche
                            }
                        } else {
                            // zone valide
                            if (degrees >= 225) degrees = degrees - 360  // -135° à 0°
                            // degrees est maintenant entre -135 et +135
                            gainButton.value = (degrees + 135) / 270
                        }
                        engine.gain = gainButton.value;
                    }
                    onDoubleClicked: gainButton.value = 0.5;
                }
            }
        }

        Text {
            text: gainButton.freqLabel
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: 20
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
                label: "CV 1";
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 6
            }

            Jack {
                label: "CV 2"
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
