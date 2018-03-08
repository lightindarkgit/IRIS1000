import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


Rectangle {
    id: messageBoxBackground    
    visible: false
    anchors.fill: parent
    color: "#80000000"
    property int currentSoundNum:0
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
        id:soundDlg
        width: 1280
        height: 466
        x:0
        y:messageBoxBackground.height - soundDlg.height
        //            rotation: 270

        RowLayout {
            id:rowLayout
            width: soundDlg.width
            height: soundDlg.height-soundRec2Btn1.height
            anchors.top:soundDlg.top
//            anchors.topMargin:106
            anchors.left: soundDlg.left
            anchors.right: soundDlg.right
            ExclusiveGroup {
                id: tabPositionGroup
            }
            RadioButton {
                //                objectName: radio1
                id: radioButton1
                checked: true
                anchors.left: rowLayout.left
                anchors.leftMargin: 52
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton1Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name1
                            text: qsTr("0")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton1Rec.horizontalCenter
                            anchors.verticalCenter: radioButton1Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r1"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName:",currentName)
                }
            }
            RadioButton {
                id: radioButton2
                anchors.left: rowLayout.left
                anchors.leftMargin: 266
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                //                Layout.minimumWidth: 200

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id:radioButton2Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name2
                            text: qsTr("1")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton2Rec.horizontalCenter
                            anchors.verticalCenter: radioButton2Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r2"
                    console.log("current----------:",tabPositionGroup.current.objectName,"currentName",currentName)
                }
            }
            RadioButton {
                id: radioButton3
                anchors.left: rowLayout.left
                anchors.leftMargin: 480
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup
                //                Layout.minimumWidth: 200

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id: radioButton3Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name3
                            text: qsTr("2")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton3Rec.horizontalCenter
                            anchors.verticalCenter: radioButton3Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r3"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }

            RadioButton {
                id: radioButton4
                anchors.left: rowLayout.left
                anchors.leftMargin: 694
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id: radioButton4Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name4
                            text: qsTr("3")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton4Rec.horizontalCenter
                            anchors.verticalCenter: radioButton4Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r4"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }

            RadioButton {
                id: radioButton5
                anchors.left: rowLayout.left
                anchors.leftMargin: 908
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id: radioButton5Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name5
                            text: qsTr("4")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton5Rec.horizontalCenter
                            anchors.verticalCenter: radioButton5Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r5"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }

            RadioButton {
                id: radioButton6
                anchors.left: rowLayout.left
                anchors.leftMargin: 1122
//                anchors.right: rowLayout.right
//                anchors.rightMargin: 52
                anchors.verticalCenter: rowLayout.verticalCenter
                exclusiveGroup: tabPositionGroup

                style: RadioButtonStyle{
                    indicator: Rectangle {
                        id: radioButton6Rec
                        implicitWidth: 106
                        implicitHeight: 106
                        radius: 53
                        color: control.checked ? "#5aa5e6":"#f0f0f0"
                        border.color:"#cccccc"
                        border.width: 1
                        Text {
                            id: name6
                            text: qsTr("5")
                            font.pixelSize:36
                            color: control.checked ? "#ffffff":"#666666"
                            anchors.horizontalCenter: radioButton6Rec.horizontalCenter
                            anchors.verticalCenter: radioButton6Rec.verticalCenter
                        }
                    }
                }
                onClicked: {
                    tabPositionGroup.current.objectName = "r6"
                    console.log("current----------:",tabPositionGroup.current.objectName)
                }
            }            

            Text {
                id: min
                text: qsTr("静音")
                font.pixelSize:24
                color: "#999999"
                anchors.top: radioButton1.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: radioButton1.horizontalCenter

            }
            Text {
                id: max
                text: qsTr("最大")
                font.pixelSize:24
                color: "#999999"
                anchors.top: radioButton6.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: radioButton6.horizontalCenter
            }
        }
        Button {
            id: soundRec2Btn1
            anchors.left: soundDlg.left
            anchors.bottom: soundDlg.bottom
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
                id: soundRec2Text1
                text: qsTr("取消")
                font.pixelSize: 36
                font.bold: true
                color: "#666666"
                anchors.verticalCenter: soundRec2Btn1.verticalCenter
                anchors.horizontalCenter: soundRec2Btn1.horizontalCenter
            }
            onClicked: {
                emit: itemClicked(false,currentName)
                messageBoxBackground.visible = false
                console.log("res: false,",currentName)
            }
        }

        Button {
            id: soundRec2Btn2
            anchors.left: soundRec2Btn1.right
            anchors.right: soundDlg.right
            anchors.bottom: soundDlg.bottom
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
                id: soundRec2Text2
                text: qsTr("确定")
                font.pixelSize: 36
                font.bold: true
                color: "#5aa5e6"
                anchors.verticalCenter: soundRec2Btn2.verticalCenter
                anchors.horizontalCenter: soundRec2Btn2.horizontalCenter
            }
            onClicked: {
                switch(currentName)
                {
                case "r1": currentSoundNum = 0; break;
                case "r2": currentSoundNum = 1; break;
                case "r3": currentSoundNum = 2; break;
                case "r4": currentSoundNum = 3; break;
                case "r5": currentSoundNum = 4; break;
                case "r6": currentSoundNum = 5; break;
                }
//                emit: itemClicked(true,currentSoundNum)
                messageBoxBackground.visible = false
                console.log("res: true,",currentName)
            }
        }

    }
}
