import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---用户设置
Rectangle {
    id:verifySet
    width: 1280
    height: 720
    property string nomerPic: "qrc:///res/image/userlist/right.png"
    property string activePic: "qrc:///res/image/userlist/right_hover.png"

    IKTopBar{
        id:verifyTopRect
        topText: "用户设置"
    }
    Button {
        id: userVerifyBtn
        anchors.top: verifyTopRect.bottom
        anchors.left: verifySet.left
        smooth: true
        property var userVerifyBtnColor: "#e9e9e9"
        property var userVerifyBtnBorderColor: "#cccccc"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:userVerifyBtn.userVerifyBtnColor
                border.color: userVerifyBtn.userVerifyBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: userVerifyBtnText
            text: qsTr("用户")
            font.pointSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: userVerifyBtn.verticalCenter
            anchors.left: userVerifyBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userVerifyRec.visible = true
            adminiVerifyRec.visible = false
            faceVerifyRec.visible = false

            userVerifyBtnText.color = "#5aa5e6"
            userVerifyBtn.userVerifyBtnColor = "#e9e9e9"
            userVerifyBtn.userVerifyBtnBorderColor = "#cccccc"

            adminiVerifyBtnText.color = "#666666"
            adminiVerifyBtn.adminiVerifyBtnColor = "#cacbca"
            adminiVerifyBtn.adminiVerifyBtnBorderColor = "#aaaaaa"

            faceVerifyBtnText.color = "#666666"
            faceVerifyBtn.faceVerifyBtnColor = "#cacbca"
            faceVerifyBtn.faceVerifyBtnBorderColor = "#aaaaaa"

        }
    }
    Button {
        id: adminiVerifyBtn
        anchors.top: userVerifyBtn.bottom
        anchors.left: verifySet.left
        smooth: true
        property var adminiVerifyBtnColor: "#cacbca"
        property var adminiVerifyBtnBorderColor: "#aaaaaa"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:adminiVerifyBtn.adminiVerifyBtnColor
                border.color: adminiVerifyBtn.adminiVerifyBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: adminiVerifyBtnText
            text: qsTr("管理员")
            font.pointSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: adminiVerifyBtn.verticalCenter
            anchors.left: adminiVerifyBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            userVerifyRec.visible = false
            adminiVerifyRec.visible = true
            faceVerifyRec.visible = false

            userVerifyBtnText.color = "#666666"
            userVerifyBtn.userVerifyBtnColor = "#cacbca"
            userVerifyBtn.userVerifyBtnBorderColor = "#aaaaaa"

            adminiVerifyBtnText.color = "#5aa5e6"
            adminiVerifyBtn.adminiVerifyBtnColor = "#e9e9e9"
            adminiVerifyBtn.adminiVerifyBtnBorderColor = "#cccccc"

            faceVerifyBtnText.color = "#666666"
            faceVerifyBtn.faceVerifyBtnColor = "#cacbca"
            faceVerifyBtn.faceVerifyBtnBorderColor = "#aaaaaa"
        }
    }
    Button {
        id: faceVerifyBtn
        anchors.top: adminiVerifyBtn.bottom
        anchors.left: verifySet.left
        smooth: true
        property var faceVerifyBtnColor: "#cacbca"
        property var faceVerifyBtnBorderColor: "#aaaaaa"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:faceVerifyBtn.faceVerifyBtnColor
                border.color: faceVerifyBtn.faceVerifyBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: faceVerifyBtnText
            text: qsTr("人脸验证")
            font.pointSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: faceVerifyBtn.verticalCenter
            anchors.left: faceVerifyBtn.left
            anchors.leftMargin: 30

        }
        onClicked:{
            userVerifyRec.visible = false
            adminiVerifyRec.visible = false
            faceVerifyRec.visible = true

            userVerifyBtnText.color = "#666666"
            userVerifyBtn.userVerifyBtnColor = "#cacbca"
            userVerifyBtn.userVerifyBtnBorderColor = "#aaaaaa"

            adminiVerifyBtnText.color = "#666666"
            adminiVerifyBtn.adminiVerifyBtnColor = "#cacbca"
            adminiVerifyBtn.adminiVerifyBtnBorderColor = "#aaaaaa"

            faceVerifyBtnText.color = "#5aa5e6"
            faceVerifyBtn.faceVerifyBtnColor = "#e9e9e9"
            faceVerifyBtn.faceVerifyBtnBorderColor = "#cccccc"
        }
    }
    Button {
        id: nullBtn1
        anchors.top: faceVerifyBtn.bottom
        anchors.left: verifySet.left
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
        anchors.left: verifySet.left
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
        anchors.left: verifySet.left
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
        id:userVerifyRec
        anchors.top: verifyTopRect.bottom
        anchors.left: userVerifyBtn.right
        anchors.right: verifySet.right
        width: 782
        height: 312
        visible: true

        Button {
            id: userVerifyBtn1
            anchors.top: userVerifyRec.top
            anchors.right: userVerifyRec.right
            anchors.left: userVerifyRec.left
            smooth: true
            property bool m_soundBtn1_soundImg1: true;
            style: ButtonStyle{
                background: Rectangle{
                    id:userVerifyBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: userVerifyBtn1Text1
                        text: qsTr("验证通过方式")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: userVerifyBtn1Rec.verticalCenter
                        anchors.left: userVerifyBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: userVerifyBtn1Text2
                        text: userVerifyDialog.currentVerify
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: userVerifyBtn1Rec.verticalCenter
                        anchors.right: userVerifyBtn1Img.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: userVerifyBtn1Img
                        anchors.verticalCenter: userVerifyBtn1Rec.verticalCenter
                        anchors.right: userVerifyBtn1Rec.right
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
                userVerifyDialog.visible = true
            }
        }
        Button {
            id: userVerifyBtn2
            anchors.top: userVerifyBtn1.bottom
            anchors.right: userVerifyRec.right
            anchors.left: userVerifyRec.left
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
            id: userVerifyBtn3
            anchors.top: userVerifyBtn2.bottom
            anchors.right: userVerifyRec.right
            anchors.left: userVerifyRec.left
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

    Rectangle{
        id:adminiVerifyRec
        anchors.top: verifyTopRect.bottom
        anchors.left: userVerifyBtn.right
        anchors.right: verifySet.right
        width: 782
        height: 312
        visible: false

        Button {
            id: adminiVerifyBtn1
            anchors.top: adminiVerifyRec.top
            anchors.right: adminiVerifyRec.right
            anchors.left: adminiVerifyRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:adminiVerifyBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: adminiVerifyBtn1Text1
                        text: qsTr("验证通过方式")
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: adminiVerifyBtn1Rec.verticalCenter
                        anchors.left: adminiVerifyBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: adminiVerifyBtn1Text2
                        text: adminiVerifyDialog.currentVerify
                        font.pointSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: adminiVerifyBtn1Rec.verticalCenter
                        anchors.right: adminiVerifyImg1.left
                        anchors.rightMargin: 30
                    }

                    Image {
                        id: adminiVerifyImg1
                        anchors.verticalCenter: adminiVerifyBtn1Rec.verticalCenter
                        anchors.right: adminiVerifyBtn1Rec.right
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
                adminiVerifyDialog.visible = true
            }
        }
        Button {
            id: adminiVerifyBtn2
            anchors.top: adminiVerifyBtn1.bottom
            anchors.right: adminiVerifyRec.right
            anchors.left: adminiVerifyRec.left
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
            id: adminiVerifyBtn3
            anchors.top: adminiVerifyBtn2.bottom
            anchors.right: adminiVerifyRec.right
            anchors.left: adminiVerifyRec.left
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
    Rectangle{
        id:faceVerifyRec
        anchors.top: verifyTopRect.bottom
        anchors.left: userVerifyBtn.right
        anchors.right: verifySet.right
        width: 782
        height: 312
        visible: false

        Button {
            id: faceVerifyBtn1
            anchors.top: faceVerifyRec.top
            anchors.right: faceVerifyRec.right
            anchors.left: faceVerifyRec.left
            smooth: true
            property bool m_faceVerifyBtn1_img: true;
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
                id: faceVerifyBtn1Text1
                text: qsTr("是否与虹膜识别同时开启")
                font.pointSize: 36
                font.bold: true
                color: "#333333"
                anchors.verticalCenter: faceVerifyBtn1.verticalCenter
                anchors.left: faceVerifyBtn1.left
                anchors.leftMargin: 50
            }

            Image {
                id: faceVerifyImg1
                anchors.verticalCenter: faceVerifyBtn1.verticalCenter
                anchors.right: faceVerifyBtn1.right
                anchors.rightMargin: 30
                width: 88
                height: 62
                fillMode: Image.TileHorizontally
                smooth: true
                source: "qrc:///res/image/userlist/element_select_open.png"
            }

            onClicked:{
                if(m_faceVerifyBtn1_img)
                {
                    faceVerifyImg1.source = "qrc:///res/image/userlist/element_select_off.png"
                    m_faceVerifyBtn1_img = false;
                }
                else
                {
                    faceVerifyImg1.source = "qrc:///res/image/userlist/element_select_open.png"
                    m_faceVerifyBtn1_img = true;
                }
            }
        }
        Button {
            id: faceVerifyBtn2
            anchors.top: faceVerifyBtn1.bottom
            anchors.right: faceVerifyRec.right
            anchors.left: faceVerifyRec.left
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
            id: faceVerifyBtn3
            anchors.top: faceVerifyBtn2.bottom
            anchors.right: faceVerifyRec.right
            anchors.left: faceVerifyRec.left
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
        anchors.right: verifySet.right
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
        anchors.right: verifySet.right
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
        anchors.bottom: verifySet.bottom
        anchors.right: verifySet.right
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

    IKIdentMode{
        id:userVerifyDialog
    }    
    IKIdentMode{
        id:adminiVerifyDialog
    }    
}
