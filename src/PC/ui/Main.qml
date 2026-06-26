import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    // id: windowRoot
    width: 1280
    height: 960
    visible: true
    title: qsTr("Hello World")

    Item {
        id: mainContainer
        objectName: "mainContainer"
        width: parent.width
        height: parent.height
    }

    // Vco {
    //     anchors.centerIn: parent;
    //     engine: osc;
    // }

    // Vco {
    //     anchors.centerIn: parent;
    //     engine: osc2;
    // }

    // Vca {
    //     anchors.centerIn: parent;
    //     engine: vca;
    // }

    // Env {
    //     anchors.centerIn: parent;
    //     engine: env;
    // }

    // Mixer4 {
    //     anchors.centerIn: parent;
    //     engine: mixer;
    // }
}
