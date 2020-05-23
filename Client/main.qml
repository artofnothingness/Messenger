import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// import client.h 1.0

ApplicationWindow {
    id: win
    visible: true
    width: 640
    height: 480

    title: qsTr("Alex Messanger")

    readonly property int defMargin: 10
    readonly property color panelColor: "#17212B"
    readonly property color bubbleColor: "#2b5278"
    readonly property color bgColor: "#0E1621"
    readonly property color textColor: "white"


    function popPage() {
        mainStackView.pop();
    }

    header: ToolBar {
        height: 50
        background: Rectangle {
            anchors.fill: parent
            color: win.panelColor
            Text {
                anchors.centerIn: parent
                color: win.textColor
                font.pointSize: 20
                text: mainStackView.currentItem.title
            }
        }

        ToolButton {
            id: toolButton

            width: 100
            height: parent.height

            visible: mainStackView.depth > 1
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Text {

                text: "<<"
                font.pointSize: 16
                color:  win.textColor
            }

            onClicked: {
                popPage()
            }

            background: Rectangle {
                id: rectTitle
                anchors.fill: parent
                color: win.panelColor
                radius: 5

            }
        }
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: loginPage
    }

    PageLogin {
        id: loginPage
        backGroundColor: bgColor
        title: "Login"
    }

    PageRegistration {
        id: regisPage
        backGroundColor: bgColor
        visible: false
        title: "Registration"
    }

    PageUsers {
        id: usersPage
        backGroundColor: bgColor
        visible : false
        title: "Users"
    }

    PageMesseges {
        id: messagesPage
        backGroundColor: bgColor
        title: "Alex Budyakov"
        visible: false
    }
}
