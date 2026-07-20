import QtQuick
import QtQuick.Controls
import "../../js/cables.js" as Cables
import synth

Item {
    id: container
    property string label: ""
    property var engine: null
    property string port: ""
    property string labelPos: "";

    property var heldCable: null;
    property var localCables: []; // -> localCables is used to identify the top cable (== last cable pushed) on a particular jack

    implicitWidth: jack.width
    implicitHeight: textItem.height + spacing + jack.height
    width: implicitWidth
    height: implicitHeight

    property real spacing: 4

    Component.onCompleted: {console.log("engine recu : ", engine) }

    Text {
        id: textItem
        text: label
        anchors.horizontalCenter: jack.horizontalCenter
        anchors.bottom: {container.labelPos === "top" ? jack.top : jack.bottom}
        anchors.top: {if (container.labelPos === "bot") jack.bottom}
        anchors.bottomMargin: spacing
    }

    Rectangle {
        id: jack
        width: 30
        height: 30
        radius: width / 2
        border.color: "black"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: proxy
            width: jack.width
            height: jack.height
            visible: true
            Drag.active: mouseArea.drag.active
            Drag.source: container
            Drag.keys: []
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            Drag.onActiveChanged: {
                if (!Drag.active) {
                    // fin du drag : on remet le proxy à sa place d'origine
                    proxy.parent = jack
                    proxy.x = 0
                    proxy.y = 0
                }
            }
        }

        MouseArea {
            property var cable: null;
            property var cables: CablesSingleton.cables

            id: mouseArea
            anchors.fill: parent
            drag.target: proxy

            Timer {
                id: cableRemoveDelayTimer
                interval: 500
                repeat: false

                onTriggered: {
                    const id = container.localCables[container.localCables.length - 1].id;
                    container.localCables.pop();
                    Cables.removeCable(CablesSingleton.cables, id);
                    console.log("Local cables Length after: ", localCables.length);
                    console.log("Global cables after: ", CablesSingleton.cables.length);
                }
            }

            onPressed: {
                InputHandler.print();
                // Reparenter AVANT que drag.target ne commence à calculer quoi que ce soit
                var pos = jack.mapToItem(container, 0, 0)
                proxy.parent = container
                proxy.x = pos.x
                proxy.y = pos.y

                if (InputHandler.getInput("shift") === true) { // removing of a cable from one port
                    const cable = container.localCables[container.localCables.length - 1];
                    cable.target = proxy;
                    container.heldCable = cable;
                } else { // creation of new cable
                    const source = jack;
                    const target = proxy;
                    const color = CablesSingleton.colors[Math.floor(Math.random() * CablesSingleton.colors.length)];
                    const cable = Cables.createNewCable(cables, source, target, container, null, color);
                    CablesSingleton.cables.push(cable);
                    container.localCables.push(cable);
                    container.heldCable = cable;
                }
            }

            onReleased: {
                const res = proxy.Drag.drop();
                if (!res) { // delete cable
                    const cable = container.localCables[localCables.length - 1];
                    console.log("length before = ", localCables.length);
                    console.log("cable = ", cable);
                    if (cable.sourceContainer && cable.targetContainer) {
                        console.log(cable.sourceContainer, cable.targetContainer);
                        console.log(cable.sourceContainer.engine, cable.targetContainer.engine);
                    }
                    if (cable.targetContainer) {
                        engine.disconnectionRequest(
                            cable.sourceContainer.engine,
                            cable.sourceContainer.port,
                            cable.targetContainer.engine,
                            cable.targetContainer.port,
                        );
                    }
                    console.log("HEY");
                    cable.target = cable.source;
                    cableRemoveDelayTimer.start();

                }
                container.heldCable = null;
            }
        }

        DropArea {
            id: dropArea
            anchors.fill: parent
            keys: []
            onDropped: function(drop) { // plugging of a cable
                const source = drop.source.children[1]; // ---> source jack
                const cable = drop.source.heldCable;
                if (cable) {
                    cable.target = container.children[1];
                    cable.targetContainer = container;
                }
                engine.connectionRequest(
                    drop.source.engine,
                    drop.source.port,
                    engine,
                    port
                );
                container.localCables.push(cable);
                drop.accept();
            }
        }
    }
}