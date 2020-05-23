import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

//width: ListView.view.width;
Item {
    id: root
    property alias text: lblText.text
    property alias backgroundColor: rectBubble.color
    property alias textColor: lblText.color
    property alias font: lblText.font



    height: lblText.contentHeight + 2 * defMargin
    Rectangle {
        id: rectBubble
        color: win.bubbleColor
        anchors.fill: parent
        radius: 5

        Text {
            id: lblText
            font.pointSize: 14
            anchors.margins: defMargin
            anchors.centerIn: parent
            color: win.textColor
        }
        MouseArea {
            anchors.fill: parent

            onClicked: {
                mainStackView.push(messagesPage)
            }
        }
    }
}
