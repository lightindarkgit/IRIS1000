import QtQuick 2.0
Rectangle {
    id: messageBoxBackground
    property string title:"提示"
    property string prompt:"确定吗？"
    property int fontSize : 0.03 * parent.height
    signal itemClicked(int index)
    function doModal()
    {
        messageBoxBackground.state = "visible"
        Qt.inputMethod.hide()
    }
    visible: false
    anchors.fill: parent
    color: "#80000000"
    //点击对话框区域外，隐藏对话框，其父窗口最后变为最外层窗口，在Component.onCompleted事件中设置
    MouseArea {
        anchors.fill: parent//
        onClicked:
        {
            //menuRoot.state = "";//非模态时可以这样用
        }
    }
    //对话框
    Rectangle {
        id: messageBox
        color: "white"
        width: 0.8 * parent.width
        height: 0.3 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        rotation: 270
        Column
        {
            anchors.fill: parent
            Rectangle
            {
                width: parent.width
                height:0.25 * parent.height
                color: "#DBDBDB"
                Text
                {
                    anchors.fill: parent
                    horizontalAlignment:Text.AlignHCenter
                    verticalAlignment:Text.AlignVCenter
                    font.pixelSize: fontSize
                    text:title
                }
            }
            Rectangle
            {
                width: parent.width
                height:1
                color: "#3399db"
            }
            Text
            {
                id:textText
                width: parent.width
                height:0.5 * parent.height
                horizontalAlignment:Text.AlignLeft
                verticalAlignment:Text.AlignVCenter
                font.pixelSize: fontSize
                wrapMode:Text.WordWrap
                text:prompt
                color: "black"
            }
            Rectangle
            {
                width: parent.width
                height:1
                color: "#3399db"
            }
            Rectangle
            {
                width: parent.width
                height:0.25 * parent.height
                color: "#3399db"
                Text
                {
                    anchors.fill: parent
                    horizontalAlignment:Text.AlignHCenter
                    verticalAlignment:Text.AlignVCenter
                    font.pixelSize: fontSize
                    text:"确定"
                }
                MouseArea {
                    anchors.fill: parent//
                    onClicked:
                    {
                        console.log("onClicked 2")
                        messageBoxBackground.state = "";
                    }
                }
            }
        }
    }
    states: State {
        name: "visible"
        PropertyChanges {target: messageBoxBackground; visible: true}
    }
    transitions: Transition {
        NumberAnimation {
            target:  messageBoxBackground
            properties: "visible"
            duration: 250
        }
    }
    Component.onCompleted:
    {
        var docRoot = messageBoxBackground.parent;
        while(docRoot.parent)
        {
            docRoot = docRoot.parent;
        }
        messageBoxBackground.parent = docRoot;
    }
}
