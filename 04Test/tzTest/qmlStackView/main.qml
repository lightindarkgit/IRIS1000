import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2

Window {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("StackViewDemo")

    Rectangle {

        id:mainRect

        visible: true
        color: "red"

        x:80
        y:300

        width: 640

        height: 480

        rotation: 270

        StackView {
            id: stack;
            anchors.centerIn: parent;
            width: 640;
            height: 480;
            property var home: null;

            Text {
                width: 120;
                height: 60;
                text: "Click to create first page";
                font.pointSize: 50;
                font.bold: true;
                color: "blue";
                anchors.centerIn: parent;
                MouseArea {
                    anchors.fill: parent;
                    onClicked:{
                        if(stack.depth == 0)stack.push(page1);
                        stack.completeTransition();
                    }
                }
            }
        }
        Component {
            id: page1;


            Rectangle {

                width: 640

                height: 480

                color:"#0034aa"

                Button{
                    width: 120;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"2"
                            font.pixelSize:  30
                        }
                    }

                    //        anchors{left: view1.left;leftMargin:80}

                    onClicked:{
                        stack.push(page2);
                        stack.completeTransition();
                    }

                }

            }
        }
        Component {
            id: page2;

            Rectangle {

                id:t1

                width: 640

                height: 480

                color:"#33aaaa"

                Button{
                    width: 120;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"3"
                            font.pixelSize:  30
                        }
                    }

                    //        anchors{left:view2.left;leftMargin:160}

                    onClicked:{
                        stack.push(page3);
                        stack.completeTransition();
                    }

                }

            }
        }
        Component {
            id: page3;

            Rectangle {

                id:t2

                width: 640

                height: 480

                color:"#331aff"

                Button{
                    width: 120;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"4"
                            font.pixelSize:  30
                        }
                    }

                    //        anchors{left: view3.left;leftMargin:200}

                    onClicked:{
                        stack.push(page4);
                        stack.completeTransition();
                    }

                }

            }
        }
        Component {
            id: page4;

            Rectangle {

                id:t3

                width: 640

                height: 480

                color:"green"

                Button{
                    id:btnInit
                    width: 120;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"5"
                            font.pixelSize:  30
                        }
                    }

                    //        anchors{left: view4.left;leftMargin:260}

                    onClicked:{
                        if(stack.depth > 0) stack.pop(stack.initialItem);
                        stack.completeTransition();
                    }

                }
                Button{
                    id:btnClear
                    width: 120;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"clear"
                            font.pixelSize:  30
                        }
                    }
                    anchors.left: btnInit.right;
                    anchors.rightMargin: 20;

                    onClicked:{
                        if(stack.depth > 0)  stack.clear();
                        stack.completeTransition();
                    }

                }
                Button{
                    id:btnInto3
                    width: 240;
                    height: 60;
                    style:ButtonStyle{
                        label:Text {
                            text:"into page3"
                            font.pixelSize:  30
                        }
                    }
                    anchors.left: btnClear.right;
                    anchors.rightMargin: 20;

                    onClicked:{
//                        var resultItem = stack.get(2);

                        var resultItem = stack.find(
                                    function(item){
//                                        console.log(item.text);
                                        return item.Stack.index === 1;
                                    }
                                    );

                        if(resultItem !== null)stack.pop(resultItem);
                        stack.completeTransition();
                    }

                }

            }
        }
    }
}
