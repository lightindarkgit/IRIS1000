import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//刷卡登录页面
Rectangle {
    id:swite
    width: 1280
    height: 720
    property var idenFlage: iKUsersSet.initUserVerifyText

    function idenButnChange(x,y)
    {
        if(x === true)
        {
            idenFlage = y;
        }
    }



    //背景图片
    Image {
        id: rocket
        fillMode: Image.TileHorizontally
        smooth: true
        source: "qrc:///image/setImage/user_bg.png"
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
        //                 var years = d.getFullYear();
        //                 var month = add_zero(d.getMonth()+1);
        //                 var days = add_zero(d.getDate());
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
    Timer {
        interval: 500; running: true; repeat: true
        onTriggered: {
            time.text = getCurTime().toString();
            date.text = getCurDate().toString();
        }
    }

    Rectangle{
        id:switeTopRec
        //        visible: m_Enroll? false:true
        anchors.top: swite.top
        anchors.left: swite.left
        width: swite.width
        height:96
        color: "#626e81"
        Text {
            id: time
            anchors.right: switeTopRec.right
            anchors.rightMargin: 50
            anchors.top: switeTopRec.top
            anchors.topMargin: (96-14-time.height-date.height)/2
            font.pixelSize:30
            color: "#ffffff"
        }

        Text {
            id: date
            font.pixelSize:30
            color: "#ffffff"
            anchors.horizontalCenter: time.horizontalCenter
            anchors.top: time.bottom
            anchors.topMargin: 14
        }
    }

    Rectangle{
        id:switePrompt
        anchors.horizontalCenter: swite.horizontalCenter
        anchors.top: switeTopRec.bottom
        anchors.topMargin: 237
        border.width: 2;
        border.color: "#cccccc";//边框的一些属性
        opacity: 0.7
        radius: 10;//圆角


        width: 270
        height: 150
        color: "#262626"
        Text {
            id: text1
            anchors.horizontalCenter: switePrompt.horizontalCenter
            anchors.top: switePrompt.top
            anchors.topMargin: 42
            font.pixelSize:26
            color: "#ffffff"
            text: "请刷卡"
        }

        Text {
            id: text2
            font.pixelSize:18
            color: "#ffffff"
            anchors.horizontalCenter: switePrompt.horizontalCenter
            anchors.bottom: switePrompt.bottom
            anchors.bottomMargin: 42
            opacity: 0.7
            text: "设备下方刷卡处"
        }

        Text {
            id: text3
            font.pixelSize:30
            color: "#ffffff"
            anchors.horizontalCenter: switePrompt.horizontalCenter
            anchors.bottom: switePrompt.bottom
        }

        Connections{
            target: qPro
            onSigQmlCarNum:{
                if(idenFlage === qsTr("虹膜和卡"))
                {
                    qPro.identFlag = true
                    root.viewShow = 1
                    iKIdentEnroll.m_Enroll = false
                    qPro.startSwipeCard = false
                }
                else if(idenFlage === qsTr("虹膜或卡"))
                {

                }
                else if(idenFlage === qsTr("只有卡"))
                {
                    text3.text = "hid:" + hid + "  pid:" + pid;
                }
            }
        }
    }

    Button{
        id:managementPagebtn
        anchors.bottom: btnlblpag.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: btnlblpag.horizontalCenter
        width: 39
        height: 46
        style: ButtonStyle{
            background: Rectangle{
                id:rect
                implicitWidth: 39
                implicitHeight: 46
                color: "#626e81"
                property string nomerPic: "qrc:///image/home/management.png"
                property string activePic: "qrc:///image/home/management_pressed.png"
                Image {
                    id: btnimagepag
                    width: 39
                    height: 46
                    source: control.pressed? activePic : nomerPic
                }
            }
        }

        onClicked:{
            qPro.startSwipeCard = false
            root.viewShow= 2
            console.log("root.viewShow = ",root.viewShow);
        }

    }
    Label{
        id:btnlblpag
        anchors.right: swite.right
        anchors.rightMargin: 70
        anchors.bottom: swite.bottom
        anchors.bottomMargin: 10
        text:"管理页面"
        font.pixelSize:18
        color:"#ffffff"
    }

}
