import QtQuick
import QtQuick.Controls

Menu {
    id: menu
    x: parent.x
    y: parent.y

    enum AudioModules {
        VCO,
        VCA,
        ENV,
        MIXER_4
    }
    MenuItem {
        text: "VCO"
        onTriggered: synth.addAudioModule(ModulesMenu.AudioModules.VCO)
    }
    MenuItem {
        text: "VCA"
        onTriggered: synth.addAudioModule(ModulesMenu.AudioModules.VCA)
    }
    MenuItem {
        text: "ENV"
        onTriggered: synth.addAudioModule(ModulesMenu.AudioModules.ENV)
    }
    MenuItem {
        text: "Mixer 4"
        onTriggered: synth.addAudioModule(ModulesMenu.AudioModules.MIXER_4)
    }
}
