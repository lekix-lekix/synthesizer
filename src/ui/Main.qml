import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    // Slider {
        // from: 20
        // to: 2000
        // value: osc.frequency       // ← lit ta Q_PROPERTY
        // onValueChanged: osc.freq = value  // ← appelle ton setter

    // }

    Osc {
        anchors.centerIn: parent;
        engine: osc;
    }

    VCA {
        engine: vca;
    }

    Env {
        engine: env;
    }
}
