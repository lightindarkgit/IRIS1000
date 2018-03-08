/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-11
描述: 主框架，包括操作逻辑
**************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QTime>
#include <QDate>
#include <QScrollBar>

#include "irisManager.h"

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

    IrisManager::get_instance()->moveToThread(&irisManagerThread);

    // connect
    connect(this, SIGNAL(sig_printInfo(QString)), this, SLOT(slot_printInfo(QString)), Qt::AutoConnection);
    connect(IrisManager::get_instance(), SIGNAL(loadFeatureResult(bool, int, int, int)),
            this,  SLOT(slot_loadFeatureReuslt(bool, int, int, int)), Qt::AutoConnection);

    irisManagerThread.start();

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
    delete ui;

    irisManagerThread.quit();
    irisManagerThread.wait();
}

void MainWindow::slot_loadFeatureReuslt(
        bool loadingNow, int result, int totalCount, int loadCount)
{
    QString info;
    //InfoType infoType = InfoType::info_type;

    if (loadingNow)
    {
        info = "特征加载中……";
    }
    else
    {
        info = "特征加载完成！";
    }

    if (result!=0)
    {
        info += QString(" | 加载失败(%1)").arg(result);
        //infoType = InfoType::error_type;
    }
    else
    {
        info += " | 加载成功";
    }

    float ratio = loadCount*100.0f/totalCount;
    info += QString(" | 总数：%1，已加载：%2，百分比：%3%")
            .arg(totalCount).arg(loadCount).arg(ratio);

    emit slot_printInfo(info);
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
    msqldatabase::get_Instance()->close();
    QApplication::exit();
}

void MainWindow::on_PB_loadFeature_clicked()
{
    IrisManInitArgs args;
    args.loadLocal = true;
    args.sendSigBlock = 500;

    IrisManager::get_instance()->initARG(args);
    appendInfo(QString("begin load person and iris totally"));
}

