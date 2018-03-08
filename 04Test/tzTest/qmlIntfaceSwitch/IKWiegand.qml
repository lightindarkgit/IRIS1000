import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Rectangle {
    id: wiegandBackground
    visible: false
    anchors.fill: parent
    color: "#80000000"
    property var currentWiegand:"26"
    property var currentName:tabPositionGroup.current.objectName
    signal itemClicked(bool res,var name)

    MouseArea {
        anchors.fill: parent//
        onClicked:
        {
            //menuRoot.state = "";//非模态时可以这样用
        }
    }
    Rectangle{
        id:wiegandDlg
        width: 1280
        height: 466
        x:0
        y:wiegandBackground.height - wiegandDlg.height

        RowLayout {
            id:rowLayout
            width: wiegandDlg.width
            height: wiegandDlg.height-wiegandDlgBtn1.height
            anchors.top:wiegandDlg.top            
            anchors.left: wiegandDlg.left
            anchors.right: wiegandDlg.right
            ExclusiveGroup {
                id: tabPositionGroup
            }
            RadioButton {
                //                objectName: radio1
                id: radioButton1
                checked: true
                anchors.left: rowLayout.left
                anchors.leftMargin: 118
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup

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
                            id: name1
                            text: qsTr("24")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton1Rec.horizontalCenter
                            anchors.verticalCenter: radioButton1Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "24"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName:",currentName)
                }
            }
            RadioButton {
                id: radioButton2
                anchors.left: rowLayout.left
                anchors.leftMargin: 519
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                //                Layout.minimumWidth: 200

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
                            id: name2
                            text: qsTr("26")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton2Rec.horizontalCenter
                            anchors.verticalCenter: radioButton2Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "26"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName",currentName)
                }
            }
            RadioButton {
                id: radioButton3
                anchors.left: rowLayout.left
                anchors.leftMargin: 920
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                //                Layout.minimumWidth: 200

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton3Rec
                        implicitWidth: 240
                        implicitHeight: 96
                        radius: 10
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name3
                            text: qsTr("禁用")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton3Rec.horizontalCenter
                            anchors.verticalCenter: radioButton3Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "禁用"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }            
        }
        Button {
            id: wiegandDlgBtn1
            anchors.left: wiegandDlg.left
            anchors.bottom: wiegandDlg.bottom
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
                id: wiegandText1
                text: qsTr("取消")
                font.pointSize: 36
                font.bold: true
                color: "#666666"
                anchors.verticalCenter: wiegandDlgBtn1.verticalCenter
                anchors.horizontalCenter: wiegandDlgBtn1.horizontalCenter
            }
            onClicked: {
                emit: itemClicked(false,currentName)
                wiegandBackground.visible = false
                console.log("res: false,",currentName)
            }
        }

        Button {
            id: wiegandDlgBtn2
            anchors.left: wiegandDlgBtn1.right
            anchors.right: wiegandDlg.right
            anchors.bottom: wiegandDlg.bottom
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
                id: verifyText2
                text: qsTr("确定")
                font.pointSize: 36
                font.bold: true
                color: "#5aa5e6"
                anchors.verticalCenter: wiegandDlgBtn2.verticalCenter
                anchors.horizontalCenter: wiegandDlgBtn2.horizontalCenter
            }
            onClicked: {
//                emit: itemClicked(true,currentName)
                currentWiegand = currentName;
                wiegandBackground.visible = false
                console.log("res: true,",currentName)
            }
        }

    }
}

