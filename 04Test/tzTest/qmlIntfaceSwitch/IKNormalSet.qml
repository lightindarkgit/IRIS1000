import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---基本设置
Rectangle {
    id:basicSet
    width: 1280
    height: 720
    property string nomerPic: "qrc:///res/image/userlist/right.png"
    property string activePic: "qrc:///res/image/userlist/right_hover.png"
    //背景图片    
    Image {
        id: rocket
        fillMode: Image.TileHorizontally
        smooth: true
        source: "qrc:///res/image/setImage/user_bg.png"
    }

    IKTopBar{
        id:topRect
        topText: "基本设置"
    }
    Button {
        id: soundBtn
        anchors.top: topRect.bottom
        anchors.left: basicSet.left
        smooth: true
        property var soundBtnColor: "#e9e9e9"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:soundBtn.soundBtnColor
                border.color: "#cccccc"
                border.width: 1
            }
        }
        Text {
            id: soundBtnText
            text: qsTr("声音")
            font.pointSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: soundBtn.verticalCenter
            anchors.left: soundBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            soundRec.visible = true
            dateRec.visible = false
            sysInfoRec.visible = false

            soundBtnText.color = "#5aa5e6"
            soundBtn.soundBtnColor = "#e9e9e9"

            dateBtnText.color = "#666666"
            dateBtn.dateBtnColor = "#cacbca"

            sysInfoBtnText.color = "#666666"
            sysInfoBtn.sysInfoBtnColor = "#cacbca"
        }
    }
    Button {
        id: dateBtn
        anchors.top: soundBtn.bottom
        anchors.left: basicSet.left
        smooth: true
        property var dateBtnColor: "#cacbca"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:dateBtn.dateBtnColor
                border.color: "#aaaaaa"
                border.width: 1
            }
        }
        Text {
            id: dateBtnText
            text: qsTr("日期时间")
            font.pointSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: dateBtn.verticalCenter
            anchors.left: dateBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            soundRec.visible = false
            dateRec.visible = true
            sysInfoRec.visible = false

            soundBtnText.color = "#666666"
            soundBtn.soundBtnColor = "#cacbca"

            dateBtnText.color = "#5aa5e6"
            dateBtn.dateBtnColor = "#e9e9e9"

            sysInfoBtnText.color = "#666666"
            sysInfoBtn.sysInfoBtnColor = "#cacbca"
        }
    }
    Button {
        id: sysInfoBtn
        anchors.top: dateBtn.bottom
        anchors.left: basicSet.left
        smooth: true
        property var sysInfoBtnColor: "#cacbca"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:sysInfoBtn.sysInfoBtnColor
                border.color: "#aaaaaa"
                border.width: 1
            }
        }
        Text {
            id: sysInfoBtnText
            text: qsTr("系统信息")
            font.pointSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: sysInfoBtn.verticalCenter
            anchors.left: sysInfoBtn.left
            anchors.leftMargin: 30

        }
        onClicked:{
            dateBtnText.color = "#666666"
            dateBtn.dateBtnColor = "#cacbca"

            soundBtnText.color = "#666666"
            soundBtn.soundBtnColor = "#cacbca"

            sysInfoBtnText.color = "#5aa5e6"
            sysInfoBtn.sysInfoBtnColor = "#e9e9e9"

            soundRec.visible = false
            dateRec.visible = false
            sysInfoRec.visible = true
        }
    }
    Button {
        id: nullBtn1
        anchors.top: sysInfoBtn.bottom
        anchors.left: basicSet.left
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
    Button {
        id: nullBtn2
        anchors.top: nullBtn1.bottom
        anchors.left: basicSet.left
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
    Button {
        id: nullBtn3
        anchors.top: nullBtn2.bottom
        anchors.left: basicSet.left
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
        id:soundRec
        anchors.top: topRect.bottom
        anchors.left: soundBtn.right
        anchors.right: basicSet.right
        width: 782
        height: 312
        visible: true

        Button {
            id: soundBtn1
            anchors.top: soundRec.top
            anchors.right: soundRec.right
            anchors.left: soundRec.left
            smooth: true
            property bool m_soundBtn1_soundImg1: true;
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                id: soundBtnText1
                text: qsTr("按键音")
                font.pointSize: 36
                font.bold: true
                color: "#333333"
                anchors.verticalCenter: soundBtn1.verticalCenter
                anchors.left: soundBtn1.left
                anchors.leftMargin: 50
            }
            Image {
                id: soundImg1
                anchors.verticalCenter: soundBtn1.verticalCenter
                anchors.right: soundBtn1.right
                anchors.rightMargin: 30
                width: 88
                height: 62
                fillMode: Image.TileHorizontally
                smooth: true
                source: "qrc:///res/image/userlist/element_select_open.png"
            }

            onClicked:{
                if(m_soundBtn1_soundImg1)
                {
                    soundImg1.source = "qrc:///res/image/userlist/element_select_off.png"
                    m_soundBtn1_soundImg1 = false;
                }
                else
                {
                    soundImg1.source = "qrc:///res/image/userlist/element_select_open.png"
                    m_soundBtn1_soundImg1 = true;
                }
            }
        }
        Button {
            id: soundBtn2
            anchors.top: soundBtn1.bottom
            anchors.right: soundRec.right
            anchors.left: soundRec.left
            smooth: true
            property bool m_soundBtn2_soundImg2: false;
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                id: soundBtnText2
                text: qsTr("语音提示")
                font.pointSize: 36
                font.bold: true
                color: "#333333"
                anchors.verticalCenter: soundBtn2.verticalCenter
                anchors.left: soundBtn2.left
                anchors.leftMargin: 50
            }
            Image {
                id: soundImg2
                anchors.verticalCenter: soundBtn2.verticalCenter
                anchors.right: soundBtn2.right
                anchors.rightMargin: 30
                width: 88
                height: 62
                fillMode: Image.TileHorizontally
                smooth: true
                source: "qrc:///res/image/userlist/element_select_off.png"
            }

            onClicked:{
                if(m_soundBtn2_soundImg2)
                {
                    soundImg2.source = "qrc:///res/image/userlist/element_select_off.png"
                    m_soundBtn2_soundImg2 = false;
                }
                else
                {
                    soundImg2.source = "qrc:///res/image/userlist/element_select_open.png"
                    m_soundBtn2_soundImg2 = true;
                }
            }
        }

        Button {
            id: soundBtn3
            anchors.top: soundBtn2.bottom
            anchors.right: soundRec.right
            anchors.left: soundRec.left
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    id:soundBtn3Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: soundBtnText3
                        text: qsTr("音量")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: soundBtn3Rec.verticalCenter
                        anchors.left: soundBtn3Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: soundBtnText4
                        text: iKVolume.currentSoundNum.toString()
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: soundBtn3Rec.verticalCenter
                        anchors.right: soundImg3.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: soundImg3
                        anchors.verticalCenter: soundBtn3Rec.verticalCenter
                        anchors.right: soundBtn3Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }

        onClicked:{
            iKVolume.visible = true
        }
        }
    }

    Rectangle{
        id:dateRec
        anchors.top: topRect.bottom
        anchors.left: soundBtn.right
        anchors.right: basicSet.right
        width: 782
        height: 312
        visible: false

        Button {
            id: dateBtn1
            anchors.top: dateRec.top
            anchors.right: dateRec.right
            anchors.left: dateRec.left
            smooth: true
            property bool m_dateBtn1_dateImg1: true;
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                id: dateBtn1Text1
                text: qsTr("联网自动更新")
                font.pointSize: 36
                font.bold: true
                color: "#333333"
                anchors.verticalCenter: dateBtn1.verticalCenter
                anchors.left: dateBtn1.left
                anchors.leftMargin: 50
            }
            Image {
                id: dateImg1
                anchors.verticalCenter: dateBtn1.verticalCenter
                anchors.right: dateBtn1.right
                anchors.rightMargin: 30
                width: 88
                height: 62
                fillMode: Image.TileHorizontally
                smooth: true
                source: "qrc:///res/image/userlist/element_select_open.png"
            }

            onClicked:{
                if(m_dateBtn1_dateImg1)
                {
                    dateImg1.source = "qrc:///res/image/userlist/element_select_off.png"
                    m_dateBtn1_dateImg1 = false;
                    dateBtnText3.color = "#999999"
                    dateBtnText5.color = "#999999"
                }
                else
                {
                    dateImg1.source = "qrc:///res/image/userlist/element_select_open.png"
                    m_dateBtn1_dateImg1 = true;
                    dateBtnText3.color = "#666666"
                    dateBtnText5.color = "#666666"
                }
            }
        }
        Button {
            id: dateBtn2
            anchors.top: dateBtn1.bottom
            anchors.right: dateRec.right
            anchors.left: dateRec.left
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    id:dateBtn2Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: dateBtnText2
                        text: qsTr("日期")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: dateBtn2Rec.verticalCenter
                        anchors.left: dateBtn2Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: dateBtnText3
                        text: ikDate.currentData.toString()
                        font.pointSize: 36
                        font.bold: true
                        color: "#999999"
                        anchors.verticalCenter: dateBtn2Rec.verticalCenter
                        anchors.right: dataImg2.left
                        anchors.rightMargin:  30
                    }
                    Image {
                        id: dataImg2
                        anchors.verticalCenter: dateBtn2Rec.verticalCenter
                        anchors.right: dateBtn2Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }


            onClicked:{
                ikDate.visible = true
            }
        }
        Button {
            id: dateBtn3
            anchors.top: dateBtn2.bottom
            anchors.right: dateRec.right
            anchors.left: dateRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:dateBtn3Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: dateBtnText4
                        text: qsTr("时间")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: dateBtn3Rec.verticalCenter
                        anchors.left: dateBtn3Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: dateBtnText5
                        text: ikTime.currentTime.toString()
                        font.pointSize: 36
                        font.bold: true
                        color: "#999999"
                        anchors.verticalCenter: dateBtn3Rec.verticalCenter
                        anchors.right: dateImg3.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: dateImg3
                        anchors.verticalCenter: dateBtn3Rec.verticalCenter
                        anchors.right: dateBtn3Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }            

            onClicked:{
                ikTime.visible = true
            }
        }
    }

    Rectangle{
        id:sysInfoRec
        anchors.top: topRect.bottom
        anchors.left: soundBtn.right
        anchors.right: basicSet.right
        width: 782
        height: 312
        visible: false

        Button {
            id: sysInfoBtn1
            anchors.top: sysInfoRec.top
            anchors.right: sysInfoRec.right
            anchors.left: sysInfoRec.left
            smooth: true
            property bool m_dateBtn1_dateImg1: true;
            style: ButtonStyle{
                background: Rectangle{
                    id: sysInfoBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: sysInfoBtn1Text1
                        text: qsTr("系统容量")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: sysInfoBtn1Rec.verticalCenter
                        anchors.left: sysInfoBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Image {
                        id: sysInfoImg1
                        anchors.verticalCenter: sysInfoBtn1Rec.verticalCenter
                        anchors.right: sysInfoBtn1Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }

            onClicked:{

            }
        }
        Button {
            id: sysInfoBtn2
            anchors.top: sysInfoBtn1.bottom
            anchors.right: sysInfoRec.right
            anchors.left: sysInfoRec.left
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    id:sysInfoBtn2Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: sysInfoBtn2Text2
                        text: qsTr("设备信息")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: sysInfoBtn2Rec.verticalCenter
                        anchors.left: sysInfoBtn2Rec.left
                        anchors.leftMargin: 50
                    }

                    Image {
                        id: sysInfoImg2
                        anchors.verticalCenter: sysInfoBtn2Rec.verticalCenter
                        anchors.right: sysInfoBtn2Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }


            onClicked:{
                root.viewShow = 5
                console.log("root.viewShow = ",root.viewShow);
            }
        }
        Button {
            id: sysInfoBtn3
            anchors.top: sysInfoBtn2.bottom
            anchors.right: sysInfoRec.right
            anchors.left: sysInfoRec.left
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
        }
    }

    Button {
        id: nullBtn4
        anchors.bottom: nullBtn5.top
        anchors.right: basicSet.right
        anchors.left: nullBtn1.right
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 782
                implicitHeight: 104
                color:"#e9e9e9"
                border.color: "#cccccc"
                border.width: 1
            }
        }
    }
    Button {
        id: nullBtn5
        anchors.bottom: nullBtn6.top
        anchors.right: basicSet.right
        anchors.left: nullBtn2.right
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 782
                implicitHeight: 104
                color:"#f0f0f0"
                border.color: "#cccccc"
                border.width: 1
            }
        }
    }
    Button {
        id: nullBtn6
        anchors.bottom: basicSet.bottom
        anchors.right: basicSet.right
        anchors.left: nullBtn3.right
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 782
                implicitHeight: 104
                color:"#e9e9e9"
                border.color: "#cccccc"
                border.width: 1
            }
        }
    }

    IKVolume{
        id:iKVolume
    }

    IKDate{
        id:ikDate
        visible: false
    }

    IKTime{
        id:ikTime
        visible: false
    }
}
