import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---数据管理
Rectangle {
    id:dateManegerment
    width: 1280
    height: 720

    IKTopBar{
        id:dateManegermentTopRect
        topText: "数据管理"
    }
    Button {
        id: userIOBtn
        anchors.top: dateManegermentTopRect.bottom
        anchors.left: dateManegerment.left
        smooth: true
        property var userIOBtnColor: "#e9e9e9"
        property var userIOBtnBorderColor: "#cccccc"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:userIOBtn.userIOBtnColor
                border.color: userIOBtn.userIOBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: userIOBtnText
            text: qsTr("人员导入/导出")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: userIOBtn.verticalCenter
            anchors.left: userIOBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userIORec.visible = true
            otherORec.visible = false

            userIOBtn.userIOBtnColor = "#e9e9e9"
            userIOBtn.userIOBtnBorderColor = "#cccccc"
            userIOBtnText.color = "#5aa5e6"

            idenRecordOBtn.idenRecordOBtnBtnColor = "#cacbca"
            idenRecordOBtn.idenRecordOBtnBorderColor = "#aaaaaa"
            idenRecordOBtnBtnColorText.color = "#666666"

            doubtPersonOBtn.doubtPersonOBtnColor = "#cacbca"
            doubtPersonOBtn.doubtPersonOBtnBorderColor = "#aaaaaa"
            doubtPersonOBtnText.color = "#666666"

            logOBtn.logOBtnColor = "#cacbca"
            logOBtn.logOBtnBorderColor = "#aaaaaa"
            logOBtnText.color = "#666666"
            dateManegermentOutputBtn1.visible = true
            dateManegermentInputBtn.visible = true
            dateManegermentOutputBtn.visible = false

        }
    }
    Button {
        id: idenRecordOBtn
        anchors.top: userIOBtn.bottom
        anchors.left: dateManegerment.left
        smooth: true
        property var idenRecordOBtnBtnColor: "#cacbca"
        property var idenRecordOBtnBorderColor: "#aaaaaa"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:idenRecordOBtn.idenRecordOBtnBtnColor
                border.color: idenRecordOBtn.idenRecordOBtnBtnColor
                border.width: 1
            }
        }
        Text {
            id: idenRecordOBtnBtnColorText
            text: qsTr("识别记录导出")
            font.pixelSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: idenRecordOBtn.verticalCenter
            anchors.left: idenRecordOBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userIORec.visible = false
            otherORec.visible = true

            userIOBtn.userIOBtnColor = "#cacbca"
            userIOBtn.userIOBtnBorderColor = "#aaaaaa"
            userIOBtnText.color = "#666666"

            idenRecordOBtn.idenRecordOBtnBtnColor = "#e9e9e9"
            idenRecordOBtn.idenRecordOBtnBorderColor = "#cccccc"
            idenRecordOBtnBtnColorText.color = "#5aa5e6"

            doubtPersonOBtn.doubtPersonOBtnColor = "#cacbca"
            doubtPersonOBtn.doubtPersonOBtnBorderColor = "#aaaaaa"
            doubtPersonOBtnText.color = "#666666"

            logOBtn.logOBtnColor = "#cacbca"
            logOBtn.logOBtnBorderColor = "#aaaaaa"
            logOBtnText.color = "#666666"

            dateManegermentOutputBtn1.visible = false
            dateManegermentInputBtn.visible = false
            dateManegermentOutputBtn.visible = true
        }
    }
    Button {
        id: doubtPersonOBtn
        anchors.top: idenRecordOBtn.bottom
        anchors.left: dateManegerment.left
        smooth: true
        property var doubtPersonOBtnColor: "#cacbca"
        property var doubtPersonOBtnBorderColor: "#cccccc"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:doubtPersonOBtn.doubtPersonOBtnColor
                border.color: doubtPersonOBtn.doubtPersonOBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: doubtPersonOBtnText
            text: qsTr("存疑人员导出")
            font.pixelSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: doubtPersonOBtn.verticalCenter
            anchors.left: doubtPersonOBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userIORec.visible = false
            otherORec.visible = true


            userIOBtn.userIOBtnColor = "#cacbca"
            userIOBtn.userIOBtnBorderColor = "#aaaaaa"
            userIOBtnText.color = "#666666"

            idenRecordOBtn.idenRecordOBtnBtnColor = "#cacbca"
            idenRecordOBtn.idenRecordOBtnBorderColor = "#aaaaaa"
            idenRecordOBtnBtnColorText.color = "#666666"

            doubtPersonOBtn.doubtPersonOBtnColor = "#e9e9e9"
            doubtPersonOBtn.doubtPersonOBtnBorderColor = "#cccccc"
            doubtPersonOBtnText.color = "#5aa5e6"

            logOBtn.logOBtnColor = "#cacbca"
            logOBtn.logOBtnBorderColor = "#aaaaaa"
            logOBtnText.color = "#666666"

            dateManegermentOutputBtn1.visible = false
            dateManegermentInputBtn.visible = false
            dateManegermentOutputBtn.visible = true
        }
    }
    Button {
        id: logOBtn
        anchors.top: doubtPersonOBtn.bottom
        anchors.left: dateManegerment.left
        smooth: true
        property var logOBtnColor: "#cacbca"
        property var logOBtnBorderColor: "#aaaaaa"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:logOBtn.logOBtnColor
                border.color: logOBtn.logOBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: logOBtnText
            text: qsTr("日志导出")
            font.pixelSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: logOBtn.verticalCenter
            anchors.left: logOBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userIORec.visible = false
            otherORec.visible = true


            userIOBtn.userIOBtnColor = "#cacbca"
            userIOBtn.userIOBtnBorderColor = "#aaaaaa"
            userIOBtnText.color = "#666666"

            idenRecordOBtn.idenRecordOBtnBtnColor = "#cacbca"
            idenRecordOBtn.idenRecordOBtnBorderColor = "#aaaaaa"
            idenRecordOBtnBtnColorText.color = "#666666"

            doubtPersonOBtn.doubtPersonOBtnColor = "#cacbca"
            doubtPersonOBtn.doubtPersonOBtnBorderColor = "#aaaaaa"
            doubtPersonOBtnText.color = "#666666"

            logOBtn.logOBtnColor = "#e9e9e9"
            logOBtn.logOBtnBorderColor = "#cccccc"
            logOBtnText.color = "#5aa5e6"

            dateManegermentOutputBtn1.visible = false
            dateManegermentInputBtn.visible = false
            dateManegermentOutputBtn.visible = true
        }
    }
    Button {
        id: nullBtn1
        anchors.top: logOBtn.bottom
        anchors.left: dateManegerment.left
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:"#cacbca"
                border.color: "#aaaaaa"
                border.width: 1
            }
        }
    }


    Rectangle{
        id:userIORec
        anchors.top: dateManegermentTopRect.bottom
        anchors.left: userIOBtn.right
        anchors.right: dateManegerment.right
        width: 782
        height: 520
        visible: true
        color: "#f0f0f0"

        ProgressBar{
            id:userIOProgress
            anchors.top: userIORec.top
            anchors.topMargin: 100
            anchors.left: userIORec.left
            anchors.leftMargin: 85
            width: 800
            height: 56
            minimumValue: 0;
            maximumValue: 100;
            value: 33;

            style: ProgressBarStyle{
                id: progressStyle;
                background: Rectangle{
                    color:"#ffffff";
                    opacity: 0.5
                    radius: 28
                }

                progress: Rectangle{
                    id: proRec
                    color:"#ffc600";
                    radius: 28
                    Text{
                        color: "#ffffff";
                        font.pixelSize: 28
                        text:userIOProgress.value + "%";
                        anchors.centerIn: parent;
                    }
                }
            }


        }

        Text {
            id: userIOText1
            text: qsTr("导入说明")
            font.pixelSize: 28
            color: "#333333"
            anchors.top:userIOProgress.bottom
            anchors.topMargin: 94
            anchors.left: userIORec.left
            anchors.leftMargin: 86
        }
        Text {
            id: userIOText2
            text: qsTr("请插入已存放了人员信息的u盘，并点击导入按钮。")
            font.pixelSize: 28
            color: "#999999"
            anchors.top:userIOText1.bottom
            anchors.topMargin: 20
            anchors.left: userIORec.left
            anchors.leftMargin: 86
        }
        Text {
            id: userIOText3
            text: qsTr("导出说明")
            font.pixelSize: 28
            color: "#333333"
            anchors.top:userIOText2.bottom
            anchors.topMargin: 50
            anchors.left: userIORec.left
            anchors.leftMargin: 86
        }
        Text {
            id: userIOText4
            text: qsTr("请插入u盘，并点击导出按钮")
            font.pixelSize: 28
            color: "#999999"
//            anchors.top:userIOText3.bottom
//            anchors.topMargin: 20
            anchors.left: userIORec.left
            anchors.leftMargin: 86
            anchors.bottom: userIORec.bottom
            anchors.bottomMargin: 78
        }
    }
    Rectangle{
        id:otherORec
        anchors.top: dateManegermentTopRect.bottom
        anchors.left: userIOBtn.right
        anchors.right: dateManegerment.right
        width: 782
        height: 520
        visible: false
        color: "#f0f0f0"

        ProgressBar{
            id:otherOProgress
            anchors.top: otherORec.top
            anchors.topMargin: 100
            anchors.left: otherORec.left
            anchors.leftMargin: 85
            width: 800
            height: 56
            minimumValue: 0;
            maximumValue: 100;
            value: 33;

            style: ProgressBarStyle{
                id: otherORecProgressStyle;
                background: Rectangle{
                    color:"#ffffff";
                    opacity: 0.5
                    radius: 28
                }

                progress: Rectangle{
                    color:"#ffc600";
                    radius: 28
                    Text{
                        color: "#ffffff";
                        font.pixelSize: 28
                        text:otherOProgress.value+ "%";
                        anchors.centerIn: parent
                    }
                }
            }


        }

        Text {
            id: otherOText1
            text: qsTr("导出说明")
            font.pixelSize: 28
            color: "#333333"
            anchors.top:otherOProgress.bottom
            anchors.topMargin: 94
            anchors.left: otherORec.left
            anchors.leftMargin: 86
        }
        Text {
            id: otherOText2
            text: qsTr("请插入u盘，并点击导出按钮。")
            font.pixelSize: 28
            color: "#999999"
            anchors.top:otherOText1.bottom
            anchors.topMargin: 20
            anchors.left: otherORec.left
            anchors.leftMargin: 86
        }
    }

    Button {
        id: dateManegermentInputBtn
        visible: true
        anchors.right: dateManegermentOutputBtn1.left
        anchors.left: dateManegerment.left
        anchors.bottom: dateManegerment.bottom
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
            text: qsTr("导入")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: dateManegermentInputBtn.verticalCenter
            anchors.horizontalCenter: dateManegermentInputBtn.horizontalCenter
        }
        onClicked: {

        }
    }

    Button {
        id: dateManegermentOutputBtn1
        visible: true
        anchors.right: dateManegerment.right
        anchors.bottom: dateManegerment.bottom
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
            id: soundRec2Text3
            text: qsTr("导出")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: dateManegermentOutputBtn1.verticalCenter
            anchors.horizontalCenter: dateManegermentOutputBtn1.horizontalCenter
        }
        onClicked: {

        }
    }


    Button {
        id: dateManegermentOutputBtn
        visible: false
        anchors.right: dateManegerment.right
        anchors.left: dateManegerment.left
        anchors.bottom: dateManegerment.bottom
        smooth: true        
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 1280
                implicitHeight: 104
                color:"#f0f0f0"
                border.color: "#cccccc"
                border.width: 1
            }
        }
        Text {
            id: soundRec2Text4
            text: qsTr("导出")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: dateManegermentOutputBtn.verticalCenter
            anchors.horizontalCenter: dateManegermentOutputBtn.horizontalCenter
        }
        onClicked: {

        }
    }
}

