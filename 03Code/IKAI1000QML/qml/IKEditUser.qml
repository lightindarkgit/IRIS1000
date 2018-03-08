import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: editperson  // 更改一下 ID 吧TextField
    width: 1280
    height: 720

    function disableAll() {
        cancelBtn.visible = false
        cancelBtn.enabled = false
        ensureBtn.visible = false
        ensureBtn.enabled = false
        idInput.enabled = false
        nameInput.enabled = false
        moreInfo.enabled = false
        isAdmin.enabled = false
        firstPswd.enabled = false
        secondPswd.enabled = false
        //        isSingle.enabled = false
    }

    function enableAll() {
        cancelBtn.visible = true
        cancelBtn.enabled = true
        ensureBtn.visible = true
        ensureBtn.enabled = true
        idInput.enabled = true
        nameInput.enabled = true
        moreInfo.enabled = true
        isAdmin.enabled = true
        firstPswd.enabled = true
        secondPswd.enabled = true
        //        isSingle.enabled = true
    }

    Rectangle {
        id: title
        anchors.top: parent.top
        width: parent.width
        height: 96
        color: "#626e81"

        Label {
            id: pageTitle
            text: qsTr("用户信息")
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 40
            color: "#ffffff"
        }

        Button {
            id: backBtn
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 50
                    implicitHeight: 43
                    color: "#626e81"  //设置为底色
                    Image {
                        id: backImg
                        source: control.pressed ? "qrc:///image/topbar/back_pressed.png" : "qrc:///image/topbar/back.png"
                    }
                }
            }
            onClicked: {
                disableAll();
                viewShow  = 11; // 用户列表界面
                console.log("viewShow = ", viewShow);
            }
        }

        Button {
            id: editBtn
            anchors.right: backBtn.left
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 44
                    implicitHeight: 48
                    color: "#626e81"  //设置为底色
                    Image {
                        id: editImg
                        source: control.pressed ? "qrc:///image/topbar/edit_pressed.png" : "qrc:///image/topbar/edit.png"
                    }
                }
            }
            onClicked: {
                enableAll();
            }
        }
    }

    property int tabView:0

    Rectangle {
        id: body
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#33363a"

        Label {
            id: userId
            text: qsTr("用户ID")
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 30
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        TextField {
            id: idInput
            enabled: false
            anchors.top: userId.bottom
            anchors.topMargin: 10
            anchors.left: userId.left
            font.pixelSize: 36
            //            text: userModel.getUserId(userListIndex)
            text: userManager.userId
            style: TextFieldStyle {
                textColor: "#ffffff"
                background: Rectangle {
                    radius: 10
                    implicitHeight: 64
                    implicitWidth: 460
                    color: "#262626"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                }
            }
            onEditingFinished: {
                // TODO 应该是填写完成就行验证
            }
        }

        Label {
            id: userName
            text: qsTr("用户名")
            anchors.top: idInput.bottom
            anchors.topMargin: 50
            anchors.left: userId.left
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        TextField {
            id: nameInput
            enabled: false
            anchors.top: userName.bottom
            anchors.topMargin: 10
            anchors.left: userId.left
            font.pixelSize: 36
            //            text: userModel.getUserName(userListIndex)
            text: userManager.userName
            style: TextFieldStyle {
                textColor: "#ffffff"
                background: Rectangle {
                    radius: 10
                    implicitHeight: 64
                    implicitWidth: 460
                    color: "#262626"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                }
            }
        }

        Button {
            id: moreInfo
            enabled: false
            anchors.top: nameInput.bottom
            anchors.topMargin: 10
            anchors.right: nameInput.right
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 24
                    implicitWidth: 100
                    color: "#33363a"
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("填写更多")
                        color: "#ffc600"
                        font.pixelSize: 24
                    }
                }
            }
            onClicked: {
                userManager.page2More = 2;  // 表示从编辑用户界面进入编辑更多界面
                viewShow = 15;  // 显示编辑更多界面
                console.log("viewShow = ", viewShow);
            }
        }

        Label {
            id: admin
            text: qsTr("管理员")
            anchors.top: nameInput.bottom
            anchors.topMargin: 70
            anchors.left: userId.left
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        CheckBox {
            id: isAdmin
            enabled: false
            anchors.top: admin.bottom
            anchors.topMargin: 10
            anchors.left: admin.left
            style: checkStyle
            checked: userManager.isAdmin;   // 根据是否管理员决定是否选择
            // TODO 对于设为管理员和取消管理员的响应函数
        }

        Label {
            id: verInfo
            text: qsTr("验证信息")
            anchors.top: userId.top
            anchors.left: idInput.right
            anchors.leftMargin: 140
            font.pixelSize: 28
            color: Qt.rgba(255,255,255,0.7)
        }

        Button {
            id: iris
            anchors.top: idInput.top
            anchors.left: idInput.right
            anchors.leftMargin: 140
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 0) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("虹膜")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView = 0
            }
        }

        Button {
            id: card
            anchors.top: idInput.top
            anchors.left: iris.right
            anchors.leftMargin: 11
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 1) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("卡")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView = 1
            }
        }

        Button {
            id: passwd
            anchors.top: idInput.top
            anchors.left: card.right
            anchors.leftMargin: 11
            style: ButtonStyle {
                background: Rectangle {
                    implicitHeight: 60
                    implicitWidth: 196
                    color: (tabView == 2) ? "#5aa5e6" : "#666666"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("密码")
                        color: "#ffffff"
                        font.pixelSize: 30
                    }
                }
            }
            onClicked: {
                tabView = 2
            }
        }

        Rectangle {
            width: 610
            height: 340
            anchors.top: iris.bottom
            anchors.left: iris.left
            border.color: Qt.rgba(204,204,204,0.7)
            border.width: 2
            radius: 10

            Rectangle {
                id: irisView    // 虹膜验证信息显示
                width: 610
                height: 340
                visible: (tabView == 0) ? true : false
                anchors.fill: parent
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10

                Component { // 虹膜分组显示，ListView的代理
                    id: irisListViewDelegate;
                    Item {
                        width: 584;
                        height: 255;
                        Rectangle {
                            anchors.fill: parent;
                            color: irisView.color;

                            Text {
                                id: irisGroupText;
                                anchors.top: parent.top;
                                anchors.topMargin: 30;
                                anchors.left: parent.left;
                                anchors.leftMargin: 50;
                                font.pixelSize:24;
                                font.family: "MicrosoftYaHei";
                                color: "#ffc600";
                                text: groupId
                            }

                            Button {
                                id: irisDelBtn;
                                anchors.top: parent.top;
                                anchors.topMargin: 35;
                                anchors.right: parent.right;
                                anchors.rightMargin: 35;
                                //                cheakable: (isHas == 1) ? true : false;
                                visible: (isHas == 1) ? true : false;
                                style: ButtonStyle {
                                    background: Rectangle {
                                        implicitHeight: 24
                                        implicitWidth: 100
                                        color: irisView.color
                                        Label {
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: qsTr("删除此组");
                                            color: "#ffc600";
                                            font.pixelSize: 24
                                            font.family: "MicrosoftYaHei";
                                        }
                                    }
                                }

                                onClicked: {
                                    //                                    irisModel.remove(index, 1); // 删除一项，下一项自动上移
                                    // 删除操作需要仔细考虑，model的删除引起虹膜2变到虹膜1的位置
                                    console.log("删除");
                                }
                            }

                            // 有虹膜图像时，显示虹膜图像
                            Image {
                                id: leftIris
                                //                                visible: (isHas != 0) ? true : false;
                                visible: true;
                                anchors.left: parent.left;
                                anchors.leftMargin: 23;
                                anchors.top: irisGroupText.bottom;
                                width: 254
                                height: 190
                                cache: false
                                //                                source: /*(isHas == 1 || isHas == 3) ? irisImageL :*/ "qrc:///image/userlist/noiris.png";
                                source: irisImageL
                            }
                            Image {
                                id: rightIris
                                //                                visible: (isHas != 0) ? true : false;
                                visible: true;
                                width: 254
                                height: 190
                                anchors.top: irisGroupText.bottom;
                                anchors.left: leftIris.right;
                                anchors.leftMargin: 30;
                                cache: false
//                                source: /*(isHas ==2 || isHas == 3) ? irisImageR :*/ "qrc:///image/userlist/noiris.png";
                                source: irisImageR
                            }

                            // 没有虹膜图像时，显示添加按钮
                            Button {
                                //                                visible: (isHas == 0) ? true : false
                                visible: false;
                                //                                enabled: (isHas == 0) ? true : false
                                anchors.centerIn: parent
                                style: ButtonStyle {
                                    background: Rectangle {
                                        implicitWidth: 96
                                        implicitHeight: 96
                                        color: "#262626"  //设置为底色
                                        Image {
                                            source: control.pressed ? "qrc:///image/userlist/user_add_pressed.png" : "qrc:///image/userlist/user_add.png"
                                        }
                                    }
                                }
                                onClicked: {  //开始注册
                                    ikirismode.visible = true;
                                }
                            }
                        }
                    }
                }

                ListModel {
                    id: irisModel;
                    ListElement {
                        groupId: "虹膜1"
                        //                            isHas: (qPro.irisDataNum > 0) ? qPro.irisGetMode : 0;   // 代表时候有虹膜数据，没有为0，有左眼为1,有右眼为2,双眼为3
                        isHas: 1;
//                        irisImageL: "image://irisData/irisImageL1"
//                        irisImageR: "image://irisData/irisImageR1"
                        irisImageL: "qrc:///image/userlist/noiris.png"
                        irisImageR: "qrc:///image/userlist/noiris.png"
                    }
                    ListElement {
                        groupId: "虹膜2"
                        //                            isHas: (qPro.irisDataNum > 1) ? qPro.irisGetMode : 0;
                        isHas: 0;
//                        irisImageL: "image://irisData/irisImageL2"
//                        irisImageR: "image://irisData/irisImageR2"
                        irisImageL: "qrc:///image/userlist/noiris.png"
                        irisImageR: "qrc:///image/userlist/noiris.png"
                    }
                    ListElement {
                        groupId: "虹膜3"
                        //                            isHas: (qPro.irisDataNum > 2) ? qPro.irisGetMode : 0;
                        isHas: 0;
//                        irisImageL: "image://irisData/irisImageL3"
//                        irisImageR: "image://irisData/irisImageR3"
                        irisImageL: "qrc:///image/userlist/noiris.png"
                        irisImageR: "qrc:///image/userlist/noiris.png"
                    }
                    ListElement {
                        groupId: "虹膜4"
                        //                            isHas: (qPro.irisDataNum > 3) ? qPro.irisGetMode : 0;
                        isHas: 0;
//                        irisImageL: "image://irisData/irisImageL4"
//                        irisImageR: "image://irisData/irisImageR4"
                        irisImageL: "qrc:///image/userlist/noiris.png"
                        irisImageR: "qrc:///image/userlist/noiris.png"
                    }
                }

                Rectangle { // 显示虹膜的区域
                    id: irisRect1;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    width: 584;
                    height: 310;

                    ListView {
                        id: irisListView;
                        anchors.fill: parent;
                        clip: true; // 不加的话显示会超出范围
                        boundsBehavior: Flickable.StopAtBounds
                        spacing: 0;
                        delegate: irisListViewDelegate;
                        model: irisModel;
                    }
                }

                Rectangle { // 滚动条
                    id:scrollbar;
                    anchors.right: parent.right;
                    anchors.top: parent.top;
                    width: 26;
                    height: irisListView.height;
                    color: "#4a4a4a";
                    border.width: 1;
                    border.color: "#666666";
                    clip: true;
                    Rectangle { // 按钮
                        id: button
                        x: 7
                        //view.visibleArea.yPosition表示一个变量,初始值为0,滚动条滚到底部时最大
                        y: irisListView.visibleArea.yPosition * scrollbar.height
                        width: 12
                        //滚动按钮的长度为view.height/view.contentHeight*scrollbar.height;与下方代码等价
                        height: irisListView.visibleArea.heightRatio * scrollbar.height;
                        color: "#999999";
                        radius: 7;

                        MouseArea { // 鼠标区域
                            id: mouseArea
                            anchors.fill: button
                            //使得按钮可以上下拖动
                            drag.target: button
                            drag.axis: Drag.YAxis
                            drag.minimumY: 0
                            drag.maximumY: scrollbar.height - button.height
                            // 拖动
                            onMouseYChanged: {
                                irisListView.contentY = button.y / scrollbar.height * irisListView.contentHeight
                            }
                        }
                    }
                }

                Button { // 显示下方虚拟卡号区域
                    anchors.bottom: parent.bottom;
                    height: 40;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    style: ButtonStyle {
                        background: Rectangle {
                            anchors.fill: parent;
                            color: "#454545";
                        }
                    }

                    Text {
                        anchors.fill: parent;
                        horizontalAlignment: Text.AlignHCenter;
                        verticalAlignment: Text.AlignVCenter;
                        color: "#ffc600";
                        font.pixelSize: 18;
                        font.family: "MicrosoftYaHei";
                        text: qsTr("虚拟卡号");
                    }

                    onClicked: {
                        console.log("clicked");
                    }
                }
            }
        }
        Rectangle {
            id: cardView
            width: 610
            height: 340
            visible: (tabView == 1) ? true : false
            anchors.fill: parent
            color: "#262626"
            border.color: Qt.rgba(204,204,204,0.7)
            border.width: 2
            radius: 10

            Label {
                text: qsTr("请刷卡")
                anchors.centerIn: parent
                font.pixelSize: 36
                color: Qt.rgba(255,255,255,0.7)
            }
        }
        Rectangle {
            id: pswdView
            width: 610
            height: 340
            visible: (tabView == 2) ? true : false
            anchors.fill: parent
            color: "#262626"
            border.color: Qt.rgba(204,204,204,0.7)
            border.width: 2
            radius: 10

            TextField {
                id: firstPswd
                enabled: false
                anchors.top: parent.top
                anchors.topMargin: 84
                anchors.left: parent.left
                anchors.leftMargin: 105
                style: TextFieldStyle {
                    textColor: Qt.rgba(255,255,255,0.5)
                    font.pixelSize: 24
                    background: Rectangle {
                        radius: 10
                        implicitHeight: 60
                        implicitWidth: 400
                        color: Qt.rgba(102,102,102,0.3)
                        border.color: Qt.rgba(204,204,204,0.7)
                        border.width: 2
                    }
                }
            }
            TextField {
                id: secondPswd
                enabled: false
                anchors.top: firstPswd.bottom
                anchors.topMargin: 50
                anchors.left: parent.left
                anchors.leftMargin: 105
                font.pixelSize: 24
                style: TextFieldStyle {
                    textColor: Qt.rgba(255,255,255,0.5)
                    background: Rectangle {
                        radius: 10
                        implicitHeight: 60
                        implicitWidth: 400
                        color: Qt.rgba(102,102,102,0.3)
                        border.color: Qt.rgba(204,204,204,0.7)
                        border.width: 2
                    }
                }
            }
        }
    }

    Button {
        id: cancelBtn
        visible: false
        enabled: false
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 96
                implicitWidth: 640
                color: "#262626"
                border.color: "#cccccc"
                border.width: 1
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("取消")
                    color: control.pressed ? Qt.rgba(255,255,255, 0.5) :Qt.rgba(255,255,255,0.7)
                    font.pixelSize: 36
                }
            }
        }
        onClicked: {
            disableAll();
            viewShow  = 11;    // 修改完成后返回用户列表
            console.log("viewShow = ", viewShow);
        }
    }

    Button {
        id: ensureBtn
        visible: false
        enabled: false
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 96
                implicitWidth: 640
                color: "#262626"
                border.color: "#cccccc"
                border.width: 1
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("完成")
                    color: control.pressed ? Qt.rgba(90,165,230,0.7) : Qt.rgba(90,165,230,1.0)
                    font.pixelSize: 36
                }
            }
        }
        onClicked: {
            // 检测用户ID不能为空，和 IKAddUser.qml 确认按键相同
            if(idInput.text == "")
            {
                ikMessageAddUser.setInfo("请输入用户ID")
                ikMessageAddUser.visible = true
                ikMessageAddUser.startTimer()
            }
            // 检测用户名不能为空，和 IKAddUser.qml 确认按键相同
            else if(nameInput.text == "")
            {
                ikMessageAddUser.setInfo("请输入用户姓名")
                ikMessageAddUser.visible = true
                ikMessageAddUser.startTimer()
            }
            // 检测是否勾选了管理员chekcbox
            if (userManager.isAdmin != isAdmin.checked) // 选中管理员的chekbox有改变
            {
                userManager.isAdmin = isAdmin.checked;
                if (isAdmin.checked)    // 为勾选，添加管理员
                {
                    // TODO 添加管理员是否需要特殊处理
                }
                else
                {
                    // TODO 取消管理员是否需要特殊处理
                }
            }
            else
            {
                userManager.userId = idInput.text;
                userManager.userName = nameInput.text;
                userManager.updateUser();
                userModel.reload();
                // TODO 修改成功是否有提示
                disableAll();
                viewShow  = 11;    // 修改完成后返回用户列表
                console.log("viewShow = ", viewShow);
            }

            console.log("userId = ", idInput.text);
        }
    }

    Connections{
        target: qPro;
        onSigUpdateEditIrisImg: {
//            leftIris.source = "";
//            rightIris.source = "";
//            leftIris.source = left > 0 ? "image://IrisImgLeft" : "qrc:///image/userlist/noiris.png";
//            rightIris.source = right > 0 ? "image://IrisImgRight" : "qrc:///image/userlist/noiris.png";
            if (left > 0)
            {
                irisModel.set(0, {"irisImageL": "image://IrisImgLeft"});
            }
            else
            {
                irisModel.set(0, {"irisImageL": "qrc:///image/userlist/noiris.png"});
            }
            if (right > 0)
            {
                irisModel.set(0, {"irisImageR": "image://IrisImgRight"});
            }
            else
            {
                irisModel.set(0, {"irisImageR": "qrc:///image/userlist/noiris.png"});
            }
        }
    }

    Component {
        id: checkStyle
        CheckBoxStyle {
            indicator: Rectangle {
                implicitHeight: 64
                implicitWidth: 64
                color: "#262626"
                border.color: Qt.rgba(204,204,204,0.7)
                border.width: 2
                radius: 10
                Image {
                    visible: control.checked
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:///image/userlist/check.png"
                }
            }
        }
    }
}

/*
        TabView {
            id: tabView
            width: 610
            anchors.top: idInput.top
            anchors.left: verInfo.left
            anchors.bottom: isSingle.bottom

            Tab { title: "虹膜" }
            Tab { title: "卡" }
            Tab { title: "密码" }

            style: TabViewStyle {
                tab: Item {
                    implicitHeight: 60
                    implicitWidth: 206
                    Rectangle {
                        width: parent.width - 11
                        height: parent.height
                        anchors.top: parent.top
                        anchors.left: parent.left
                        color: styleData.selected ? "#5aa5e6" : "#666666"
                        border.color: Qt.rgba(204,204,204,0.7)
                        border.width: 2
                        radius: 10
                        Text {
                            id: text
                            text: styleData.title
                            font.pixelSize: 30
                            anchors.centerIn: parent
                            color: "#ffffff"
                        }
                    }
                    Rectangle {
                        width: 11
                        height: parent.height
                        anchors.top: parent.top
                        anchors.right: parent.right
                        visible: false
                    }
                }
                frame: Rectangle {
                    color: "#262626"
                    border.color: Qt.rgba(204,204,204,0.7)
                    border.width: 2
                    radius: 10
                }
            }
        } */
