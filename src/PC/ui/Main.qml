import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1280
    height: 960
    visible: true
    title: qsTr("Hello World")

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
