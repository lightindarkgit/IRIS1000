import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: delperson
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
            text: qsTr("个人信息")
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
                viewShow  = 1;
                console.log("viewShow = ", viewShow);
            }
        }
    }

    Rectangle {
        id: body
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Button {
            id: cancelBtn
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 96
                    implicitWidth: 640
                    color: "#ffffff"
                    border.color: "#cccccc"
                    border.width: 1
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("取消")
                        color:  "#666666"
                        opacity: control.pressed ? 0.5 : 0.7
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
                    color: "#ffffff"
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
    }
}
