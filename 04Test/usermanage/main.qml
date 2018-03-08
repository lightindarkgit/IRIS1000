import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Enterprise.VirtualKeyboard 2.0

Window {
    id: root
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")
    property int viewShow:0

    /*
      按照这种方式，在设计界面时就不用考虑旋转的问题了
      */
    Item {
        id: appContainer
        width: Screen.width < Screen.height ? parent.height : parent.width
        height: Screen.width < Screen.height ? parent.width : parent.height
        anchors.centerIn: parent
        rotation: Screen.width < Screen.height ? 270 : 0

        Userlist {
            id: userList
            anchors.fill: parent
            visible: viewShow == 0
        }

        Addperson {
            id: addPerson
            anchors.fill:parent
            visible: viewShow == 1
        }

        Delperson {
            id: delPerson
            anchors.fill: parent
            visible: viewShow == 2
        }

        Editperson {
            id: edtPerson
            anchors.fill: parent
            visible: viewShow == 3
        }

        Userdetails {
            id: userDetail
            anchors.fill: parent
            visible: viewShow == 4
        }

        InputPanel {
            id: inputPanel
            z: 99
            y: appContainer.height
            anchors.left: parent.left
            anchors.right: parent.right
            states: State {
                name: "visible"
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: appContainer.height - inputPanel.height
                }
            }
            transitions: Transition {
                from: ""
                to: "visible"
                reversible: true
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
