import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQml 2.2
Rectangle {
    id: contain
    width: 1280
    height: 600
    x: 0
    y: 120
    property var yearData: []
    property var monthData: []
    property var dayData: []
    property var dayD:[31,28,31,30,31,30,31,31,30,31,30,31]
    property int curIndex:0
    property int curMonth:0
    property int curYear:0
    property int curDay:0
    property string showYear:""
    property string showMonth:""
    property string showDay:""
    property var dateTime: Date(2000, 1, 1);
    property int lastMonth: curMonth

Rectangle {
    id: year
    width: 100
    height: 400
    x: (contain.width - year.width - month.width - day.width) /2 - 145
    y: contain.height - year.height - date_cancel.height
    Component {
        id: delegate
        Column {
            id: wrapper
            Label {
                id: nameText
                text:  name
                color: wrapper.PathView.isCurrentItem ? "#FF333333" : "#80999999"
                font.pixelSize:  wrapper.PathView.isCurrentItem ? 36 : 30
            }
        }
    }
    PathView {
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                for (var i = 2000; i < 2100; ++i) {
                    append({"objectName": i.toString(),"name": i.toString()});
                    yearData[i-2000]=i;
                }
                showYear = yearData[curYear] + "年"
                if((yearData[curYear]%4==0&&yearData[curYear]%100!=0)||yearData[curYear]%400==0)
                {  //是闰年
                    dayD[1] = 29;
                }
                else
                {
                    dayD[1]=28;
                }
                var locale= Qt.locale()
                var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
                var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd")
                showDate.text = showYear + showMonth + showDay + "   " + tmp
            }
        }
        delegate: delegate

        pathItemCount: 5     ///当前最多显示5个
        highlightRangeMode :PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlight: Rectangle{
//            color:"#090999"
            width: parent.width
            height: year.height / 5
        }

        path: Path {
            startX: year.width / 2
            startY: 0
            PathLine { x: year.width / 2; y: 400 }
//            PathQuad { x: 120; y: 25; controlX: 260; controlY: 75 }
        }
        onMovementEnded:{
            curYear =currentIndex
            showYear = yearData[curYear] + "年"
//            leapYear[yearData[curYear]]
            if((yearData[curYear]%4==0&&yearData[curYear]%100!=0)||yearData[curYear]%400==0)
            {  //是闰年
                dayD[1] = 29;
            }
            else
            {
                dayD[1]=28;
            }

            var taD = dayD[curMonth]
            if(taD < dayData[curDay] )
            {
                dayData.splice(0, dayData.length);
                dayPv.model.clear();
                curDay = 0
                for (var i = 0; i < taD; ++i) {
                    if(i < 9)
                    {
                         dayPv.model.append({"name": "0" + (i+1).toString()});
                        dayData[i] = "0" + (i+1).toString();
                    }
                    else
                    {
                        dayPv.model.append({"name": (i+1).toString()});
                        dayData[i] = (i+1).toString();
                    }
                }
            }
            if(taD !== dayD[lastMonth])
            {
                dayPv.model.clear();
                curDay = 0
                for (var i = 0; i < taD; ++i) {
                    if(i < 9)
                    {
                         dayPv.model.append({"name": "0" + (i+1).toString()});
                        dayData[i] = "0" + (i+1).toString();
                    }
                    else
                    {
                        dayPv.model.append({"name": (i+1).toString()});
                        dayData[i] = (i+1).toString();
                    }
                }
            }
            var locale= Qt.locale()
            var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
            showDay = dayData[curDay] + "日"
            var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd");
            showDate.text = showYear + showMonth + showDay + "   " + tmp
        }
    }
}
Rectangle{
    id: yearText
    width: 20
    height: 20
    x: year.x + year.width - 0
    y: contain.height - year.height / 2 - date_cancel.height - 10
    Label{
        text: "年"
        font.pixelSize:  18
        color:  "#333333"
    }
}

