import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---接口设置
Rectangle {
    id:interfaceSet
    width: 1280
    height: 720
    property string nomerPic: "qrc:///image/userlist/right.png"
    property string activePic: "qrc:///image/userlist/right_pressed.png"

    IKTopBar{
        id:topRect
        topText: "接口设置"
    }
    Button {
        id: wiegandBtn
        anchors.top: topRect.bottom
        anchors.left: interfaceSet.left
        smooth: true
        property var wiegandBtnColor: "#e9e9e9"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:wiegandBtn.wiegandBtnColor
                border.color: "#cccccc"
                border.width: 1
            }
        }
        Text {
            id: wiegandBtnText
            text: qsTr("输出接口设置")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: wiegandBtn.verticalCenter
            anchors.left: wiegandBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
        }
    }
    Button {
        id: nullBtn1
        anchors.top: wiegandBtn.bottom
        anchors.left: interfaceSet.left
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
        anchors.left: interfaceSet.left
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
        anchors.left: interfaceSet.left
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
        id: nullBtn4
        anchors.top: nullBtn3.bottom
        anchors.left: interfaceSet.left
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
        id: nullBtn5
        anchors.top: nullBtn4.bottom
        anchors.left: interfaceSet.left
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
        id:wiegandRec
        anchors.top: topRect.bottom
        anchors.left: wiegandBtn.right
        anchors.right: interfaceSet.right
        width: 782
        height: 312
        visible: true

        Button {
            id: wiegandRecBtn1
            anchors.top: wiegandRec.top
            anchors.right: wiegandRec.right
            anchors.left: wiegandRec.left
            smooth: true
//            property var currentName:wiegandGroup.current.objectName

            style: ButtonStyle{
                background: Rectangle{
                    id:wiegandRecBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: wiegandRecBtn1Text1
                        text: qsTr("韦根设置")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: wiegandRecBtn1Rec.verticalCenter
                        anchors.left: wiegandRecBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: wiegandRecBtn1Text2
                        text: iKWiegand.currentWiegand.toString()
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: wiegandRecBtn1Rec.verticalCenter
                        anchors.right: wiegandImg1.left
                        anchors.rightMargin:  30
                    }

                    Image {
                        id: wiegandImg1
                        anchors.verticalCenter: wiegandRecBtn1Rec.verticalCenter
                        anchors.right: wiegandRecBtn1Rec.right
                        anchors.rightMargin: 30
                        width: 25
                        height: 44
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }         
            onClicked: {
                iKWiegand.visible = true
            }
        }
        Button {
            id: wiegandRecBtn2
            anchors.top: wiegandRecBtn1.bottom
            anchors.right: wiegandRec.right
            anchors.left: wiegandRec.left
            smooth: true
            property bool m_wiegandRecBtn2_img: false;
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
                id: wiegandRecBtn2Text
                text: qsTr("I/O设置")
                font.pixelSize: 36
                font.bold: true
                color: "#333333"
                anchors.verticalCenter: wiegandRecBtn2.verticalCenter
                anchors.left: wiegandRecBtn2.left
                anchors.leftMargin: 50
            }
            Image {
                id: wiegandRecBtn2Img
                anchors.verticalCenter: wiegandRecBtn2.verticalCenter
                anchors.right: wiegandRecBtn2.right
                anchors.rightMargin: 30
                width: 88
                height: 62
                fillMode: Image.TileHorizontally
                smooth: true
                source: "qrc:///image/userlist/element_select_off.png"
            }

            onClicked:{
                if(m_wiegandRecBtn2_img)
                {
                    wiegandRecBtn2Img.source = "qrc:///image/userlist/element_select_off.png"
                    m_wiegandRecBtn2_img = false;
                }
                else
                {
                    wiegandRecBtn2Img.source = "qrc:///image/userlist/element_select_on.png"
                    m_wiegandRecBtn2_img = true;
                }
            }
        }
        Button {
            id: wiegandRecBtn3
            anchors.top: wiegandRecBtn2.bottom
            anchors.right: wiegandRec.right
            anchors.left: wiegandRec.left
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
        id: nullBtn6
        anchors.bottom: nullBtn7.top
        anchors.right: interfaceSet.right
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
    Button {
        id: nullBtn7
        anchors.bottom: nullBtn8.top
        anchors.right: interfaceSet.right
        anchors.left: nullBtn4.right
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
        id: nullBtn8
        anchors.bottom: interfaceSet.bottom
        anchors.right: interfaceSet.right
        anchors.left: nullBtn5.right
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
    IKWiegand{
        id:iKWiegand
    }
}
