/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-12
描述: 启动函数
**************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QTextStream>

//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
////    QByteArray localMsg = msg.toLocal8Bit();
////    switch (type) {
////    case QtDebugMsg:
////        fprintf(stderr, "D:%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
////        break;
////    case QtInfoMsg:
////        fprintf(stderr, "I %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
////        break;
////    case QtWarningMsg:
////        fprintf(stderr, "W: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
////        break;
////    case QtCriticalMsg:
////        fprintf(stderr, "C: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
////        break;
////    case QtFatalMsg:
////        fprintf(stderr, "F: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
////        abort();
////    }
//    QFile file("text.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
//        return;
//    QTextStream out(&file);
//    out << msg << endl;
//}

int main(int argc, char *argv[])
{
//    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);

    //初始Application的字体,整个application有效
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setPixelSize(20);
    a.setFont(font);

    MainWindow w;
    w.setFixedSize(1280,720);
    QGraphicsScene  *scene = new QGraphicsScene;
    QGraphicsProxyWidget *gw = scene->addWidget(&w);
    gw->setRotation(270);

    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(720,1280);
    view->show();

    //w.show();
    return a.exec();
}
