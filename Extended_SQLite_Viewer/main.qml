import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("SQLite Viewer")

    Rectangle {
        id: rectangle
        color: "#ffffff"
        width: 50
        height: 50
        scale:  mouseArea.containsMouse ? 1.4 : 1.0
        smooth: mouseArea.containsMouse

        Text {
            id: menu_name
            x: 0
            y: 0
            width: parent
            height: parent
            text: qsTr(" =")
            font.pixelSize: 36
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            anchors.margins: -5
            hoverEnabled: true
        }
    }

    Rectangle {
        id: leftField
        x: 22
        y: 52
        width: 278
        height: 404
        color: "#ececec"
    }

    Rectangle {
        id: rightField
        x: 336
        y: 52
        width: 278
        height: 404
        color: "#ececec"
    }
}




/*##^## Designer {
    D{i:1;anchors_height:19;anchors_width:19;anchors_x:0;anchors_y:0}
}
 ##^##*/
