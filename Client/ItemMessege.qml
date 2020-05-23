import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

//width: ListView.view.width;
Item {
    id: root
    property alias text: lblText.text
    property alias time: lblTime.text

    property alias backgroundColor: rectBubble.color
    property alias textColor: lblText.color
    property alias font: lblText.font
    
    height: lblText.contentHeight + 2 * defMargin + lblTime.height
    


    Rectangle {
        id: rectBubble
        color: win.bubbleColor
        anchors.fill: parent
        radius: 5

        Text {
            id: lblText
            font.pointSize: 12
            anchors.margins: defMargin
            anchors.top : parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            color: win.textColor
        }
        Text {
            id: lblTime
            anchors.margins: defMargin / 2
            font.pointSize: 8
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: win.textColor
        }

    }
}
