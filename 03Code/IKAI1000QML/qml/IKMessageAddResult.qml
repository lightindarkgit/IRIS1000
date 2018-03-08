import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: messageAddBG
    visible: false
    anchors.fill: parent
    color: "#80000000"
    property int m_height: 0
    property string infoText:"abc"
    property int m_result:-1
    MouseArea {
        anchors.fill: parent   //
        onClicked:
        {
            //menuRoot.state = "";//非模态时可以这样用
        }
    }
    Rectangle{
        id: contain
        x: 475
        y: 195
        width: 330
        height: 330
        radius: 10
        color: "#B30f0f0f"
        Rectangle{
//            id: message
            Image {
                id: ok_image
                x: 117
                y: 82
                fillMode: Image.TileHorizontally
                smooth: true
                source:  m_result == 0 ? "qrc:///image/toast/pass.png":"qrc:///image/toast/error.png"
            }
            Label{
                id: info
                anchors.top: ok_image.bottom
                anchors.topMargin: 35
                anchors.horizontalCenter: ok_image.horizontalCenter
                font.pixelSize: 36
                text : infoText
                color: "#ffffffff"
            }
            Timer {
                    id: show_timer
                    interval: 3000;//设置定时器定时时间为3000ms,
                    repeat: false //是否重复定时,默认为false
                    running: false //是否开启定时，默认是false，当为true的时候，进入此界面就开始定时
                    triggeredOnStart: false // 是否开启定时就触发onTriggered，一些特殊用户可以用来设置初始值。
                    onTriggered: {  //定时触发槽,定时完成一次就进入一次
                        visible = false
                        if(m_result == 0)
                            irisEnrSuccess = true;
                        userManager.initPersonInfo();
                        viewShow = 12
                    }
            }

            Connections {
                target: qPro;
                onCppEnrollResult:{
                    infoText = str;
                    m_result = result
                    visible = true
                    show_timer.start();
                }
            }
        }
    }
    function startTimer()
    {
        show_timer.start()
    }
    function setInfo(info)
    {
        infoText = info
    }
}
