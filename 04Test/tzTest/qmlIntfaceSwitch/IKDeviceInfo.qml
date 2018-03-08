import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//设备信息页
Rectangle {
    id:sysInfoHome
    width: 1280
    height: 720

    Rectangle{
        id:sysInfoHomeTop
        anchors.top: sysInfoHome.top
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 96
        color: "#626e81"

        Text {
            id: sysyInfoText1
            anchors.verticalCenter: sysInfoHomeTop.verticalCenter
            anchors.left: sysInfoHomeTop.left
            anchors.leftMargin: 30
            font.pixelSize:28
            color: "#ffffff"
            text: "设备信息"
        }
        Button {
            id: sysyInfoTextBtn
            anchors.verticalCenter: sysInfoHomeTop.verticalCenter
            anchors.right: sysInfoHomeTop.right
            anchors.rightMargin: 30
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 43
                    implicitHeight: 38
                    color:"#626e81"
                    property string nomerPic: "qrc:///res/image/topbar/back.png"
                    property string activePic: "qrc:///res/image/topbar/back_hover.png"
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

    }

    Rectangle{
        id:sysInfoHomeRct1
        anchors.top: sysInfoHomeTop.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: sysyInfoText2
            anchors.verticalCenter: sysInfoHomeRct1.verticalCenter
            anchors.left: sysInfoHomeRct1.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "版权所有"
        }
        Text {
            id: sysyInfoText3
            anchors.verticalCenter: sysInfoHomeRct1.verticalCenter
            anchors.right: sysInfoHomeRct1.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "北京中科虹霸科技有限公司"
        }
    }
    Rectangle{
        id:sysInfoHomeRct2
        anchors.top: sysInfoHomeRct1.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#e9e9e9"

        Text {
            id: sysyInfoText4
            anchors.verticalCenter: sysInfoHomeRct2.verticalCenter
            anchors.left: sysInfoHomeRct2.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "版本号"
        }
        Text {
            id: sysyInfoText5
            anchors.verticalCenter: sysInfoHomeRct2.verticalCenter
            anchors.right: sysInfoHomeRct2.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "v1.0.1"
        }
    }
    Rectangle{
        id:sysInfoHomeRct3
        anchors.top: sysInfoHomeRct2.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: sysyInfoText6
            anchors.verticalCenter: sysInfoHomeRct3.verticalCenter
            anchors.left: sysInfoHomeRct3.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "序列号"
        }
        Text {
            id: sysyInfoText7
            anchors.verticalCenter: sysInfoHomeRct3.verticalCenter
            anchors.right: sysInfoHomeRct3.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "00-01-6C-06-A6-29"
        }
    }
    Rectangle{
        id:sysInfoHomeRct4
        anchors.top: sysInfoHomeRct3.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#e9e9e9"

        Text {
            id: sysyInfoText8
            anchors.verticalCenter: sysInfoHomeRct4.verticalCenter
            anchors.left: sysInfoHomeRct4.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "MAC地址"
        }
        Text {
            id: sysyInfoText9
            anchors.verticalCenter: sysInfoHomeRct4.verticalCenter
            anchors.right: sysInfoHomeRct4.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "00-01-6C-06-A6-29"
        }
    }
    Rectangle{
        id:sysInfoHomeRct5
        anchors.top: sysInfoHomeRct4.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: sysyInfoText10
            anchors.verticalCenter: sysInfoHomeRct5.verticalCenter
            anchors.left: sysInfoHomeRct5.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "公司地址"
        }
        Text {
            id: sysyInfoText11
            anchors.verticalCenter: sysInfoHomeRct5.verticalCenter
            anchors.right: sysInfoHomeRct5.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "北京市海淀区银谷大厦702"
        }
    }
    Rectangle{
        id:sysInfoHomeRct6
        anchors.top: sysInfoHomeRct5.bottom
        anchors.left: sysInfoHome.left
        anchors.right: sysInfoHome.right
        width: sysInfoHome.width
        height: 104
        color: "#e9e9e9"

        Text {
            id: sysyInfoText12
            anchors.verticalCenter: sysInfoHomeRct6.verticalCenter
            anchors.left: sysInfoHomeRct6.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#333333"
            text: "联系电话"
        }
        Text {
            id: sysyInfoText13
            anchors.verticalCenter: sysInfoHomeRct6.verticalCenter
            anchors.right: sysInfoHomeRct6.right
            anchors.rightMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "010-5120343-8899"
        }
    }
}
