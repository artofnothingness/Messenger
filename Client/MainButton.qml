import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    width: 75
    height: 35
    property alias backGroundColor: rect.color
    property alias buttonText: content.text
    signal buttonClicked();

    Button {
        anchors.fill: parent
        id: mainButton
        font.pointSize: 14
        onClicked : {
           root.buttonClicked();
        }

        contentItem: Text {
            id: content
            text: mainButton.text
            font: mainButton.font
            color:  win.textColor
        }

        background: Rectangle {
            id: rect
            width: parent.width
            height: parent.height

            color: win.panelColor
            border.width: 1
            border.color: win.textColor
            radius: 8
        }
    }
}
