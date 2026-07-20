pragma Singleton
import QtQuick

QtObject {
    id: cableSingleton
    property var colors: ["orange", "black", "pink", "green", "blue", "grey", "red", "purple"]
    property var cables: [];
}
