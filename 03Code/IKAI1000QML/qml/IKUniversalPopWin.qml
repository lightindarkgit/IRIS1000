import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

//通用弹窗
//通过以下参数的设置，定制弹窗：
//1.按钮 当需要两个button时，设置属性btn1和btn2的内容，btn1为默认按钮;
//       当只需要一个button时，只设置属性btn1内容即可
//2.内容 当弹窗内容为一项时，设置属性promptContent的内容;
//       当弹窗内容为两项时，设置属性promptContent和promptContent2的内容，promptContent在promptContent2的下面
//3.倒计时退出 使用倒计时退出需要在调用弹窗时，设置setTime内容(单位s)，并调用startTimer()函数开启定时器
//弹窗返回说明:
//点击“默认按钮”发送信号 emit: popWinClicked(true)   点击非默认按钮发送信号  emit: popWinClicked(false)
Rectangle {
    id: popWinBackground
    visible: false
    anchors.fill: parent
    color: "#80000000"
    property var btn1:null
    property var btn2:null
    property var promptContent:null
    property var promptContent2:null
    property int setTime: 0
    signal popWinClicked(bool res);

    Timer {
            id: show_timer
            interval: 1000;//设置定时器定时时间为1000ms,
            repeat: true //是否重复定时,默认为false
            running: setTime == 0? false:true //是否开启定时，默认是false，当为true的时候，进入此界面就开始定时
            triggeredOnStart: false // 是否开启定时就触发onTriggered，一些特殊用户可以用来设置初始值。
            onTriggered: {  //定时触发槽,定时完成一次就进入一次
                popWinBackground.setTime = popWinBackground.setTime -1;
                if(popWinBackground.setTime === 0)
                {
                    emit: popWinClicked(true)
                    console.log("==================res: true")
                    show_timer.stop();
                    popWinBackground.visible = false
                }
            }
    }
    function startTimer()
    {
        show_timer.start()
    }
    MouseArea {
        anchors.fill: parent//
        onClicked:
        {
            //menuRoot.state = "";//非模态时可以这样用
        }
    }
    Rectangle{
        id:popWinDlg
        width: 630
        height: 300
        x:(popWinBackground.width-popWinDlg.width)/2
        y:(popWinBackground.height - popWinDlg.height)/2
        radius: 10
        color: "#ffffff"
        Label{
            id: popWinDlgLabel
            anchors.left: popWinDlg.left
            anchors.leftMargin: 30
            anchors.right: popWinDlg.right
            anchors.rightMargin: 30
            anchors.top: popWinDlg.top
            anchors.bottom: popWinDlgBtn1.top

            Text {
                id: popWinDlgText1
                anchors.horizontalCenter: popWinDlgLabel.horizontalCenter
                anchors.bottom: popWinDlgLabel.bottom
                anchors.bottomMargin: promptContent2 == null ? (popWinDlgLabel.height-popWinDlgText1.height)/2 : (popWinDlgLabel.height-popWinDlgText1.height-popWinDlgText2.height-10)/2
                text: promptContent
                font.pixelSize: 30
                color: "#333333"
            }
            Text {
                id: popWinDlgText2
                visible: promptContent2 == null ? false:true
                anchors.horizontalCenter: popWinDlgLabel.horizontalCenter
                anchors.bottom: popWinDlgText1.top
                anchors.bottomMargin: 10
                text: promptContent2
                font.pixelSize: 30
                color: "#333333"
            }
        }

        Button {
            id: popWinDlgBtn1
            visible: btn2 == null ? false:true
            anchors.left: popWinDlg.left
            anchors.bottom: popWinDlg.bottom
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 315
                    implicitHeight: 80
                    color:"#ffffff"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                id: popWinDlgBtn1Text
                text: btn2
                font.pixelSize: 30
                font.bold: true
                color: "#666666"
                anchors.verticalCenter: popWinDlgBtn1.verticalCenter
                anchors.horizontalCenter: popWinDlgBtn1.horizontalCenter
            }
            onClicked: {
                emit: popWinClicked(false)
                popWinBackground.visible = false
                console.log("===================res: false")
            }
        }

        Button {
            id: popWinDlgBtn2
//            anchors.left: popWinDlgBtn1.right
            anchors.right: popWinDlg.right
            anchors.bottom: popWinDlg.bottom
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: btn2 == null ? 630 : 315
                    implicitHeight: 80
                    color:"#ffffff"
                    border.color: "#cccccc"
                    border.width: 1
                }
            }
            Text {
                id: popWinDlgBtn2Text
                text: setTime == 0 ? btn1 : ( btn1 + "(" + popWinBackground.setTime + "s)" )
                font.pixelSize: 30
                font.bold: true
                color: "#5aa5e6"
                anchors.verticalCenter: popWinDlgBtn2.verticalCenter
                anchors.horizontalCenter: popWinDlgBtn2.horizontalCenter
            }
            onClicked: {
                emit: popWinClicked(true)
                console.log("==================res: true")
                popWinBackground.visible = false
            }
        }

    }
}

