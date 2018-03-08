import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//设备信息页
Rectangle {
    id: usersInfo
    width: 1280
    height: 720

    Rectangle{
        id: usersInfoTop
        anchors.top: usersInfo.top
        anchors.left: usersInfo.left
        anchors.right: usersInfo.right
        width: usersInfo.width
        height: 104
        color: "#626e81"

        Text {
            id: usersInfoText1
            anchors.verticalCenter: usersInfoTop.verticalCenter
            anchors.left: usersInfoTop.left
            anchors.leftMargin: 30
            font.pixelSize: 40
            color: "#ffffff"
            text: "个人信息"
        }
        Button {
            id: usersInfoBtn
            anchors.verticalCenter: usersInfoTop.verticalCenter
            anchors.right: usersInfoTop.right
            anchors.rightMargin: 30
            smooth: true
            style: ButtonStyle{
                background: Rectangle{
                    implicitWidth: 43
                    implicitHeight: 38
                    color:"#626e81"
                    property string nomerPic: "qrc:///image/topbar/back.png"
                    property string activePic: "qrc:///image/topbar/back_pressed.png"
                    Image {
                        source: control.pressed? activePic : nomerPic
                    }
                }
            }
            onClicked:{
                root.viewShow = (userManager.page2More == 1) ? 12 : 13; // 返回进入编辑更多之前的界面
                console.log("root.viewShow = ",root.viewShow);
            }
        }

    }

    Rectangle{
        id:usersInfoRct1
        anchors.top: usersInfoTop.bottom
        anchors.left: usersInfo.left
        anchors.right: usersInfo.right
        width: usersInfo.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: usersInfoName
            anchors.verticalCenter: usersInfoRct1.verticalCenter
            anchors.left: usersInfoRct1.left
            anchors.leftMargin: 30
            font.pixelSize: 36
            color: "#666666"
            text: "姓名"
        }
        TextField {
            id: nameInput
            anchors.left: usersInfoName.right
            anchors.leftMargin: 127
            font.pixelSize: 36
            placeholderText: "未填写"
            text: userManager.userName
            style: TextFieldStyle {
                textColor: nameInput.displayText =="未填写" ? "#999999" :"#333333"
                background: Rectangle {
                    implicitHeight: usersInfoRct1.height
                    implicitWidth: 1280 - usersInfoName.width
                    color: "#f0f0f0"
                }
            }
            onEditingFinished:  {   // 输入完成检查合法性
                // 暂时不需要检查
            }
        }

    }
    Rectangle{
        id: usersInfoRct2
        anchors.top: usersInfoRct1.bottom
        anchors.left: usersInfoRct1.left
        anchors.right: usersInfoRct1.right
        width: usersInfoRct1.width
        height: 104
        color: "#e9e9e9"

        Text {
            id: sexInfoName
            anchors.verticalCenter: usersInfoRct2.verticalCenter
            anchors.left: usersInfoRct2.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "性别"
        }
        Button {
            id: sexSelect
            anchors.left: sexInfoName.right
            anchors.leftMargin: 127
            style: ButtonStyle{
                background: Rectangle{
                    implicitHeight: usersInfoRct2.height
                    implicitWidth: 1280 - sexInfoName.width
                    color: "#e9e9e9"
                    Label {
                        anchors.verticalCenter:  parent.verticalCenter
                        anchors.left: parent.left
                        text: userManager.sex == "" ? "未填写" : userManager.sex
                        font.pixelSize:  36
                        color: userManager.sex =="" ? "#999999" :"#333333"
                    }
                }
            }
            onClicked: {
                iksex.visible = true;
            }
        }
    }
    Rectangle{
        id:usersInfoRct3
        anchors.top: usersInfoRct2.bottom
        anchors.left: usersInfoRct2.left
        anchors.right: usersInfoRct2.right
        width: usersInfoRct2.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: usersInfoOccupation
            anchors.verticalCenter: usersInfoRct3.verticalCenter
            anchors.left: usersInfoRct3.left
            anchors.leftMargin: 30
            font.pixelSize: 36
            color: "#666666"
            text: "职业"
        }
        TextField {
            id:  occupationInput
            anchors.left: usersInfoOccupation.right
            anchors.leftMargin: 127
            font.pixelSize: 36
            placeholderText: "未填写"
            text: userManager.profession
            style: TextFieldStyle {
                textColor: occupationInput.displayText =="未填写" ? "#999999" :"#333333"
                background: Rectangle {
                    implicitHeight: usersInfoRct3.height
                    implicitWidth: 1280 - usersInfoOccupation.width
                    color: "#f0f0f0"
                }
            }
        }

    }
    Rectangle{
        id: usersInfoRct4
        anchors.top: usersInfoRct3.bottom
        anchors.left: usersInfoRct3.left
        anchors.right: usersInfoRct3.right
        width: usersInfoRct3.width
        height: 104
        color: "#e9e9e9"

        Text {
            id: idInfoName
            anchors.verticalCenter: usersInfoRct4.verticalCenter
            anchors.left: usersInfoRct4.left
            anchors.leftMargin: 30
            font.pixelSize:36
            color: "#666666"
            text: "身份证号"
        }
        TextField {
            id: idInput
            anchors.left: idInfoName.right
            anchors.leftMargin: 55
            font.pixelSize: 36
            placeholderText: "未填写"
            text: userManager.idcard
            style: TextFieldStyle {
                textColor: idInput.displayText =="未填写" ? "#999999" :"#333333"
                background: Rectangle {
                    implicitHeight: usersInfoRct4.height
                    implicitWidth: 1280 - idInfoName.width
                    color: "#e9e9e9"
                }
            }
//            validator: RegExpValidator{regExp: /^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$)|(^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}$/}  ///    /[0-5][0-9][0-5][.][0-9]/}
            validator: RegExpValidator{regExp: /[0-9]{17}[0-9|x|X] | [0-9]{15}/}
        }
    }
    Rectangle{
        id:usersInfoRct5
        anchors.top: usersInfoRct4.bottom
        anchors.left: usersInfoRct4.left
        anchors.right: usersInfoRct4.right
        width: usersInfoRct4.width
        height: 104
        color: "#f0f0f0"

        Text {
            id: usersInfoAddress
            anchors.verticalCenter: usersInfoRct5.verticalCenter
            anchors.left: usersInfoRct5.left
            anchors.leftMargin: 30
            font.pixelSize: 36
            color: "#666666"
            text: "常用住址"
        }
        TextField {
            id:  addressInput
            anchors.left: usersInfoAddress.right
            anchors.leftMargin: 55
            font.pixelSize: 36
            placeholderText: "未填写"
            text: userManager.address
            style: TextFieldStyle {
                textColor: addressInput.displayText =="未填写" ? "#999999" :"#333333"
                background: Rectangle {
                    implicitHeight: usersInfoRct5.height
                    implicitWidth: 1280 - usersInfoAddress.width
                    color: "#f0f0f0"
                }
            }
        }
    }

    Button
    {
        id: usersInfo_cancel
        anchors.bottom: usersInfo.bottom
        anchors.bottomMargin: 0
        anchors.left: usersInfo.left
        anchors.leftMargin: 0
        width: 640
        height: 96
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 120
                implicitHeight: 96
                color:"#FFFFFF"
                border.width: 1
                border.color:"#cccccc"
                Label {
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "取消"
                    font.pixelSize:  36
                    color: usersInfo_cancel.pressed ? "#80666666" :"#B3666666"
                }
            }
        }
        onClicked:{
            root.viewShow = (userManager.page2More == 1) ? 12 : 13; // 返回进入编辑更多之前的界面
//            root.viewShow = 12
        }
    }
    Button
    {
        id: usersInfo_ok
        anchors.bottom: usersInfo.bottom
        anchors.bottomMargin: 0
        anchors.left: usersInfo_cancel.right
        anchors.leftMargin: 0
        width: 640
        height: 96
        smooth: true
        style: ButtonStyle{
            background: Rectangle{
                implicitWidth: 120
                implicitHeight: 96
                color:"#FFFFFF"
                border.width: 1
                border.color:"#cccccc"
                Label {
                    anchors.verticalCenter:  parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "确认"
                    font.pixelSize:  36
                    color: usersInfo_ok.pressed ? "#b35aa5e6" :"#ff5aa5e6"
                }
            }
        }
        onClicked:{
//            userManager.initPersonInfo();
//            root.viewShow = 12  // NOTIFY 回到新增用户界面？
            // 返回之前，按下确认，先把参数保存一遍
            userManager.userName = nameInput.text;  // 保存第一行 姓名
//            userManager.sex = iksex.sexstr; // 保存第二行 性别
            userManager.profession = occupationInput.text;  // 保存第三行 职业
            userManager.idcard = idInput.text;  // 保存第四行 身份证号   // NOTIFY 位数是否也写入reg中了
            userManager.address = addressInput.text;    // 保存第五行，地址
            root.viewShow = (userManager.page2More == 1) ? 12 : 13; // 返回进入编辑更多之前的界面
//            var reg =  /^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$)|(^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}$/
//            var reg = /[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9|x|X] | [0-9]{15}/
            var reg = /(^\d{15}$)|(^\d{18}$)|(^\d{17}(\d|X|x)$)/
            console.log( reg.test(idInput.text) + "   reg test");
        }
    }
    IKSex {
        id: iksex
    }
}
