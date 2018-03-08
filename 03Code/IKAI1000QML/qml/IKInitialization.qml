import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---初始化设置
Rectangle {
    id:initSet
    width: 1080
    height: 720
    property string nomerPic: "qrc:///image/userlist/right.png"
    property string activePic: "qrc:///image/userlist/right_pressed.png"

    IKTopBar{
        id:topRect
        topText: "初始化设置"
    }

    Button {
        id: initSetBtn
        anchors.top: topRect.bottom
        anchors.left: initSet.left
        smooth: true
        property var initSetBtnColor: "#e9e9e9"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:initSetBtn.initSetBtnColor
                border.color: "#cccccc"
                border.width: 1
            }
        }
        Text {
            id: soundBtnText
            text: qsTr("初始化设置")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: initSetBtn.verticalCenter
            anchors.left: initSetBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
        }
    }
    Button {
        id: nullBtn1
        anchors.top: initSetBtn.bottom
        anchors.left: initSet.left
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
        anchors.left: initSet.left
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
        anchors.left: initSet.left
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
        anchors.left: initSet.left
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
        anchors.left: initSet.left
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
        id:initSetRec
        anchors.top: topRect.bottom
        anchors.left: initSetBtn.right
        anchors.right: initSet.right
        width: 782
        height: 312
        visible: true

        Button {
            id: initSetBtn1
            anchors.top: initSetRec.top
            anchors.right: initSetRec.right
            anchors.left: initSetRec.left
            smooth: true
            property bool m_soundBtn1_soundImg1: true;
            style: ButtonStyle{
                background: Rectangle{
                    id:initSetBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: initSetBtnText1
                        text: qsTr("重启设备")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: initSetBtn1Rec.verticalCenter
                        anchors.left: initSetBtn1Rec.left
                        anchors.leftMargin: 50
                    }

                    Image {
                        id: initSetImg1
                        anchors.verticalCenter: initSetBtn1Rec.verticalCenter
                        anchors.right: initSetBtn1Rec.right
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
            id: initSetBtn2
            anchors.top: initSetBtn1.bottom
            anchors.right: initSetRec.right
            anchors.left: initSetRec.left
            smooth: true
            property bool m_soundBtn2_soundImg2: false;
            style: ButtonStyle{
                background: Rectangle{
                    id:initSetBtn2Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: initSetBtnText2
                        text: qsTr("回复出厂设置")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: initSetBtn2Rec.verticalCenter
                        anchors.left: initSetBtn2Rec.left
                        anchors.leftMargin: 50
                    }
                    Image {
                        id: initSetImg2
                        anchors.verticalCenter: initSetBtn2Rec.verticalCenter
                        anchors.right: initSetBtn2Rec.right
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
            id: initSetBtn3
            anchors.top: initSetBtn2.bottom
            anchors.right: initSetRec.right
            anchors.left: initSetRec.left
            smooth: true
            property bool m_soundBtn2_soundImg2: false;
            style: ButtonStyle{
                background: Rectangle{
                    id:initSetBtn3Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: initSetBtnText
                        text: qsTr("关机")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: initSetBtn3Rec.verticalCenter
                        anchors.left: initSetBtn3Rec.left
                        anchors.leftMargin: 50
                    }
                    Image {
                        id: initSetImg
                        anchors.verticalCenter: initSetBtn3Rec.verticalCenter
                        anchors.right: initSetBtn3Rec.right
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
    }

    Button {
        id: nullBtn6
        anchors.bottom: nullBtn7.top
        anchors.right: initSet.right
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
        anchors.right: initSet.right
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
        anchors.bottom: initSet.bottom
        anchors.right: initSet.right
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
}
