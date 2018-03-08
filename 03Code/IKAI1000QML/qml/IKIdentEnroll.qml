import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//虹膜注册、识别、登录页面
Rectangle {
    id:face1
    width: 1280
    height: 720
    property bool m_pswdValidabtn_visible: false;
    property bool m_Enroll:false

    //背景图片
    Image {
        id: rocket
        fillMode: Image.TileHorizontally
        smooth: true
        source: "qrc:///image/setImage/user_bg.png"
    }

    //RGB image
    Image {
        id: faceImage
        anchors.top: face1.top
        anchors.bottom: face1.bottom
        anchors.left: face1.left
        anchors.leftMargin: 320
        width: 640
        height: face1.height
        fillMode: Image.TileHorizontally
        smooth: true
        cache: false
    }
    Connections {
        target: qPro;
        onSigUpdateImageRGB:{
            faceImage.source= "";
            faceImage.source= "image://screenRGB";//image:必须
            qPro.ableCapImage = true;
        }
    }
//显示虹膜图像，测试用，正式版可去掉
    Image {
        id: showImageIris
        x: 20
        y: 150
        width: 240
        height: 135
        cache: false
//        mirror: true
    }
    Connections {
        target: qPro;
        onSigUpdateImageIris:{
            showImageIris.source= "";
            showImageIris.source= "image://screenIris";//image:必须
            qPro.ableCapIris = true;
        }
    }

    //眼镜、美瞳图标显示
    Rectangle{
        id:eyeFlageLbl
        anchors.top: face1.top
        anchors.left: face1.left
        width: 320
        height:96
        color: "#626e81"

        Image {
            id:image1
            anchors.verticalCenter: eyeFlageLbl.verticalCenter
            anchors.left: eyeFlageLbl.left
            anchors.leftMargin: 52
            width: 64
            height:64
            source: "qrc:///image/topbar/glasses.png"
        }

        Image {
            id:image2
            anchors.verticalCenter: eyeFlageLbl.verticalCenter
            anchors.left: image1.right
            anchors.leftMargin: 12
            width: 64
            height:64
            source: "qrc:///image/topbar/contactlenses.png"
        }

        Image {
            id:image3
            anchors.verticalCenter: eyeFlageLbl.verticalCenter
            anchors.left: image2.right
            anchors.leftMargin: 12
            width: 64
            height:64
            source: "qrc:///image/topbar/eye.png"
        }
    }

    //注册识别距离提示
    Rectangle{
        id:distanceTipsLbl
        anchors.top: face1.top
        anchors.left: faceImage.left
        anchors.right: faceImage.right
        width: 640
        height:96
        //        color: "#5aa5e6"
        color: qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")

        opacity:0.7
        Text {
            id: name
            anchors.horizontalCenter: distanceTipsLbl.horizontalCenter
            anchors.verticalCenter: distanceTipsLbl.verticalCenter
            font.pixelSize:40
            font.bold: true
            color: "#ffffff"
            //            text: qsTr("请退后")
            text:qPro.msgText            
        }
    }

    Rectangle{
        id:rectop
        visible: m_Enroll ? true: (rgbChangeBtn.changeFaceImage ? true:false)
        opacity:0.7
        width: 600
        height:5
        anchors.top: distanceTipsLbl.bottom
        anchors.topMargin:45
        anchors.horizontalCenter: faceImage.horizontalCenter
        color: qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
    }
    Rectangle{
        id:recbottom
        visible: m_Enroll ? true: (rgbChangeBtn.changeFaceImage ? true:false)
        opacity:0.7
        width: 600
        height:5
        anchors.top: rectop.bottom
        anchors.topMargin:260
        anchors.horizontalCenter: faceImage.horizontalCenter
        color: qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
    }
    ProgressBar{
        id:progress1
        orientation: Qt.Vertical
        visible: m_Enroll ? true: (rgbChangeBtn.changeFaceImage ? true:false)
        anchors.top: rectop.bottom
        anchors.left: rectop.left
        width: 20
        height: 260
        minimumValue: 0;
        maximumValue: 100;
        value: qPro.leftNum;

        style: ProgressBarStyle{
            id: progressStyle1;
            background: Rectangle{
                color: m_Enroll ? "#ffffff" : distanceTipsLbl.color
                opacity: 0.7
                //                radius: 28
            }
            progress: Rectangle{
                id: proRec1
                color:qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
            }
        }
    }
    ProgressBar{
        id:progress2
        orientation: Qt.Vertical
        visible: m_Enroll ? true: (rgbChangeBtn.changeFaceImage ? true:false)
        anchors.top: rectop.bottom
        anchors.right: rectop.right
        width: 20
        height: 260
        minimumValue: 0;
        maximumValue: 100;
        value: qPro.rightNum;

        style: ProgressBarStyle{
            id: progressStyle2;
            background: Rectangle{
                color: m_Enroll ? "#ffffff" : distanceTipsLbl.color
                opacity: 0.7
            }
            progress: Rectangle{
                id: proRec2
                color:qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
            }
        }
    }

    Rectangle{
        id:recleft
        visible: m_Enroll ? false: (rgbChangeBtn.changeFaceImage ? false:true)
        opacity:0.7
        width: 10
        height:624
        anchors.top: distanceTipsLbl.bottom
        anchors.left: faceImage.left
        color: qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
    }
    Rectangle{
        id:recright
        visible: m_Enroll ? false: (rgbChangeBtn.changeFaceImage ? false:true)
        opacity:0.7
        width: 10
        height:624
        anchors.top: distanceTipsLbl.bottom
        anchors.right: faceImage.right
        color: qPro.msgText === "请退后"? "#5aa5e6":(qPro.msgText === "请靠近"? "#d8293b":"green")
    }
    function distanceTipColor()
    {
        if(qPro.msgText === "请退后")
        {
            distanceTipsLbl.color = "#5aa5e6"
        }
        else if(qPro.msgText === "请靠近")
        {
            distanceTipsLbl.color = "#d8293b"
        }
        else
        {
            distanceTipsLbl.color = "green"
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
    //时间显示
    Rectangle{
        id:timeViewLbl
        visible: m_Enroll? false:true
        anchors.top: face1.top
        anchors.right: face1.right
        width: 320
        height:96
        color: "#626e81"

        Text {
            id: time
            anchors.horizontalCenter: timeViewLbl.horizontalCenter
            anchors.top: timeViewLbl.top
            anchors.topMargin: (96-14-time.height-date.height)/2
            font.pixelSize:30
            color: "#ffffff"
        }

        Text {
            id: date
            font.pixelSize:30
            color: "#ffffff"
            anchors.horizontalCenter: timeViewLbl.horizontalCenter
            anchors.top: time.bottom
            anchors.topMargin: 14
        }
    }
    Button{
        id:returnBtn
        visible: m_Enroll
        anchors.top: face1.top
        anchors.right: face1.right
        width: 320
        height:96
        style: ButtonStyle{
            background: Rectangle{
                id:returnBtnRec
                color: "#626e81"
                implicitWidth: 320
                implicitHeight: 96
                Text {
                    id: returnBtnText
                    anchors.horizontalCenter: returnBtnRec.horizontalCenter
                    anchors.verticalCenter: returnBtnRec.verticalCenter
                    font.pixelSize:30
                    color: "#ffffff"
                    text: "返回"
                }
            }
        }
        onClicked: {
            viewShow  = 12;
            qPro.identFlag = false
        }
    }
        //密码验证按钮
    Button{
            id:pswdValidabtn
            anchors.left:face1.left
            anchors.bottom: face1.bottom
            visible: m_Enroll? false : m_pswdValidabtn_visible

            width: 320;
            height: 96;
            style: ButtonStyle{
                background: Rectangle{
                    id: pswdValidaRec
                    implicitWidth: 320
                    implicitHeight: 96
                    color: "#262626"
                    property string nomerPic: "qrc:///image/home/lock.png"
                    property string activePic: "qrc:///image/home/lock_pressed.png"

                    Image {
                        id: btnimage
                        anchors.horizontalCenter: pswdValidaRec.horizontalCenter
                        anchors.top: pswdValidaRec.top
                        anchors.topMargin:(40-btnlbl.height)/2
                        width: 39
                        height: 46
                        fillMode: Image.TileHorizontally
                        smooth: true
                        source: control.pressed? activePic : nomerPic
                    }

                    Label{
                        id:btnlbl
                        anchors.horizontalCenter: pswdValidaRec.horizontalCenter
                        anchors.top:btnimage.bottom
                        anchors.topMargin: 10
                        text:"密码验证"
                        font.pixelSize:18
                        color:"#ffffff"
                    }
                }
            }

            onClicked:{
                qPro.identFlag = false
                root.viewShow= 2
            }

        }

        //管理页面按钮
    Button{
            id:managementPagebtn
            anchors.right: face1.right
            anchors.bottom: face1.bottom
            visible: m_Enroll? false:true

            width: 320;
            height: 96;
            style: ButtonStyle{
                background: Rectangle{
                    id:rect
                    implicitWidth: 320
                    implicitHeight: 96
                    color: "#262626"
                    property string nomerPic: "qrc:///image/home/management.png"
                    property string activePic: "qrc:///image/home/management_pressed.png"
                    Image {
                        id: btnimagepag
                        anchors.horizontalCenter: rect.horizontalCenter
                        anchors.top: rect.top
                        anchors.topMargin:(40-btnlblpag.height)/2
                        width: 39
                        height: 46
                        source: control.pressed? activePic : nomerPic
                    }
                    Label{
                        id:btnlblpag
                        anchors.horizontalCenter: rect.horizontalCenter
                        anchors.top:btnimagepag.bottom
                        anchors.topMargin: 10
                        text:"管理页面"
                        font.pixelSize:18
                        color:"#ffffff"
                    }
                }
            }

            onClicked:{  //停止识别，注册
                if(m_Enroll)
                {
                    qPro.qmlStartEnroll = false
                }
                else
                {
                    qPro.identFlag = false
                }
                root.viewShow= 2
                console.log("root.viewShow = ",root.viewShow);
            }

        }

        //RGB图像切换按钮
    Button{
            id:rgbChangeBtn
            visible: m_Enroll? false:true
            anchors.horizontalCenter: face1.horizontalCenter
            anchors.bottom: face1.bottom
            anchors.bottomMargin: 50
            width: 160
            height: 80
            opacity:1
            signal itemClicked()
            property bool changeFaceImage:true                      //true默认显示虹膜识别

            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 160
                    implicitHeight: 80
                    radius: 10
                    property string nomerFacePic: "qrc:///image/other/face.png"
                    property string activeFacePic: "qrc:///image/other/face_pressed.png"
                    property string nomerIrisPic: "qrc:///image/other/iris.png"
                    property string activeIrisPic: "qrc:///image/other/iris_pressed.png"

                    Image {
                        id:rgbChangeImg
                        source: {
                            if(rgbChangeBtn.changeFaceImage)
                            {
                                control.pressed ? activeFacePic : nomerFacePic
                            }
                            else
                            {
                                control.pressed ? activeIrisPic : nomerIrisPic
                            }
                        }
                    }
                }
            }

            onClicked: {
                changeFaceImage = changeFaceImage ? false : true
            }
        }

    Connections {
        target: qPro;
        onCppEnrollResult:{
            console.log("enroll resut is " + result)
            //收到注册结果 要进行 弹 窗 并切换界面
        }
    }
}
