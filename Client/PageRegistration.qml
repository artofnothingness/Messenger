import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// import client.h 1.0
Page {
    id: pageLogin

    property alias backGroundColor: backGroundRect.color
    background: Rectangle {
        id: backGroundRect
    }

    Keys.onEscapePressed: {
        popPage();
    }

    ColumnLayout {
        id:loGeneral
        anchors.fill: parent
        anchors.margins: defMargin
        spacing: defMargin

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.minimumHeight: 200
            Label {
                text: "Some information about you"
                font.pointSize: 14
                font.bold: true
                color: textColor
            }
            Item {
                height: 20
            }
            Label {
                text: "Username"
            }
            TextField {
                placeholderText: "Enter username"
                selectByMouse: true
                Layout.fillWidth: true
            }
            Label {
                text: "Password"
            }
            TextField {
                selectByMouse: true
                echoMode: TextInput.Password
                placeholderText: "Enter Password"
                Layout.fillWidth: true
            }
            Item {
                Layout.fillHeight: true;
            }
        }

        RowLayout {
            Item {
                Layout.fillWidth: true
            }

            MainButton {
                id: loginButton
                buttonText: "Confirm"
                width: 100
                onButtonClicked: {
                    mainStackView.pop(loginPage)
                }
            }
        }
    }
}

