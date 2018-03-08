import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Rectangle {
    id: verifyBackground
    visible: false
    anchors.fill: parent
    color: "#80000000"
    property var currentVerify:qsTr("虹膜或卡")
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
        id:verifyDlg
        width: 1280
        height: 466
        x:0
        y:verifyBackground.height - verifyDlg.height

        RowLayout {
            id:rowLayout
            width: verifyDlg.width
            height: verifyDlg.height-verifyDlgBtn1.height
            anchors.top:verifyDlg.top            
            anchors.left: verifyDlg.left
            anchors.right: verifyDlg.right
            ExclusiveGroup {
                id: tabPositionGroup
            }
            RadioButton {
                //                objectName: radio1
                id: radioButton1
                checked: true
                anchors.left: rowLayout.left
                anchors.leftMargin: 38
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
                            text: qsTr("虹膜或卡")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton1Rec.horizontalCenter
                            anchors.verticalCenter: radioButton1Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "虹膜或卡"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName:",currentName)
                }
            }
            RadioButton {
                id: radioButton2
                anchors.left: rowLayout.left
                anchors.leftMargin: 359
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
                            text: qsTr("虹膜和卡")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton2Rec.horizontalCenter
                            anchors.verticalCenter: radioButton2Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "虹膜和卡"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName",currentName)
                }
            }
            RadioButton {
                id: radioButton3
                anchors.left: rowLayout.left
                anchors.leftMargin: 680
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
                            text: qsTr("只有虹膜")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton3Rec.horizontalCenter
                            anchors.verticalCenter: radioButton3Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "只有虹膜"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }

            RadioButton {
                id: radioButton4
                anchors.left: rowLayout.left
                anchors.leftMargin: 1001
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                //                Layout.minimumWidth: 200

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton4Rec
                        implicitWidth: 240
                        implicitHeight: 96
                        radius: 10
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name4
                            text: qsTr("只有卡")
                            font.pixelSize:30
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton4Rec.horizontalCenter
                            anchors.verticalCenter: radioButton4Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "只有卡"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }            
        }
        Button {
            id: verifyDlgBtn1
            anchors.left: verifyDlg.left
            anchors.bottom: verifyDlg.bottom
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
                id: verifyText1
                text: qsTr("取消")
                font.pointSize: 36
                font.bold: true
                color: "#666666"
                anchors.verticalCenter: verifyDlgBtn1.verticalCenter
                anchors.horizontalCenter: verifyDlgBtn1.horizontalCenter
            }
            onClicked: {
                emit: itemClicked(false,currentName)
                verifyBackground.visible = false
                console.log("res: false,",currentName)
            }
        }

        Button {
            id: soundRec2Btn2
            anchors.left: verifyDlgBtn1.right
            anchors.right: verifyDlg.right
            anchors.bottom: verifyDlg.bottom
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
                anchors.verticalCenter: soundRec2Btn2.verticalCenter
                anchors.horizontalCenter: soundRec2Btn2.horizontalCenter
            }
            onClicked: {
//                emit: itemClicked(true,currentName)
                currentVerify = currentName;
                verifyBackground.visible = false
                console.log("res: true,",currentName)
            }
        }

    }
}

