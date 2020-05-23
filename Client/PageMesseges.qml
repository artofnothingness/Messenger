import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: pageMessages

    property alias backGroundColor: backGroundRect.color
    background: Rectangle {
        id: backGroundRect
    }

    Keys.onEscapePressed: {
        popPage();
    }

    footer: MessageWritingArea {
        onNewMessage: {
            if (msg === "") { return; }
            var newMsg = {};
            newMsg.text = msg;
            newMsg.time = Qt.formatTime(new Date(), "hh:mm");
            listModel.append(newMsg);
        }
    }

    ListView {
        spacing: defMargin
        anchors.topMargin: 10
        ScrollBar.vertical: ScrollBar {}
        id: listView
        anchors.fill: parent
        model: listModel

        delegate: ItemMessege {
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: defMargin
            text: model.text
            time: model.time
        }
    }

    
    ListModel { id: listModel }
}
