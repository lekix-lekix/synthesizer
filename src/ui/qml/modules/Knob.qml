import QtQuick
import synth 1.0

Item {
    id: knobRoot

    property real value: 0.5;           // 0.0 à 1.0
    property var engine: null;
    property string targetProperty: ""
    property string label: "";


    Rectangle {
        id: knob
        width: parent.width;
        height: width;
        radius: 60          // cercle parfait
        border.color: "black"
        border.width: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height * 0.1

        Rectangle {
            id: knobButton
            width: parent.width * 0.6
            height: parent.height * 0.6
            radius: width / 2
            color: "black"
            border.color: "black"
            border.width: 2
            anchors.centerIn: parent

            Rectangle {
                id: indicator
                width: 3
                height: parent.height / 2    // va du centre jusqu'au bord
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top      // commence en haut
                transformOrigin: Item.Bottom // tourne depuis le bas (= centre du cercle)
                rotation: knobRoot.value * 270 - 135
            }

            MouseArea {
                cursorShape: CablesSingleton.currentCursor

                hoverEnabled: true;
                onPressed: { CablesSingleton.currentCursor = Qt.ClosedHandCursor; }
                onEntered: { CablesSingleton.currentCursor = Qt.OpenHandCursor; }
                onReleased: { CablesSingleton.currentCursor = Qt.ArrowCursor; }
                onExited: {
                    if (!pressed)
                        CablesSingleton.currentCursor = Qt.ArrowCursor;
                }

                anchors.fill: parent
                onPositionChanged: function(mouse) {
                    if (!pressed) return;
                    const cx = knobButton.width / 2
                    const cy = knobButton.height / 2
                    const angle = Math.atan2(mouse.y - cy, mouse.x - cx)
                    let   degrees = angle * (180 / Math.PI) + 90

                    if (degrees < 0) degrees = degrees + 360
                    if (degrees > 135 && degrees < 225) {
                        if (degrees < 180) {
                            knobRoot.value = 1.0   // colle à droite
                        } else {
                            knobRoot.value = 0.0   // colle à gauche
                        }
                    } else {
                        if (degrees >= 225) degrees = degrees - 360  // -135° à 0°
                        knobRoot.value = (degrees + 135) / 270
                    }
                    knobRoot.engine[knobRoot.targetProperty] = knobRoot.value;
                }
                onDoubleClicked: {
                    knobRoot.engine[knobRoot.targetProperty] = 0.5;
                    knobRoot.value = 0.5;
                }
            }
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: 25
    }
}
