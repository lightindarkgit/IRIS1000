import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Enterprise.VirtualKeyboard 2.0
//import an.qt.testclass 1.0
import QtQuick.Dialogs 1.2

Window {
    id: window1
    visible: true
    width: 1280
    height: 720
    title: qsTr("中科虹霸")
    property int fps: 0
    property int frameCounter: 0

    //qml取图测试
        Item {
            id: itme
            x: 280
            y: 280
            width: parent.width
            height: parent.height
            rotation:270

            //        TestClass {
            //            id:testcls;
            //        }

//            Text {
//                id:username;
//                width: 70
//                height: 40;
//                x:100
//                y: 400
//                font.pixelSize: 20;
//                text: "用户名:";
//            }

//            TextInput {
//                id: usernameInput;
//                width: 70;
//                height: 40;
//                x: 300
//                y: 400
//                font.pixelSize: 20;
//                text: "username";
//            }

//            function change(button, algorithm){
//                switch(algorithm)
//                {
//                case 0:
//                    button.text = "打开OV2710设备";
//                    break;
//                case 1:
//                    button.text = "关闭OV2710设备";
//                    break;
//                }
//            }

            Button {
                id:openIrisBtn;
                width: 260;
                height: 60;
                x:100
                y: 500
                style:ButtonStyle{
                    label:Text {
                        id: name
                        text: qsTr("打开OV2710设备");
                        font.pixelSize:  30
                    }
                }
                onClicked: {
                    qPro.slotOnBtnOpenIrisDevClicked();
                    //                console.log("============")
                    //                change(openIrisBtn, 1);
                }

            }

            Button {
                id:openRGBBtn;
                width: 260;
                height: 60;
                x:380
                y: 500
                text: "打开OV5640设备";
                style:ButtonStyle{
                    label:Text {
                        id: name1
                        text: "打开OV5640设备";
                        font.pixelSize:  30
                    }
                }
                onClicked: {
                    qPro.slotOnBtnOpenRGBDevClicked();
                }
            }

            Button {
                id:saveImgIrisBtn;
                width: 260;
                height: 60;
                x:100
                y: 600
                style:ButtonStyle{
                    label:Text {
                        id: name2
                        text: "保存OV2710";
                        font.pixelSize:  30
                    }
                }
                onClicked: {
                    qPro.slotOnBtnSaveImgIrisDevClicked();
                }
            }
            Button {
                id:saveImgRGBBtn;
                width: 260;
                height: 60;
                x:380
                y: 600
                style:ButtonStyle{
                    label:Text {
                        id: name3
                        text: "保存OV5640";
                        font.pixelSize:  30
                    }
                }
                onClicked: {
                    qPro.slotOnBtnSaveImgRGBDevClicked();
                }
            }

            Image {
                id: showImageRGB
                x: 700
                y: 46
                width: 480
                height: 640
                cache: false
                //            source: "qrc:///image/res/pass.png"
            }

            Connections {
                target: qPro;
                onSigUpdateImageRGB:{
                    showImageRGB.source= "";
                    showImageRGB.source= "image://screenRGB";//image:必须
//                    ++frameCounter;
                }
            }

            Image {
                id: showImageIris
                x: 20
                y: 46
                width: 480
                height: 270
                cache: false
            }
            Connections {
                target: qPro;
                onSigUpdateImageIris:{
                    showImageIris.source= "";
                    showImageIris.source= "image://screenIris";//image:必须
                    //                console.log("============")
//                    ++frameCounter;
                }
            }
//            Timer {
//                interval: 1000
//                repeat: true
//                running: true
//                onTriggered: {
//                    fps = frameCounter
//                    frameCounter = 0
//                    console.log("qml framerate is:",window1.fps);
//                }
//            }

        }

    //qml软键盘测试
    //        Item {
    //            x: 0
    //            y: 0
    //            width: parent.width
    //            height: parent.height

    //            Item {
    //                id: appContainer
    //                width: Screen.width < Screen.height ? parent.height : parent.width
    //                height: Screen.width < Screen.height ? parent.width : parent.height
    //                anchors.centerIn: parent
    //                rotation: Screen.width < Screen.height ? 270 : 0

    //                TextField {
    //                    id:textField;
    //                    width: 800;
    //                    height: 50;
    //                    y:10
    //                    anchors.horizontalCenter: parent.horizontalCenter;
    //                    font.pixelSize: 20;
    //                    text: "虚拟键盘测试";
    //                }

    //                /*  Keyboard input panel.

    //                    The keyboard is anchored to the bottom of the application.
    //                */
    //                InputPanel {
    //                    id: inputPanel
    //                    z: 99
    //                    y: appContainer.height
    //                    anchors.left: parent.left
    //                    anchors.right: parent.right
    //                    states: State {
    //                        name: "visible"
    //                        /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
    //                            but then the handwriting input panel and the keyboard input panel can be visible
    //                            at the same time. Here the visibility is bound to InputPanel.active property instead,
    //                            which allows the handwriting panel to control the visibility when necessary.
    //                        */
    //                        when: inputPanel.active
    //                        PropertyChanges {
    //                            target: inputPanel
    //                            y: appContainer.height - inputPanel.height
    //                        }
    //                    }
    //                    transitions: Transition {
    //                        from: ""
    //                        to: "visible"
    //                        reversible: true
    //                        ParallelAnimation {
    //                            NumberAnimation {
    //                                properties: "y"
    //                                duration: 250
    //                                easing.type: Easing.InOutQuad
    //                            }
    //                        }
    //                    }
    //    //                AutoScroller {}
    //                }
    //            }
    //        }

    //qml 弹窗测试
//    Item {
//        x: 0
//        y: 0
//        width: parent.width
//        height: parent.height
////                rotation:270

//        Button {
//            id:testBtn;
//            width: 260;
//            height: 60;
//            x:100
//            y: 500
//            style:ButtonStyle{
//                label:Text {
//                    id: idname
//                    text: qsTr("打开OV2710设备");
//                    font.pixelSize:  30
//                }
//            }
//            onClicked: {
//                myMsgbox.open();
//            }
//        }

//        MessageDialog
//        {
//            id:myMsgbox
//            //            width: 500
//            //            height: 260
//            standardButtons: StandardButton.Yes | StandardButton.No
//            modality: Qt.ApplicationModal
//            title: "确认退出"
//            text:"你确定要退出商旅平台吗？"
//            //            Component.onCompleted: visible = true
//            onYes:
//            {
//                //                Qt.quit();
//                window1.close();
//            }
//        }
//    }

}
