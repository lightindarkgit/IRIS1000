import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
Rectangle {
    id: contain
    width: 1280
    height: 600
    x: 0
    y: 120
    property var hourData: []
    property var minuteData: []
    property int curIndex:0
    property int curHour:0
    property int curMinute:0

Rectangle {
    id: hour
    width: 100
    height: 400
    x: 480
    y: contain.height - hour.height - time_cancel.height
    Component {
        id: delegateH
        Column {
            id: wrapperH
            Label {
                id: nameH
                text:  name
                color: wrapperH.PathView.isCurrentItem ? "#FF333333" : "#80999999"
                font.pixelSize:  wrapperH.PathView.isCurrentItem ? 36 : 30
            }
        }
    }
    PathView {
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                for (var i = 0; i < 24; ++i) {
                    if(i < 10)
                    {
                        append({"name": "0" + (i).toString()})
                    }
                    else
                    {
                        append({"name": (i).toString()});
                    }
                    hourData[i]=i;
                }
                if(curHour < 10)
                {
                    showHour.text = "0" + hourData[curHour]
                }
                else
                {
                    showHour.text = hourData[curHour]
                }
            }
        }
        delegate: delegateH
        pathItemCount: 5
        highlightRangeMode :PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlight: Rectangle{
            width: hour.width
            height: hour.height / 5
        }
        path: Path {
            startX: hour.width / 2
            startY: 0
            PathLine { x: hour.width / 2; y: 400 }
        }
        onMovementEnded:{
            curHour =currentIndex
            if(curHour < 10)
            {
                showHour.text = "0" + hourData[curHour]
            }
            else
            {
                showHour.text = hourData[curHour]
            }
        }
    }
}
Rectangle {
    id: minute
    width: 100
    height: 400
    x: hour.x + hour.width + 120
    y: contain.height - hour.height - time_cancel.height
    Component {
        id: delegateMin
        Column {
            id: wrapperMin
            Label {
                id: nameMin
                text:  name
                color: wrapperMin.PathView.isCurrentItem ? "#FF333333" : "#80999999"
                font.pixelSize:  wrapperMin.PathView.isCurrentItem ? 36 : 30
            }
        }
    }
    PathView {
        id: minutePv
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                for (var i = 0; i < 60; ++i) {
                    if(i < 10)
                    {
                        append({"name": "0" + (i ).toString()})
                    }
                    else
                        append({"name": (i).toString()});
                    minuteData[i]=i;
                }
                if(curMinute < 10)
                {
                    showMin.text = "0" + minuteData[curMinute]
                }
                else
                {
                    showMin.text = minuteData[curMinute]
                }
            }
        }
        delegate: delegateMin
        pathItemCount: 5
        highlightRangeMode :PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlight: Rectangle{
            width: minute.width
            height: minute.height / 5
        }
        path: Path {
            startX: minute.width / 2
            startY: 0
            PathLine { x: minute.width / 2; y: 400 }
        }
        onMovementEnded:{
            curMinute = currentIndex
            if(curMinute < 10)
            {
                showMin.text = "0" + minuteData[curMinute]
            }
            else
            {
                showMin.text = minuteData[curMinute]
            }
        }
    }
}

Button
{
    id: time_cancel
    anchors.top:hour.bottom
    anchors.topMargin: 0
    anchors.left: contain.left
    anchors.leftMargin: 0
    width: 640
    height: 80
    smooth: true
    style: ButtonStyle{
        background: Rectangle{
            implicitWidth: 120
            implicitHeight: 80
            color:"#FFFFFF"
            border.width: 1
            border.color:"#cccccc"
            Label {
                anchors.verticalCenter:  parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "取消"
                font.pixelSize:  36
                color: time_cancel.pressed ? "#80666666" :"#B3666666"
            }
        }
    }
    onClicked:{
//        root.viewShow = 1
    }
}
Button
{
    id: time_ok
    anchors.top:hour.bottom
    anchors.topMargin: 0
    anchors.left: time_cancel.right
    anchors.leftMargin: 0
    width: 640
    height: 80
    smooth: true
    style: ButtonStyle{
        background: Rectangle{
            implicitWidth: 120
            implicitHeight: 80
            color:"#FFFFFF"
            border.width: 1
            border.color:"#cccccc"
            Label {
                anchors.verticalCenter:  parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "确认"
                font.pixelSize:  36
                color: time_ok.pressed ? "#b35aa5e6" :"#ff5aa5e6"
            }
        }
    }
    onClicked:{
        root.viewShow = 1
    }
}

//画线
Rectangle{
    id:linea
    x:0
    y: minute.y + minute.height / 5 *2
    width: parent.width
    height: 2
    color: "#cccccc"
}
Rectangle{
    id: lineb
    x:0
    y: linea.y + minute.height / 5
    width: parent.width
    height: 2
    color: "#cccccc"
}

Label{
    id: showHour
    x: 615
    y: 40
    font.pixelSize:  24
    color: "#666666"
}
Label{
    id: showid
    x: 640
    y: 40
    font.pixelSize:  24
    color: "#666666"
    text: ":"
}
Label{
    id: showMin
    x: 645
    y: 40
    font.pixelSize:  24
    color: "#666666"
}

}

