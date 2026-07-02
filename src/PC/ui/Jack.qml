import QtQuick
import QtQuick.Controls
import "cables.js" as Cable

Item {
    id: container
    property string label: ""
    property var engine: null
    property string port: ""

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
        anchors.bottom: jack.top
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
            property var canvas: CanvasSingleton.canvas

            id: mouseArea
            anchors.fill: parent
            drag.target: proxy

            Timer {
                id: cableDelayTimer
                interval: 500
                repeat: false

                onTriggered: {
                    mouseArea.cables.pop();
                }
            }

            onPressed: {
                // Reparenter AVANT que drag.target ne commence à calculer quoi que ce soit
                var pos = jack.mapToItem(container, 0, 0)
                proxy.parent = container
                proxy.x = pos.x
                proxy.y = pos.y

                const source = jack;
                const target = proxy;
                const sourcePos = source.mapToItem(null, source.width / 2, source.height / 2);
                const targetPos = target.mapToItem(null, target.width / 2, target.height / 2);
                const color = CablesSingleton.colors[Math.floor(Math.random() * CablesSingleton.colors.length)];
                const cable = new Cable.Cable(
                    sourcePos.x,
                    sourcePos.y,
                    targetPos.x,
                    targetPos.y,
                    source,
                    target,
                    color,
                    cables.length
                );
                CablesSingleton.cables.push(cable);
            }
            onReleased: {
                const res = proxy.Drag.drop();
                // console.log(res);
                if (!res) {
                    cableDelayTimer.start();
                    // cables.pop();
                }
            }
            onPositionChanged: {
            }
        }

        DropArea {
            property var cables: CablesSingleton.cables
            property var canvas: CanvasSingleton.canvas

            id: dropArea
            anchors.fill: parent
            keys: []
            onEntered: function(drag) { console.log("survolé par", drag.source.port) }
            onExited: { console.log("plus survolé") }
            onDropped: function(drop) {
                const source = drop.source.children[1]; // ---> source jack
                const cable = Cable.findCable(cables, source);
                console.log(cable);
                if (cable)
                    cable.target = container.children[1];
                engine.connectionRequest(
                    drop.source.engine,
                    drop.source.port,
                    engine,
                    port
                );
                drop.accept();
            }
        }
    }
}