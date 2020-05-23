import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: pageUsers

    property alias backGroundColor: backGroundRect.color
    background: Rectangle {
        id: backGroundRect
    }

    Keys.onEscapePressed: {
        popPage();
    }

    ListView {
        spacing: defMargin
        anchors.topMargin: 10
        ScrollBar.vertical: ScrollBar {}
        id: listViewUsers
        anchors.fill: parent
        model: listModel

        delegate: ItemUser {
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top : parent.top
            anchors.margins: defMargin
            text: model.text
        }
    }

    ListModel {
        id: listModel
        ListElement{
            text: qsTr("SOME USER")
        }
    }
}
