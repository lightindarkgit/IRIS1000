import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import  "./qml/jbQuick"
Rectangle
{
    property int curUsers:33
    property int curAdmins:25
    property int curOthers:100 - curUsers - curAdmins
    id:sysCap
    x:0
    y:0
    width:1280
    height:720
    color: "#e9e9e9"
    Rectangle{
        id: title
        x: 0
        y: 0
        width: 1280
        height: 96
        color: "#626e81"
        Label{
            x: 30
            y: 20
            text: "系统容量"
            color: "#ffffff"
            font.pixelSize: 40
        }
        Button{
            id : aa
            anchors.right: parent.right
            anchors.rightMargin: 30
            y: 20
            style: ButtonStyle{
                background:
                    Rectangle{
                    implicitWidth: 50
                    implicitHeight: 43
                    color: title.color
//                    border.width: control.pressed ?2 :1
                }
            }
            iconSource: pressed ? "qrc:///res/image/back.png" : "qrc:///res/image/back-pressed.png"
        }
    }

    Chart {
      id: chart_pie
      x: 478
      y: 142
      width: 324
      height: 324
      chartAnimated: true;
      chartAnimationEasing: Easing.Linear;
      chartAnimationDuration: 500;      ///动画时间
      chartData: [{
              value: curUsers,
              color: "#f77b7e"
           }, {
              value: curAdmins,
              color: "#4ac3fc"
           }, {
              value: curOthers,
              color: "#e9e9e9"
          }]
      chartType: Charts.ChartType.PIE;
    }

    Rectangle   {
        x: 0
        y: 512
        height: 104
        width:1280
        color:"#f0f0f0"
        Canvas {
            x: 30
            y: 38
            width: 28
            height: 28
            onPaint: {
              var ctx = getContext("2d");
              ctx.fillStyle = Qt.rgba(0xf7/0xff, 0x7b/0xff, 0x7e/0xff, 1);
              ctx.arc(14,14,14, 0, Math.PI*2, 0);
              ctx.closePath();
              ctx.fill();
//              ctx.stroke();   ///描边
              ctx.closePath();
          }
        }
        Label{
            x: 78
            y: 28
            width: 180
            color: "#333333"
            font.pixelSize: 36
            text: "用户登记数"
        }
        Label{
            x: 591
            y: 32
            color: "#999999"
            font.pixelSize: 30
            text: "(" + curUsers  +"%)"
        }
        Label{
            anchors.right: parent.right
            anchors.rightMargin: 30
            x:1100
            y: 32
            color: "#333333"
            font.pixelSize: 36
            text: "1000"
        }
    }

    Rectangle{
    x: 0
    y: 616
    height: 104
    width:1280
    color:"#e9e9e9"

    Canvas {
        x: 30
        y: 38
        width: 28
        height: 28
        onPaint: {
          var ctx = getContext("2d");
          ctx.fillStyle = Qt.rgba(0x4a/0xff, 0xc3/0xff, 0xfc/0xff, 1);
          ctx.arc(14,14,14, 0, Math.PI*2, 0);
          ctx.closePath();
          ctx.fill();
//              ctx.stroke();   ///描边
          ctx.closePath();
      }
    }
    Label{
        x: 78
        y: 28
        width: 180
        color: "#333333"
        font.pixelSize: 36
        text: "管理员登记数"
    }
    Label{
        x: 591
        y: 32
        color: "#999999"
        font.pixelSize: 30
        text: "(" + curAdmins  +"%)"
    }
    Label{
anchors.right: parent.right
anchors.rightMargin: 30
        x:1100
        y: 32
        color: "#333333"
        font.pixelSize: 36
        text: "700"
    }

}

}
