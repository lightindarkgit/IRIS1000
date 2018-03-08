import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//管理主页
Rectangle {
    id:managementHome
    width: 1280
    height: 720
    property var idenFlage: iKUsersSet.initUserVerifyText

        function idenButnChange(x,y)
        {
            if(x === true)
            {
                console.log("0000000000000000000000000000000000000000000000000000000000000000000000000000\n")
                idenFlage = y;
            }
        }

    function getCurDate()
    {
        var d = new Date();
        var week;
        switch (d.getDay()){
        case 1: week="星期一"; break;
        case 2: week="星期二"; break;
        case 3: week="星期三"; break;
        case 4: week="星期四"; break;
        case 5: week="星期五"; break;
        case 6: week="星期六"; break;
        default: week="星期天";
        }
        return week;
    }

    function getCurTime()
    {
        var d = new Date();
        var hours = add_zero(d.getHours());
        var minutes = add_zero(d.getMinutes());
        var seconds=add_zero(d.getSeconds());
        var ndate = hours+":"+minutes+":"+seconds;
        return ndate;
    }

    function add_zero(temp)
    {
        if(temp<10) return "0"+temp;
        else return temp;
    }

    //背景图片
    Image {
        id: rocket
        fillMode: Image.TileHorizontally
        smooth: true
        source: "qrc:///image/setImage/background.png"
    }

    Rectangle {
        id:topRect
        width: 1280
        height: 50
        anchors.top:managementHome.top
        anchors.left: managementHome.left
        color: "#262626"

        Image {
            id: topRectImg1
            fillMode: Image.TileHorizontally
            anchors.verticalCenter: topRect.verticalCenter
            anchors.left: topRect.left
            anchors.leftMargin: 30
            smooth: true
//            source: "qrc:///res/image/statusbar/irisking.png"
            source: "qrc:///image/statusbar/irisking_disabled.png"
        }

        Image {
            id: topRectImg2
            fillMode: Image.TileHorizontally
            anchors.verticalCenter: topRect.verticalCenter
            anchors.left: topRectImg1.right
            anchors.leftMargin: 15
            smooth: true
//            source: "qrc:///res/image/statusbar/keyboard.png"
            source: "qrc:///image/statusbar/keyboard_disabled.png"
        }
        Image {
            id: topRectImg3
            fillMode: Image.TileHorizontally
            anchors.verticalCenter: topRect.verticalCenter
            anchors.left: topRectImg2.right
            anchors.leftMargin: 15
            smooth: true
//            source: "qrc:///res/image/statusbar/usb.png"
            source: "qrc:///image/statusbar/USB_disabled.png"
        }
        Image {
            id: topRectImg4
            fillMode: Image.TileHorizontally
            anchors.verticalCenter: topRect.verticalCenter
            anchors.left: topRectImg3.right
            anchors.leftMargin: 15
            smooth: true
//            source: "qrc:///res/image/statusbar/pc.png"
            source: "qrc:///image/statusbar/PC_disabled.png"
        }

        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: {
                time.text = getCurTime().toString();
                date.text = getCurDate().toString();
            }
        }
        //时间显示


        Text {
            id: date
            anchors.verticalCenter: topRect.verticalCenter
            anchors.right: time.left
            anchors.rightMargin: 20
            font.pixelSize:28
            color: "#ffffff"
        }

        Text {
            id: time
            anchors.verticalCenter: topRect.verticalCenter
            anchors.right: topRect.right
            anchors.rightMargin: 30
            font.pixelSize:28
            color: "#ffffff"
        }
    }

    Button
    {
        id: userImage
        anchors.top:managementHome.top
        anchors.topMargin: 223
        anchors.right: sysSetImage.left
        anchors.rightMargin: 200
        width: 200
        height:234
        smooth: true        
        style: ButtonStyle{
            background: Rectangle{
                color: "#262626"
                property string nomerPic: "qrc:///image/home/user.png"
                property string activePic: "qrc:///image/home/user_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                    }
                }
            }
        onClicked:{
//            qPro.identFlag = true
            root.viewShow = 11
            console.log("root.viewShow = ",root.viewShow);
        }
    }
    Button
    {
        id: sysSetImage
        anchors.top:managementHome.top
        anchors.topMargin: 223
        anchors.right: managementHome.right
        anchors.rightMargin: 321
        width: 238
        height:222
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                color: "#262626"
                property string nomerPic: "qrc:///image/home/setting.png"
                property string activePic: "qrc:///image/home/setting_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                    }
                }
            }
        onClicked:{
//            qPro.identFlag = true
            root.viewShow = 3
            console.log("root.viewShow = ",root.viewShow);
        }
    }

    Label{
        id:usysSetText
        anchors.top: userImage.bottom
        anchors.topMargin: 40
        anchors.bottom: managementHome.bottom
        anchors.bottomMargin: 180
        anchors.horizontalCenter: userImage.horizontalCenter
        font.pixelSize:40
        color: "#ffffff"
        text: "用户管理"
    }

    Label{
        id:userText
        anchors.top: sysSetImage.bottom
        anchors.topMargin: 40
        anchors.bottom: managementHome.bottom
        anchors.bottomMargin: 180
        anchors.horizontalCenter: sysSetImage.horizontalCenter
        font.pixelSize:40
        color: "#ffffff"
        text: "系统设置"
    }
    Button
    {
        id: idenButn
        anchors.top:managementHome.top
        anchors.topMargin: 100
        anchors.right: managementHome.right
        anchors.rightMargin: 30

        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 160
                implicitHeight: 80
                color:"#2B2C2E"
                property string nomerPic: "qrc:///image/other/recognition.png"
                property string activePic: "qrc:///image/other/recognition_pressed.png"
                Image {
                    source: control.pressed? activePic : nomerPic
                    }
                }
            }
        onClicked:{
            if(idenFlage === qsTr("虹膜和卡") || idenFlage === qsTr("只有卡"))
            {
                root.viewShow = 16
                qPro.startSwipeCard = true
            }
            else if(idenFlage === qsTr("虹膜或卡"))
            {
                qPro.identFlag = true
                root.viewShow = 1
                iKIdentEnroll.m_Enroll = false
                qPro.startSwipeCard = true
            }
            else if(idenFlage === qsTr("只有虹膜"))
            {
                qPro.identFlag = true
                root.viewShow = 1
                iKIdentEnroll.m_Enroll = false
                qPro.startSwipeCard = false
            }

            console.log("root.viewShow = ",root.viewShow);
        }
    }
}
