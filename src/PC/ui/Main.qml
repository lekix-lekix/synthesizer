import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1280
    height: 960
    visible: true
    title: qsTr("Hello World")

    Item {
        id: mainContainer
        objectName: "mainContainer"
        anchors.fill: parent

        property var synth: null;

        Button {
            id: moduleButton
            width: 50
            height: 50
            anchors.top: parent.top
            anchors.right: parent.right
            onClicked: menu.open()
        }

        ModulesMenu {
            id: menu
        }

        Drawer {
            height: parent.height
            width: parent.width / 4
        }
    }
}
