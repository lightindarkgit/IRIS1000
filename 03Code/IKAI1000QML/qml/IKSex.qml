import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: sexBackground
    visible: false
    anchors.fill: parent
    color: "#80000000"

//    property  string sexstr: "未填写"
    property bool isMale: (userManager.sex === "男" || userManager.sex === "") ? true : false;// 此处中文相等，需要注意多语言的处理

    MouseArea {
        anchors.fill: parent
        onClicked: {
        }
    }
    Rectangle {
        id:sexDlg
        width: 1280
        height: 466
        x:0
        y:sexBackground.height - sexDlg.height

        RowLayout {
            id:rowLayout
            width: sexDlg.width
            height: sexDlg.height-cancelBtn.height
            anchors.top:sexDlg.top
            anchors.left: sexDlg.left
            anchors.right: sexDlg.right
            ExclusiveGroup {
                id: tabPositionGroup
            }
            RadioButton {
                id: rdBtnMale
//                checked: true
                anchors.left: rowLayout.left
                anchors.leftMargin: 200
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                checked: isMale;

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton1Rec
                        implicitWidth: 240
                        implicitHeight: 96
                        radius: 10
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            text: qsTr("男")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton1Rec.horizontalCenter
                            anchors.verticalCenter: radioButton1Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "男"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }
            RadioButton {
                id: rdBtnFemale
                anchors.right: rowLayout.right
                anchors.rightMargin: 200
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                checked: !isMale;

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton2Rec
                        implicitWidth: 240
                        implicitHeight: 96
                        radius: 10
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            text: qsTr("女")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton2Rec.horizontalCenter
                            anchors.verticalCenter: radioButton2Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "女"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }
        }
        Button {
            id: cancelBtn
            anchors.left: sexDlg.left
            anchors.bottom: sexDlg.bottom
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 640
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                text: qsTr("取消")
                font.pixelSize: 36
                font.bold: true
                color: "#666666"
                anchors.verticalCenter: cancelBtn.verticalCenter
                anchors.horizontalCenter: cancelBtn.horizontalCenter
            }
            onClicked: {
                sexBackground.visible = false
            }
        }

        Button {
            id: ensureBtn
            anchors.left: cancelBtn.right
            anchors.right: sexDlg.right
            anchors.bottom: sexDlg.bottom
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 640
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                text: qsTr("确定")
                font.pixelSize: 36
                font.bold: true
                color: "#5aa5e6"
                anchors.verticalCenter: ensureBtn.verticalCenter
                anchors.horizontalCenter: ensureBtn.horizontalCenter
            }
            onClicked: {
                sexBackground.visible = false;
                if(tabPositionGroup.current.objectName == "")
                    userManager.sex = "男";
                else
//                    sexstr = tabPositionGroup.current.objectName;
                    userManager.sex = tabPositionGroup.current.objectName;
            }
        }
    }
}
