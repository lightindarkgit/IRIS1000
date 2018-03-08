import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id:root
    visible: true
    width: 1280
    height: 720

    title: qsTr("Hello World")
    property int viewShow:0

    Item {
        x: 0
        y: 0
        width: parent.width
        height: parent.height

        Rectangle {
            id:mainRect
            visible: true
            color:"red"
            width: Screen.width < Screen.height ? parent.height : parent.width
            height: Screen.width < Screen.height ? parent.width : parent.height
            anchors.centerIn: parent
            rotation: Screen.width < Screen.height ? 270 : 0

            Button{
                width: 120;
                height: 60;
                style:ButtonStyle{
                    label:Text {
                        text: qsTr("1");
                        font.pixelSize:  30
                    }
                }

                onClicked:{

                    viewShow = 1;
                    iKIdentEnroll.m_pswdValidabtn_visible = true
                    console.log("viewShow = ",viewShow);
                }

            }

            IKIdentEnroll{
                id:iKIdentEnroll
                anchors.fill:parent
                visible: viewShow == 1
            }

            IKManage{
                id:iKManage
                anchors.fill:parent
                visible: viewShow == 2
            }

            IKSettings{
                id:iKSettings
                anchors.fill:parent
                visible: viewShow == 3
            }
            IKNormalSet{
                id:iKNormalSet
                anchors.fill:parent
                visible: viewShow == 4
            }
            IKDeviceInfo{
                id:iKDeviceInfo
                anchors.fill:parent
                visible: viewShow == 5
            }
            IKIOSetting{
                id:iKIOSetting
                anchors.fill:parent
                visible: viewShow == 6
            }

            IKUsersSet{
                id:iKUsersSet
                anchors.fill:parent
                visible: viewShow == 7
            }
            IKCommuncation{
                id:iKCommuncation
                anchors.fill:parent
                visible: viewShow == 8
            }
            IKDataManage{
                id:iKDataManage
                anchors.fill:parent
                visible: viewShow == 9
            }
            IKInitialization{
                id:iKInitialization
                anchors.fill:parent
                visible: viewShow == 10
            }
        }
    }
}
