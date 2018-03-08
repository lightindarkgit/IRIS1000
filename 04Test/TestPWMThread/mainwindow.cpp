/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-11
描述: 主框架，包括操作逻辑
**************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmapCache>
#include <QDebug>

#include <QTime>
#include <QDate>
#include <QScrollBar>

#include <sys/time.h>  //gettimeofday
#include <stdio.h>

#include "ptzbase.h"

/*********************************
功   能：主框架构造函数
作   者：lhc
日   期：2017-12-11
修改 人：
修改内容：
修改日期：
参   数：QObject *parent
返回 值：
**********************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    linecount(0)
{
    ui->setupUi(this);
    ui->mainToolBar->setVisible(false);
    ui->menuBar->setVisible(false);
    ui->statusBar->setVisible(false);
    ui->LB_RGB->setVisible(false);

    ui->textEdit->document()->setMaximumBlockCount(500);
    ui->textEdit->setReadOnly(true);    //  只读

//    sqlManageObj = new SqlManage();
//    sqlManageObj->moveToThread(&myThread);

//    int error = sqlManageObj->getLastError();
//    QString info = QString("open database ret=%1").arg(error);
//    appendInfo(info);

//    if (error==E_MSQL_SUCCESS)
//    {
//        sqlOpened = true;
//        error = sqlManageObj->setDeviceInfo();
//        QString info = QString("setDeviceInfo ret=%1").arg(error);
//        appendInfo(info);
//    }

//    connect(this, SIGNAL(sig_insertPersonIris(int)), sqlManageObj, SLOT(slot_insertPersonIris(int)), Qt::AutoConnection);
//    connect(sqlManageObj, SIGNAL(sig_printInfo(QString)), this, SLOT(slot_printInfo(QString)), Qt::AutoConnection);

//    connect(this, SIGNAL(sig_insertPerson(int)), sqlManageObj, SLOT(slot_insertPerson(int)), Qt::AutoConnection);

    ptzBase::get_Instance()->moveToThread(&myThread);
    myThread.start();

//    qtnum_ov5640 = 0;
//    qDebug() << "hi";

//    ov5640framesThread = new DemoOv5640Thread(this);
//    connect(ov5640framesThread, SIGNAL(newFrameGetted(QImage)), this, SLOT(ov5640imageUpdated(QImage)));
//    ov5640framesThread->startThread();
    ui->stackedWidget->setCurrentIndex(0);
}
/*********************************
功   能：析构函数
作   者：lhc
日   期：2017-12-11
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
MainWindow::~MainWindow()
{
//     ov5640framesThread->stopThread();
    delete ui;

    myThread.quit();
    myThread.wait();

//    if (sqlManageObj)
//    {
//        delete sqlManageObj;on_PB_addPerson_clicked
//        sqlManageObj = NULL;
//    }

}

void MainWindow::slot_printInfo(QString info)
{
    appendInfo(info);
}

// 显示提示信息
void MainWindow::appendInfo(QString info, InfoType type)
{
    linecount ++;

    QString output = QString("%3. [%1] : %2").arg(getDateTime()).arg(info).arg(linecount);

    // logEntity::get_instance()->writeLog(L_ELAPSE, info);

    QTextCursor workCursor = ui->textEdit->textCursor();
    workCursor.movePosition(QTextCursor::End);
    //文本字符格式
    QTextCharFormat fmt;

    // 前景色(即字体色)设为color色
    QColor color;
    switch (type)
    {
    case none_type:
        color = Qt::darkBlue;
        break;

    case error_type:
        color = Qt::red;
        break;

    case warning_type:
        color = Qt::darkMagenta;
        break;

    case info_type:
        color = Qt::darkCyan;
        break;
    }

    fmt.setForeground(color);

    workCursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示

    workCursor.insertText(output);
    workCursor.insertBlock();

    //移动滚动条到底部
    QScrollBar *scrollbar = ui->textEdit->verticalScrollBar();
    if (scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }

}

// 获取字符串的时间，格式年-月-日 时:分:秒-毫秒
// needms=true，表示需要毫秒;=false，不需要毫秒
// 缺省为true
QString MainWindow::getDateTime(bool needms)
{
    QTime current_time = QTime::currentTime();
    QDate current_date = QDate::currentDate();

    QString printtime = QString("%1 ")
            .arg(current_date.toString("yyyy-MM-dd"));

    if (needms)
    {
        printtime += QString(current_time.toString("hh:mm:ss-zzz"));
    }
    else
    {
        printtime += QString(current_time.toString("hh:mm:ss"));
    }

    return printtime;
}

void MainWindow::on_PB_Tip_clicked()
{
//    msqldatabase::get_Instance()->close();
    QApplication::exit();
}

void MainWindow::on_PB_addAngle_clicked()
{
    int nret = ptzBase::get_Instance()->setSteeringFrame(1.0f);

    appendInfo(QString("+1 angle, %1").arg(nret));
}

void MainWindow::on_PB_minusAngle_clicked()
{
    int nret = ptzBase::get_Instance()->setSteeringFrame(-1.0f);

    appendInfo(QString("-1 angle, %1").arg(nret));
}

void MainWindow::on_PB_getAngle_clicked()
{
    int angle = ptzBase::get_Instance()->getSteeringAngle();

    QString info = QString("current angle is %1").arg(angle);

    appendInfo(info);
}
