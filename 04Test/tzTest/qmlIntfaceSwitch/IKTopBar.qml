import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//topbar


Rectangle {
    id:topRect
    width: 1280
    height: 96
    anchors.top:parent.top
    anchors.left: parent.left
    color: "#626e81"
    property var topText:"初始化设置"
    property bool topRectBtn1visible:true

    Text {
        id: date
        anchors.verticalCenter: topRect.verticalCenter
        anchors.left: topRect.left
        anchors.leftMargin: 30
        font.pixelSize:28
        color: "#ffffff"
        text: topText
    }
    Button {
        id: topRectBtn1
        anchors.verticalCenter: topRect.verticalCenter
        anchors.right: topRectBtn2.left
        anchors.rightMargin: 50
        smooth: true
        visible:topRectBtn1visible
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
            root.viewShow = 3
            console.log("root.viewShow = ",root.viewShow);

        }
    }

    Button {
        id: topRectBtn2
        anchors.verticalCenter: topRect.verticalCenter
        anchors.right: topRect.right
        anchors.rightMargin: 30
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 43
                implicitHeight: 38
                color:"#626e81"
                property string nomerPic: "qrc:///res/image/topbar/home.png"
                property string activePic: "qrc:///res/image/topbar/home_hover.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                }
            }
        }
        onClicked:{
            root.viewShow = 2
            console.log("root.viewShow = ",root.viewShow);
        }
    }
}
