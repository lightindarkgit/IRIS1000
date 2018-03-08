#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

// 这个程序用于演示创建线程，在线程中执行的方式
// 可以修改不同的连接方式Qt::AutoConnection...
// 来观察不同的效果

// 程序的效果是点击界面上的start按钮，qDebug输出主线程的id
// 并显示槽函数所在线程的id，槽函数中会sleep2秒

// 这样可以显示出信号和槽所在线程的id（连接方式不同时，有不同的时候，有相同的时候）
// 还可以显示信号是否一定要等待槽返回后才能继续执行

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    k(0),
    writeStringObj(NULL)
{
    ui->setupUi(this);

    writeStringObj = new WriteObject();
    writeStringObj->moveToThread(&myThread);

    connect(this, SIGNAL(haveClicked(QString)), writeStringObj, SLOT(run(QString)), Qt::AutoConnection);

    myThread.start();

//    Qt::AutoConnection 系统默认的连接方式，信号进入一个消息队列，何时执行槽由系统决定；
//                       当信号和槽在同一个线程，与Qt::DirectConnection等效
//                       当信号和槽不在同一个线程，与Qt::QueuedConnection等效

//    Qt::DirectConnection 直接连接，信号发出就到槽执行；无论槽所属的对象在哪个线程
//                         槽函数都在信号发出的那个线程内执行（注意，不是槽自己的线程）

//    Qt::QueuedConnection 在不同线程之间连接；在槽所属的对象所在的线程中执行，信号按顺序执行
//                         按照队列顺序执行；如线程停止，暂停执行；下次启动线程时会再次按队列顺序执行
//                         （？？之前没有执行完的不会被清除吗？？）

//    Qt::BlockingQueuedConnection 必须信号和槽在不同的线程中，否则会死锁；完全同步队列，只有槽执行完毕后才返回

//    Qt::UniqueConnection 与Qt::AutoConnection工作方式相同，但是不能重复连接相同的信号和槽
//                         重复连接会导致一个信号发出，对应槽函数执行多次

//    Qt::AutoCompatConnection 是为了链接QT4到QT3的信号槽兼容方式，一般应该是不会用
}

MainWindow::~MainWindow()
{
    delete ui;

    myThread.quit();
    myThread.wait();

    if (writeStringObj)
    {
        delete writeStringObj;
        writeStringObj = NULL;
    }
}

void MainWindow::on_PB_start_clicked()
{
    qDebug() << "mainwin thread id=" << QThread::currentThreadId();

    k++;

    QString str = QString::number(k);

    emit haveClicked(str);
}
