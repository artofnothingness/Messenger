import QtQuick 2.0

Item {
    id:root
    height: 80
    anchors.margins: defMargin
    property alias title: title.text

    Rectangle {
        id: rectTitle
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        color: win.panelColor
        radius: 5
        Text {
            id: title
            font.pointSize: 35
            anchors.margins: defMargin
            anchors.top : parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            color: win.textColor

        }
    }
}
