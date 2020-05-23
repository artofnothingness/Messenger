import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root
    color: win.panelColor
    height: 60
    
    property alias textColor: edtText.color
    signal newMessage(string msg)
    
    RowLayout {
        anchors.fill: parent
        anchors.margins: defMargin
        
        TextField {
            id: edtText
            selectByMouse: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            placeholderText: "Write a message..."
            font.pointSize: 10
            color: win.textColor

            background: Rectangle {
                color: root.color
            }
        }

        MainButton {
            id: btnAddItem
            buttonText: "Send"
            onButtonClicked: {
                newMessage(edtText.text)
                edtText.clear()
            }
        }
    }
}
