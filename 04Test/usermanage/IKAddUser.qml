import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: addperson
    width: 1280
    height: 720

    Rectangle {
        id: title
        anchors.top: parent.top
        width: parent.width
        height: 96
        color: "#626e81"

        Label {
            id: pageTitle
            text: qsTr("添加用户")
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 40
            color: "#ffffff"
        }

        Button {
            id: backBtn
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 50
                    implicitHeight: 43
                    color: "#626e81"  //设置为底色
                    Image {
                        id: backImg
                        source: control.pressed ? "qrc:///image/back-hover.png" : "qrc:///image/back.png"
                    }
                }
            }
            onClicked: {
                viewShow  = 0;
                console.log("viewShow = ", viewShow);
            }
        }
    }

    property int tabView:0

    Rectangle {
        id: body
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#33363a"

        Label {
            id: userId
            text: qsTr("用户ID")
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 30
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        TextField {
            id: idInput
            anchors.top: userId.bottom
            anchors.topMargin: 10
            anchors.left: userId.left
            style: TextFieldStyle {
                textColor: "#ffffff"
                font.pixelSize: 36
                background: Rectangle {
                    radius: 10
                    implicitHeight: 64
                    implicitWidth: 460
                    color: "#262626"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                }
            }
        }

        Label {
            id: userName
            text: qsTr("用户名")
            anchors.top: idInput.bottom
            anchors.topMargin: 50
            anchors.left: userId.left
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        TextField {
            id: nameInput
            anchors.top: userName.bottom
            anchors.topMargin: 10
            anchors.left: userId.left
            style: TextFieldStyle {
                textColor: "#ffffff"
                font.pixelSize: 36
                background: Rectangle {
                    radius: 10
                    implicitHeight: 64
                    implicitWidth: 460
                    color: "#262626"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                }
            }
        }

        Button {
            id: moreInfo
            anchors.top: nameInput.bottom
            anchors.topMargin: 10
            anchors.right: nameInput.right
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 24
                    implicitWidth: 100
                    color: "#33363a"
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("填写更多")
                        color: "#ffc600"
                        font.pixelSize: 24
                    }
                }
            }
            onClicked: {
                viewShow = 4;
                console.log("viewShow = ", viewShow);
            }
        }

        Label {
            id: admin
            text: qsTr("管理员")
            anchors.top: nameInput.bottom
            anchors.topMargin: 70
            anchors.left: userId.left
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        CheckBox {
            id: isAdmin
            anchors.top: admin.bottom
            anchors.topMargin: 10
            anchors.left: admin.left
            style: checkStyle
        }

        Label {
            id: single
            text: qsTr("采集单眼")
            anchors.top: nameInput.bottom
            anchors.topMargin: 70
            anchors.right: nameInput.right
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        CheckBox {
            id: isSingle
            anchors.top: single.bottom
            anchors.topMargin: 10
            anchors.left: single.left
            style: checkStyle
        }

        Label {
            id: verInfo
            text: qsTr("验证信息")
            anchors.top: userId.top
            anchors.left: idInput.right
            anchors.leftMargin: 140
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        Button {
            id: iris
            anchors.top: idInput.top
            anchors.left: idInput.right
            anchors.leftMargin: 140
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 0) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("虹膜")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView = 0
            }
        }

        Button {
            id: card
            anchors.top: idInput.top
            anchors.left: iris.right
            anchors.leftMargin: 11
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 1) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("卡")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView = 1
            }
        }

        Button {
            id: passwd
            anchors.top: idInput.top
            anchors.left: card.right
            anchors.leftMargin: 11
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 2) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("密码")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView =  2
            }
        }

        Rectangle {
            width: 610
            height: 340
            anchors.top: iris.bottom
            anchors.left: iris.left
            border.color: Qt.rgba(204,204,204,0.7)
            border.width: 2
            radius: 10

            Rectangle {
                id: irisView
                width: 610
                height: 340
                visible: (tabView == 0) ? true : false
                anchors.fill: parent
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10

                Button {
                    anchors.centerIn: parent
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 96
                            implicitHeight: 96
                            color: "#262626"  //设置为底色
                            Image {
                                source: control.pressed ? "qrc:///image/user-add-hover.png" : "qrc:///image/user-add.png"
                            }
                        }
                    }
                }
            }
            Rectangle {
                id: cardView
                width: 610
                height: 340
                visible: (tabView == 1) ? true : false
                anchors.fill: parent
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10

                Label {
                    text: qsTr("请刷卡")
                    anchors.centerIn: parent
                    font.pixelSize: 36
                    color: Qt.rgba(255,255,255,0.7)
                }
            }
            Rectangle {
                id: pswdView
                width: 610
                height: 340
                visible: (tabView == 2) ? true : false
                anchors.fill: parent
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10

                TextField {
                    id: firstPswd
                    anchors.top: parent.top
                    anchors.topMargin: 84
                    anchors.left: parent.left
                    anchors.leftMargin: 105
                    style: TextFieldStyle {
                        textColor: Qt.rgba(255,255,255,0.5)
                        font.pixelSize: 24
                        background: Rectangle {
                            radius: 10
                            implicitHeight: 60
                            implicitWidth: 400
                            color: Qt.rgba(102,102,102,0.3)
                            border.color: Qt.rgba(204,204,204,0.7)
                            border.width: 2
                        }
                    }
                }
                TextField {
                    id: secondPswd
                    anchors.top: firstPswd.bottom
                    anchors.topMargin: 50
                    anchors.left: parent.left
                    anchors.leftMargin: 105
                    style: TextFieldStyle {
                        textColor: Qt.rgba(255,255,255,0.5)
                        font.pixelSize: 24
                        background: Rectangle {
                            radius: 10
                            implicitHeight: 60
                            implicitWidth: 400
                            color: Qt.rgba(102,102,102,0.3)
                            border.color: Qt.rgba(204,204,204,0.7)
                            border.width: 2
                        }
                    }
                }
            }
        }
    }

    Button {
        id: cancelBtn
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 96
                implicitWidth: 640
                color: "#262626"
                border.color: "#cccccc"
                border.width: 1
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("取消")
                    color: control.pressed ? Qt.rgba(255,255,255, 0.5) :Qt.rgba(255,255,255,0.7)
                    font.pixelSize: 36
                }
            }
        }
    }

    Button {
        id: ensureBtn
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 96
                implicitWidth: 640
                color: "#262626"
                border.color: "#cccccc"
                border.width: 1
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("完成")
                    color:  "#5aa5e6"
                    opacity: control.pressed ? 0.7 : 1.0
                    font.pixelSize: 36
                }
            }
        }
    }

    Component {
        id: checkStyle
        CheckBoxStyle {
            indicator: Rectangle {
                implicitHeight: 64
                implicitWidth: 64
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10
                Image {
                    visible: control.checked
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:///image/check.png"
                }
            }
        }
    }
}
