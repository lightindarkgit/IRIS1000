import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: ikirismode
    visible: false
    anchors.fill: parent
    color: "#80000000"

    Rectangle {
        id: irisModeDlg
        width: 630
        height: 300
        anchors.centerIn: parent
        radius: 10

        Label {
            id: titleLabel
            text: qsTr("采集虹膜选择")
            font.pixelSize: 28
            anchors.top: parent.top
            anchors.topMargin: 45
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#666666"
        }
        Label {
            id: bothLabel
            text: qsTr("双眼")
            font.pixelSize: 30
            anchors.top: titleLabel.bottom
            anchors.topMargin: 51
            anchors.left: parent.left
            anchors.leftMargin: 60
            color: "#333333"
        }
        Label {
            id: leftLabel
            text: qsTr("左眼")
            font.pixelSize: 30
            anchors.top: bothLabel.top
            anchors.left: bothCheckBox.right
            anchors.leftMargin: 40
            color: "#333333"
        }
        Label {
            id: rightLabel
            text: qsTr("右眼")
            font.pixelSize: 30
            anchors.top: leftLabel.top
            anchors.left: leftCheckBox.right
            anchors.leftMargin: 40
            color: "#333333"
        }

        ExclusiveGroup {
            id: modeGroup
        }

        CheckBox {
            id: bothCheckBox
            objectName: "bothEye"
            exclusiveGroup: modeGroup
            anchors.top: titleLabel.bottom
            anchors.topMargin: 34
            anchors.left: bothLabel.right
            anchors.leftMargin: 20
            style: checkStyle
            checked: true
        }
        CheckBox {
            id: leftCheckBox
            objectName: "leftEye"
            exclusiveGroup: modeGroup
            anchors.top: bothCheckBox.top
            anchors.left: leftLabel.right
            anchors.leftMargin: 20
            style: checkStyle
        }
        CheckBox {
            id: rightCheckBox
            objectName: "rightEye"
            exclusiveGroup: modeGroup
            anchors.top: leftCheckBox.top
            anchors.left: rightLabel.right
            anchors.leftMargin: 20
            style: checkStyle
        }

        Component {
            id: checkStyle
            CheckBoxStyle {
                indicator: Rectangle {
                    implicitHeight: 64
                    implicitWidth: 64
                    border.color: "#cccccc"
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

        Rectangle {
            id: btnBorder
            width: parent.width
            height: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 80
            color: "#cccccc"
        }

        Button {
            id: ensureBtn
            anchors.top: btnBorder.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            style: ButtonStyle {
                background: Rectangle {
                    radius: 10
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("确认")
                        color:  "#5aa5e6"
                        opacity: control.pressed ? 0.7 : 1.0
                        font.pixelSize: 36
                    }
                }
            }
            onClicked: {
                console.log(modeGroup.current.objectName);
                if(modeGroup.current.objectName == "leftEye")
                    qPro.irisEnrMode = 1;
                else if(modeGroup.current.objectName == "rightEye")
                    qPro.irisEnrMode = 2;
                else
                    qPro.irisEnrMode = 3;
                ikirismode.visible = false;
                viewShow  = 1;
                iKIdentEnroll.m_Enroll = true
                console.log("viewShow = ", viewShow);
                qPro.qmlStartEnroll = true;
            }
        }
    }
}
