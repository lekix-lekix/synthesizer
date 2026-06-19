import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1280
    height: 960
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

    Osc {
        anchors.centerIn: parent;
        engine: osc2;
    }

    VCA {
        anchors.centerIn: parent;
        engine: vca;
    }

    Env {
        anchors.centerIn: parent;
        engine: env;
    }

    Mixer4 {
        anchors.centerIn: parent;
        engine: mixer;
    }
}
