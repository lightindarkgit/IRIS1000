/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-11
描述: 主框架，包括操作逻辑
**************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QThread>

#include "sqlmanage.h"

typedef enum _tagInfoType
{
    none_type = 0,      // 普通类型，显示深蓝色
    error_type,         // 错误类型，显示红色
    warning_type,       // 警告类型，显示紫色
    info_type           // 信息类型，显示绿色
}InfoType;


class DemoOv5640Thread;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);   //构造函数
    ~MainWindow();   //析构函数
public slots:
//    void ov5640imageUpdated(QImage);  //获取到图像后 刷新界面进行显示
private:
    Ui::MainWindow *ui;    //主ui

    int linecount;

//    DemoOv5640Thread *ov5640framesThread;    //5640采集RGB线程

signals:
    int sig_insertPersonIris(int);
    int sig_insertPerson(int);
    int sig_loadPersonIris();
    int sig_insertIrisParas();

public slots:
    void slot_printInfo(QString);

private slots:
    void on_PB_addFeature_clicked();
    void on_PB_addPerson_clicked();
    void on_PB_loadFeature_clicked();
    void on_PB_Tip_clicked();

private:
    void appendInfo(QString info, InfoType type = none_type);

    // 获取字符串的时间，格式年-月-日 时:分:秒-毫秒
    // needms=true，表示需要毫秒;=false，不需要毫秒
    QString getDateTime(bool needms=true);

    QThread myThread;
    SqlManage *sqlManageObj;

    bool sqlOpened;
};

#endif // MAINWINDOW_H
