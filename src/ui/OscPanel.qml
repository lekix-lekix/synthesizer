import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    width: 200
    height: 400
    border.width: 2
    border.color: black

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: "wave"
            onClicked: osc.toggleWave()
        }

        Slider {
            from: 20
            to: 3000
            value: osc.freq
            onValueChanged: osc.freq = value
        }
    }
}