#include "mainwindow.h"
#include <QApplication>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    //初始Application的字体,整个application有效
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    font.setPixelSize(30);
    a.setFont(font);

    MainWindow w;
    w.setFixedSize(640, 480);
    QGraphicsScene  *scene = new QGraphicsScene;
    QGraphicsProxyWidget *gw = scene->addWidget(&w);
    gw->setRotation(270);

    qDebug() << scene->sceneRect();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(640, 480);
    view->show();

    return a.exec();
}