Rectangle {
    id: month
    width: 100
    height: 400
    x: yearText.x + yearText.width + 130
    y: contain.height - year.height - date_cancel.height
    Component {
        id: delegateM
        Column {
            id: wrapper
            Label {
                id: nameText
                text:  name
                color: wrapper.PathView.isCurrentItem ? "#FF333333" : "#80999999"
                font.pixelSize:  wrapper.PathView.isCurrentItem ? 36 : 30
            }
        }
    }
    PathView {
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                for (var i = 0; i < 12; ++i) {
                    if(i < 9)
                    {
                        append({"name": "0" + (i+1).toString()})
                        monthData[i]="0" + (i+1).toString();
                    }
                    else
                    {
                        append({"name": (i+1).toString()});
                        monthData[i]=  (i+1).toString();
                    }
                }
                showMonth = monthData[curMonth] + "月"
                var locale= Qt.locale()
                var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
                var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd")
                showDate.text = showYear + showMonth + showDay + "   " + tmp
            }
        }
        delegate: delegateM
        pathItemCount: 5
        highlightRangeMode :PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlight: Rectangle{
            width: parent.width
            height: month.height / 5
        }

        path: Path {
            startX: month.width / 2
            startY: 0
            PathLine { x: month.width / 2; y: 400 }
        }
        onMovementEnded:{
            lastMonth = curMonth
            curMonth =currentIndex
            var taD = dayD[curMonth]
            if(taD < dayData[curDay] )
            {
                dayData.splice(0, dayData.length);
                dayPv.model.clear();
                curDay = 0
                for (var i = 0; i < taD; ++i) {
                    if(i < 9)
                    {
                         dayPv.model.append({"name": "0" + (i+1).toString()});
                        dayData[i] = "0" + (i+1).toString();
                    }
                    else
                    {
                        dayPv.model.append({"name": (i+1).toString()});
                        dayData[i] = (i+1).toString();
                    }
                }
            }
            if(taD !== dayD[lastMonth])
            {
                dayPv.model.clear();
                curDay = 0
                for (var i = 0; i < taD; ++i) {
                    if(i < 9)
                    {
                         dayPv.model.append({"name": "0" + (i+1).toString()});
                        dayData[i] = "0" + (i+1).toString();
                    }
                    else
                    {
                        dayPv.model.append({"name": (i+1).toString()});
                        dayData[i] = (i+1).toString();
                    }
                }
            }

            showMonth = monthData[curMonth] + "月"
            showDay = dayData[curDay] + "日"
            var locale= Qt.locale()
            var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
            var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd")
            showDate.text = showYear + showMonth + showDay + "   " + tmp
        }
    }
}
Rectangle{
    id: monthText
    width: 20
    height: 20
    x: month.x + month.width - 25
    y: contain.height - year.height / 2 - date_cancel.height - 10
    Label{
        text: "月"
        font.pixelSize:  18
        color:  "#333333"
    }
}

Rectangle {
    id: day
    width: 100
    height: 400

    x: monthText.x + monthText.width + 130
    y: contain.height - year.height - date_cancel.height
    Component {
        id: delegateD
        Column {
            id: wrapper
            Label {
                id: nameText
                text:  name
                color: wrapper.PathView.isCurrentItem ? "#FF333333" : "#80999999"
                font.pixelSize:  wrapper.PathView.isCurrentItem ? 36 : 30
            }
        }
    }
    PathView {
        id: dayPv
        anchors.fill: parent
        model: ListModel {
            Component.onCompleted: {
                var taD = dayD[curMonth]
                dayData.splice(0, dayData.length);
                for (var i = 0; i < taD; ++i) {
                    if(i < 9)
                    {
                        append({"name": "0" + (i +1).toString()})
                        dayData[i]= "0" + (i +1).toString();
                    }
                    else
                    {
                        append({"name": (i+1).toString()});
                        dayData[i] = (i +1).toString()
                    }
                }
                showDay = dayData[curDay] + "日"
                var locale= Qt.locale()
                var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
                var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd")
                showDate.text = showYear + showMonth + showDay + "   " + tmp
            }
        }
        delegate: delegateD
        pathItemCount: 5
        highlightRangeMode :PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlight: Rectangle{
            width: parent.width
            height: day.height / 5
        }
        path: Path {
            startX: day.width / 2
            startY: 0
            PathLine { x: day.width / 2; y: 400 }
        }
        onMovementEnded:{
            curDay = currentIndex
            showDay = dayData[curDay] + "日"
            var locale= Qt.locale()
            var dateTimeString = yearData[curYear]+"-"+ monthData[curMonth]+"-"+ dayData[curDay]
            var tmp = Date.fromLocaleString(locale,dateTimeString, "yyyy-MM-dd").toLocaleString(Qt.locale("zh_CN"), "ddd")
            showDate.text = showYear + showMonth + showDay + "   " + tmp
        }
    }
}
Rectangle{
    id: dayText
    width: 20
    height: 20
    x: day.x + day.width - 25
    y: contain.height - year.height / 2 - date_cancel.height - 10
    Label{
        text: "日"
        font.pixelSize:  18
        color:  "#333333"
    }
}


Button
{
    id: date_cancel
    anchors.bottom: contain.bottom
    anchors.bottomMargin: 0
    anchors.left: contain.left
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
                color: date_cancel.pressed ? "#80666666" :"#B3666666"
            }
        }
    }
//        iconSource:{ source: "qrc:///res/image/setImage/基本.png"}
    onClicked:{
        root.viewShow = 1
    }
}
Button
{
    id: date_ok
    anchors.bottom: contain.bottom
    anchors.bottomMargin: 0
    anchors.left: date_cancel.right
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
                color: date_ok.pressed ? "#b35aa5e6" :"#ff5aa5e6"
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
    y: month.y + month.height /5 *2
    width: parent.width
    height: 2
    color: "#cccccc"
}
Rectangle{
    id: lineb
    x:0
    y: linea.y + day.height / 5
    width: parent.width
    height: 2
    color: "#cccccc"
}

Label{
    id:showDate
    x:530
    y:30
    font.pixelSize:  24
    color: "#666666"
}
}

