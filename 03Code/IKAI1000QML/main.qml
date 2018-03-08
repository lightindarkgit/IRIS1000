import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Enterprise.VirtualKeyboard 2.0
import  "./qml"
Window {
    id:root
    visible: true
    width: 1280
    height: 720
    property int viewShow:(iKUsersSet.initUserVerifyText === qsTr("虹膜和卡") ||
                        iKUsersSet.initUserVerifyText === qsTr("只有卡"))? (qPro.startSwipeCard = true&&16):
                        (iKUsersSet.initUserVerifyText === qsTr("虹膜或卡") ? (qPro.startSwipeCard = true)&&(qPro.identFlag=true)&&1:((qPro.identFlag=true)&&1))
    property bool irisEnrSuccess:false
    property int userListIndex:0

    Item {
        id: appContainer
        width: Screen.width < Screen.height ? parent.height : parent.width
        height: Screen.width < Screen.height ? parent.width : parent.height
        anchors.centerIn: parent
        rotation: Screen.width < Screen.height ? 270 : 0
        IKIdentEnroll {  //注册识别界面
            id:iKIdentEnroll
            anchors.fill:parent
            visible: viewShow == 1
        }
        IKManage{  //管理主页界面
                id:iKManage
                anchors.fill:parent
                visible: viewShow == 2
            }
        IKSettings {  //设置界面
                id:iKSettings
                anchors.fill:parent
                visible: viewShow == 3
            }
        IKNormalSet {  //基本设置界面
                id:iKNormalSet
                anchors.fill:parent
                visible: viewShow == 4
            }
        IKDeviceInfo {  //设备信息界面
                id:iKDeviceInfo
                anchors.fill:parent
                visible: viewShow == 5
            }
        IKIOSetting {   //接口设置界面
                id:iKIOSetting
                anchors.fill:parent
                visible: viewShow == 6
            }
        IKUsersSet { //用户设置界面
                id:iKUsersSet
                anchors.fill:parent
                visible: viewShow == 7
                initUserVerifyText: qsTr("虹膜和卡")
            }
        IKCommuncation {  //通信设置界面
                id:iKCommuncation
                anchors.fill:parent
                visible: viewShow == 8
            }
        IKDataManage {    //数据管理界面
                id:iKDataManage
                anchors.fill:parent
                visible: viewShow == 9
            }
        IKInitialization {   //初始化设置界面
                id:iKInitialization
                anchors.fill:parent
                visible: viewShow == 10
            }
        IKUsersList{  //用户列表
                id:iKUsersList
                anchors.fill:parent
                visible: viewShow == 11
            }
        IKAddUser{  //新增用户
            id:iKAddUsers
            anchors.fill:parent
            visible: viewShow == 12
        }
        IKEditUser{  //编辑用户
                id:iKEditUsers
                anchors.fill:parent
                visible: viewShow == 13
            }
        IKDelete{  //删除用户
                id:iKDelete
                anchors.fill:parent
                visible: viewShow == 14
            }
        IKEditMore{
            id:ikEditMore
            anchors.fill:parent
            visible: viewShow == 15
        }
        IKSwite{
            id:ikSwite
            anchors.fill:parent
            visible: viewShow == 16
        }

        IKMessageIdentResult{
            id:ikMessageIdentResult
            anchors.fill:parent
            visible: false
        }
        IKMessageAddResult
        {
            id:ikMessageAddUser
            anchors.fill:parent
            visible: false
        }

        InputPanel {
            id: inputPanel
            z: 99
            y: appContainer.height
            anchors.left: parent.left
            anchors.right: parent.right
            states: State {
                name: "visible"
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: appContainer.height - inputPanel.height
                }
            }
            transitions: Transition {
                from: ""
                to: "visible"
                reversible: true
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
