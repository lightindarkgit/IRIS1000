import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//系统设置主页
Rectangle {
    id:setHome
    width: 1280
    height: 720
    property bool m_pswdValidabtn_visible: false;

    //背景图片
    Image {
        id: rocket
        fillMode: Image.TileHorizontally
        smooth: true
        source: "qrc:///image/setImage/background.png"
    }

    IKTopBar{
        id:topRect
        topText: "系统设置"
        topRectBtn1visible: false
    }

    Button
    {
        id: sysHomeBtn1
        anchors.top:setHome.top
        anchors.topMargin: topRect.height+70
        anchors.left: setHome.left
        anchors.leftMargin: 158
        width: 112
        height:104
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 112
                implicitHeight: 104
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/basic.png"
                property string activePic: "qrc:///image/setImage/basic_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }

        onClicked:{
            root.viewShow = 4
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysHomeBtn2
        anchors.top:setHome.top
        anchors.topMargin: topRect.height+70
        anchors.left: sysHomeBtn1.right
        anchors.leftMargin: 315
        width: 110
        height:110
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 110
                implicitHeight: 110
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/interface.png"
                property string activePic: "qrc:///image/setImage/interface_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 6
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysHomeBtn3
        anchors.top:setHome.top
        anchors.topMargin: topRect.height+70
        anchors.left: sysHomeBtn2.right
        anchors.leftMargin: 325
        width: 93
        height:110
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 93
                implicitHeight: 110
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/verify.png"
                property string activePic: "qrc:///image/setImage/verify_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 7
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysHomeBtn4
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 129
        anchors.left: setHome.left
        anchors.leftMargin: 156
        width: 117
        height:121
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 117
                implicitHeight: 121
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/Communication.png"
                property string activePic: "qrc:///image/setImage/Communication_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 8
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysHomeBtn5
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 129
        anchors.left: sysHomeBtn4.right
        anchors.leftMargin: 313
        width: 108
        height:108
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 108
                implicitHeight: 108
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/data.png"
                property string activePic: "qrc:///image/setImage/data_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 9
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysHomeBtn6
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 129
        anchors.left: sysHomeBtn5.right
        anchors.leftMargin: 315
        width: 114
        height:114
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 114
                implicitHeight: 114
                color:"#262626"
                property string nomerPic: "qrc:///image/setImage/init.png"
                property string activePic: "qrc:///image/setImage/init_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 10
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Text {
        id: sysHomeText1
        text: qsTr("基本设置")
        anchors.top: sysHomeBtn1.bottom
        anchors.topMargin:30
        anchors.horizontalCenter: sysHomeBtn1.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }
    Text {
        id: sysHomeText2
        text: qsTr("接口设置")
        anchors.top: sysHomeBtn2.bottom
        anchors.topMargin:30
        anchors.horizontalCenter: sysHomeBtn2.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }
    Text {
        id: sysHomeText3
        text: qsTr("用户设置")
        anchors.top: sysHomeBtn3.bottom
        anchors.topMargin:30
        anchors.horizontalCenter: sysHomeBtn3.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }
    Text {
        id: sysHomeText4
        text: qsTr("通信设置")
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 63
        anchors.horizontalCenter: sysHomeBtn4.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }
    Text {
        id: sysHomeText5
        text: qsTr("数据管理")
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 63
        anchors.horizontalCenter: sysHomeBtn5.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }
    Text {
        id: sysHomeText6
        text: qsTr("初始化设置")
        anchors.bottom: setHome.bottom
        anchors.bottomMargin: 63
        anchors.horizontalCenter: sysHomeBtn6.horizontalCenter
        font.pixelSize:36
        color: "#ffffff"
    }

}
