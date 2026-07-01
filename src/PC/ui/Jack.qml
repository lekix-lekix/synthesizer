import QtQuick
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
            id: mouseArea
            anchors.fill: parent
            drag.target: proxy
            onPressed: {
                // Reparenter AVANT que drag.target ne commence à calculer quoi que ce soit
                var pos = jack.mapToItem(container, 0, 0)
                proxy.parent = container
                proxy.x = pos.x
                proxy.y = pos.y
            }
            onReleased: {
                proxy.Drag.drop();
            }
        }

        DropArea {
            property var cables: container.parent.parent.parent.parent.cables
            property var canvas: container.parent.parent.parent.parent.canvas

            id: dropArea
            anchors.fill: parent
            keys: []
            onEntered: function(drag) { console.log("survolé par", drag.source.port) }
            onExited: { console.log("plus survolé") }
            onDropped: function(drop) {
                console.log(drop.source.children);
                const source = drop.source.children[1];
                const target = container.children[1];
                // console.log("a reçu un drop de", drop.source.engine);
                const sourcePos = source.mapToItem(canvas, source.width / 2, source.height / 2);
                const targetPos = target.mapToItem(canvas, target.width / 2, target.height / 2);
                cables.push(new Cable.Cable(sourcePos.x, sourcePos.y, targetPos.x, targetPos.y, "black"));
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