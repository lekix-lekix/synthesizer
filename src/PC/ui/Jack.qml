import QtQuick

Item {
    id: container
    property string label: ""
    property var engine: null

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
            Drag.source: engine
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
            id: dropArea
            anchors.fill: parent
            keys: []
            onEntered: function(drag) { console.log("survolé par", drag.source) }
            onExited: { console.log("plus survolé") }
            onDropped: function(drop) {
                console.log("a reçu un drop de", drop.source);
                console.log(engine);
                drop.source.print();
                drop.accept();
            }
        }
    }
}