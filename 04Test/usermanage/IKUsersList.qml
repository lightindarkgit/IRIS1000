import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import an.qt.CModel 1.0

Rectangle {
    id: mainRec
    width: 1280
    height: 720

    Rectangle {
        id: title
        anchors.top: parent.top
        width: parent.width
        height: 96
        color: "#626e81"

        TextField {
            id: keyInput
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            style: TextFieldStyle {
                textColor: "#333333"
                font.pixelSize: 30
                background: Rectangle {
                    radius: 10
                    implicitHeight: 64
                    implicitWidth: 800
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 1
                }
            }
        }

        Button {
            id: add
            anchors.top: parent.top
            anchors.topMargin: 28
            anchors.right: del.left
            anchors.rightMargin: 50
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    color: "#626e81"  //设置为底色
                    Image {
                        id: addImg
                        source: control.pressed ? "qrc:///image/add-hover.png" : "qrc:///image/add.png"
                    }
                }
            }

            onClicked: {
                viewShow = 1;
                console.log("viewShow = ", viewShow);
            }
        }

        Button {
            id: del
            anchors.top: parent.top
            anchors.topMargin: 28
            anchors.right: home.left
            anchors.rightMargin: 50
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    color: "#626e81"  //设置为底色
                    Image {
                        id: delImg
                        source: control.pressed ? "qrc:///image/delete-hover.png" : "qrc:///image/delete.png"
                    }
                }
            }

            onClicked: {
                viewShow = 2;
                console.log("viewShow = ", viewShow);
            }
        }

        Button {
            id: home
            anchors.top: parent.top
            anchors.topMargin: 28
            anchors.right: parent.right
            anchors.rightMargin: 30
            style: ButtonStyle {
                background: Rectangle{
                    implicitWidth: 40
                    implicitHeight: 40
                    color: "#626e81"  //设置为底色
                    Image {
                        id: homeImg
                        source: control.pressed ? "qrc:///image/home-hover.png" : "qrc:///image/home.png"
                    }
                }
            }

            onClicked: {

            }
        }
    }

    Rectangle {
        id: body
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Component {
            id: userDelegate
            Item {
                id: wrapper
                width: parent.width
                height: 104

                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                        viewShow = 3;
                        console.log("viewShow = ", viewShow);
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    color: wrapper.ListView.isCurrentItem ? "#e9e9e9" : "#f0f0f0";
                    border.color: "#e9e9e9"
                    border.width: 2
                    Image {
                        width: 28
                        height: 48
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:///image/right.png"
                    }
                    RowLayout {
                        anchors.left: parent.left;
                        anchors.verticalCenter: parent.verticalCenter;
                        Text {
                            id: userName
                            text: username
                            color: "#333333"
                            font.pixelSize: 36
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            Layout.minimumWidth: 36
                        }
                        Text {
                            id: userId
                            text: userid
                            color: "#666666"
                            font.pixelSize: 36
                            anchors.left: userName.right
                            anchors.leftMargin: 10
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }

        ListView {
            id: userlist
            anchors.fill: parent
            delegate: userDelegate
            model: UserListModel { source: "users.xml"}
            clip: true      //此属性的默认值是false，表示不会自动截掉超出显示区域的部分
            focus: true
        }
    }
}
