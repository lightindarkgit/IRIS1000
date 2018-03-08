import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

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

        TextField {
            id: keyInput
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
            style: TextFieldStyle {
                textColor: "#333333"
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
            id: ensureBtn
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 36
                    implicitWidth: 75
                    color: "#626e81"  //设置为底色
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
            onClicked: {
                userManager.idListDelete(); // 在数据库中删除用户
                viewShow  = 11;
                console.log("viewShow = ", viewShow);
            }
        }

        Button {
            id: cancelBtn
            anchors.right: ensureBtn.left
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 36
                    implicitWidth: 75
                    color: "#626e81"  //设置为底色
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("取消")
                        color: control.pressed ? Qt.rgba(255,255,255, 0.5) :Qt.rgba(255,255,255,0.7)
                        font.pixelSize: 36
                    }
                }
            }
            onClicked: {
                userManager.idListClear();  // 取消删除，则清空待删除用户id列表，不执行删除操作
                userModel.reload(); // 重新加载用户
                viewShow  = 11; // 切换回现实用户列表
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
                    }
                }

                Rectangle {
                    anchors.fill: parent
                    color: wrapper.ListView.isCurrentItem ? "#e9e9e9" : "#f0f0f0";
                    border.color: "#e9e9e9"
                    border.width: 2
                    Button {
                        id: delBtn
                        anchors.right: parent.right
                        anchors.rightMargin: 30
                        anchors.verticalCenter: parent.verticalCenter
                        style: ButtonStyle {
                            background: Rectangle {
                                implicitWidth: 60
                                implicitHeight: 104
                                color: wrapper.ListView.isCurrentItem ? "#e9e9e9" : "#f0f0f0";
                                Label {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("删除")
                                    color:  "#d8293b"
                                    opacity: control.pressed ? 0.7 : 1.0
                                    font.pixelSize: 30
                                }
                            }
                        }
                        onClicked: {
                            wrapper.ListView.view.currentIndex = index;
                            userManager.idListAdd(userModel.getUserId(index));  // 根据索引id，将用户id加入带删除列表
                            wrapper.ListView.view.model.remove(index);
                        }
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
            model: userModel
            clip: true      //此属性的默认值是false，表示不会自动截掉超出显示区域的部分
            focus: true
        }
    }
}
