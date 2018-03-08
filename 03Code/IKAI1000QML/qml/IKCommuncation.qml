import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置---通信设置
Rectangle {
    id:communicationSet
    width: 1280
    height: 720
    property string nomerPic: "qrc:///image/userlist/right.png"
    property string activePic: "qrc:///image/userlist/right_pressed.png"

    IKTopBar{
        id:communicationTopRect
        topText: "通信设置"
    }
    Button {
        id: internetSetBtn
        anchors.top: communicationTopRect.bottom
        anchors.left: communicationSet.left
        smooth: true
        property var internetSetBtnColor: "#e9e9e9"
        property var internetSetBtnBorderColor: "#cccccc"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:internetSetBtn.internetSetBtnColor
                border.color: internetSetBtn.internetSetBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: internetSetBtnText
            text: qsTr("网络设置")
            font.pixelSize: 36
            font.bold: true
            color: "#5aa5e6"
            anchors.verticalCenter: internetSetBtn.verticalCenter
            anchors.left: internetSetBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            internetSetRec.visible = true
            serverConnectRec.visible = false

            internetSetBtn.internetSetBtnColor = "#e9e9e9"
            serverConnectBtn.serverConnectBtnColor = "#cacbca"
            internetSetBtn.internetSetBtnBorderColor = "#cccccc"
            serverConnectBtn.serverConnectBtnBorderColor = "#aaaaaa"


            internetSetBtnText.color = "#5aa5e6"
            serverConnectBtnText.color = "#666666"



        }
    }
    Button {
        id: serverConnectBtn
        anchors.top: internetSetBtn.bottom
        anchors.left: communicationSet.left
        smooth: true
        property var serverConnectBtnColor: "#cacbca"
        property var serverConnectBtnBorderColor: "#aaaaaa"
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 298
                implicitHeight: 104
                color:serverConnectBtn.serverConnectBtnColor
                border.color: serverConnectBtn.serverConnectBtnBorderColor
                border.width: 1
            }
        }
        Text {
            id: serverConnectBtnText
            text: qsTr("服务器连接设置")
            font.pixelSize: 36
            font.bold: true
            color: "#666666"
            anchors.verticalCenter: serverConnectBtn.verticalCenter
            anchors.left: serverConnectBtn.left
            anchors.leftMargin: 30
        }

        onClicked:{
            internetSetRec.visible = false
            serverConnectRec.visible = true

            internetSetBtn.internetSetBtnColor = "#cacbca"
            serverConnectBtn.serverConnectBtnColor = "#e9e9e9"
            internetSetBtn.internetSetBtnBorderColor = "#aaaaaa"
            serverConnectBtn.serverConnectBtnBorderColor = "#cccccc"

            internetSetBtnText.color = "#666666"
            serverConnectBtnText.color = "#5aa5e6"
        }
    }
    Button {
        id: nullBtn1
        anchors.top: serverConnectBtn.bottom
        anchors.left: communicationSet.left
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
        anchors.left: communicationSet.left
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
        anchors.left: communicationSet.left
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
        anchors.left: communicationSet.left
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
        id:internetSetRec
        anchors.top: communicationTopRect.bottom
        anchors.left: internetSetBtn.right
        anchors.right: communicationSet.right
        width: 782
        height: 312
        visible: true

        Button {
            id: internetSetRecBtn1
            anchors.top: internetSetRec.top
            anchors.right: internetSetRec.right
            anchors.left: internetSetRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:internetSetRecBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: internetSetRecBtn1Text1
                        text: qsTr("IP地址")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn1Rec.verticalCenter
                        anchors.left: internetSetRecBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: internetSetRecBtn1Text2
                        text: qsTr("192.168.1.1")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn1Rec.verticalCenter
                        anchors.right: internetSetImg.left
                        anchors.rightMargin: 30
                    }

                    Image {
                        id: internetSetImg
                        anchors.verticalCenter: internetSetRecBtn1Rec.verticalCenter
                        anchors.right: internetSetRecBtn1Rec.right
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
            id: internetSetRecBtn2
            anchors.top: internetSetRecBtn1.bottom
            anchors.right: internetSetRec.right
            anchors.left: internetSetRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:internetSetRecBtn2Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: internetSetRecBtn2Text1
                        text: qsTr("网关")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn2Rec.verticalCenter
                        anchors.left: internetSetRecBtn2Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: internetSetRecBtn2Text2
                        text: qsTr("192.168.1.1")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn2Rec.verticalCenter
                        anchors.right: internetSetRecBtn2Img.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: internetSetRecBtn2Img
                        anchors.verticalCenter: internetSetRecBtn2Rec.verticalCenter
                        anchors.right: internetSetRecBtn2Rec.right
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
            id: internetSetRecBtn3
            anchors.top: internetSetRecBtn2.bottom
            anchors.right: internetSetRec.right
            anchors.left: internetSetRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:internetSetRecBtn3Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: internetSetRecBtn3Text1
                        text: qsTr("子网掩码")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn3Rec.verticalCenter
                        anchors.left: internetSetRecBtn3Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: internetSetRecBtn3Text2
                        text: qsTr("192.168.1.1")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: internetSetRecBtn3Rec.verticalCenter
                        anchors.right: internetSetRecBtn3Img.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: internetSetRecBtn3Img
                        anchors.verticalCenter: internetSetRecBtn3Rec.verticalCenter
                        anchors.right: internetSetRecBtn3Rec.right
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

    Rectangle{
        id:serverConnectRec
        anchors.top: communicationTopRect.bottom
        anchors.left: internetSetBtn.right
        anchors.right: internetSetRec.right
        width: 782
        height: 312
        visible: false

        Button {
            id: serverConnectRecBtn1
            anchors.top: serverConnectRec.top
            anchors.right: serverConnectRec.right
            anchors.left: serverConnectRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:serverConnectRecBtn1Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#f0f0f0"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: serverConnectRecBtn1Text1
                        text: qsTr("服务器IP")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: serverConnectRecBtn1Rec.verticalCenter
                        anchors.left: serverConnectRecBtn1Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: serverConnectRecBtn1Text2
                        text: qsTr("192.168.1.1")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: serverConnectRecBtn1Rec.verticalCenter
                        anchors.right: serverConnectRecBtn1Img.left
                        anchors.rightMargin: 30
                    }

                    Image {
                        id: serverConnectRecBtn1Img
                        anchors.verticalCenter: serverConnectRecBtn1Rec.verticalCenter
                        anchors.right: serverConnectRecBtn1Rec.right
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
            id: serverConnectRecBtn2
            anchors.top: serverConnectRecBtn1.bottom
            anchors.right: serverConnectRec.right
            anchors.left: serverConnectRec.left
            smooth: true

            style: ButtonStyle{
                background: Rectangle{
                    id:serverConnectRecBtn2Rec
                    implicitWidth: 782
                    implicitHeight: 104
                    color:"#e9e9e9"
                    border.color: "#cccccc"
                    border.width: 1
                    Text {
                        id: serverConnectRecBtn2Text1
                        text: qsTr("端口")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: serverConnectRecBtn2Rec.verticalCenter
                        anchors.left: serverConnectRecBtn2Rec.left
                        anchors.leftMargin: 50
                    }
                    Text {
                        id: serverConnectRecBtn2Text2
                        text: qsTr("888888888")
                        font.pixelSize: 36
                        font.bold: true
                        color: "#333333"
                        anchors.verticalCenter: serverConnectRecBtn2Rec.verticalCenter
                        anchors.right: serverConnectRecBtn2Img.left
                        anchors.rightMargin: 30
                    }
                    Image {
                        id: serverConnectRecBtn2Img
                        anchors.verticalCenter: serverConnectRecBtn2Rec.verticalCenter
                        anchors.right: serverConnectRecBtn2Rec.right
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
            id: serverConnectRecBtn3
            anchors.top: serverConnectRecBtn2.bottom
            anchors.right: serverConnectRec.right
            anchors.left: serverConnectRec.left
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
        id: nullBtn5
        anchors.bottom: nullBtn6.top
        anchors.right: communicationSet.right
        anchors.left: nullBtn2.right
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
        id: nullBtn6
        anchors.bottom: nullBtn7.top
        anchors.right: communicationSet.right
        anchors.left: nullBtn3.right
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
        id: nullBtn7
        anchors.bottom: communicationSet.bottom
        anchors.right: communicationSet.right
        anchors.left: nullBtn4.right
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
