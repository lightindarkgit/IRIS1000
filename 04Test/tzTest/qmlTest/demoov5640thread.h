/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-12
描述: RGB采图线程
**************************************************/

#ifndef DEMOOV5640THREAD_H
#define DEMOOV5640THREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
//#include "tracker.h"

class DemoOv5640Thread : public QThread
{
    Q_OBJECT

public:
    explicit DemoOv5640Thread(QObject *parent = 0);  //构造函数
    ~DemoOv5640Thread();           //析构函数
    void stopThread();   //停止线程运行
    void startThread();   //开始线程运行

signals:
    void newFrameGetted(QImage img);  //获得到新的图像的信号 ，供外部使用

private slots:
//    void getResult(pointData info);     //获得人脸检测结果的槽函数

protected:
    void run();   //线程

private:
    volatile bool stopped;    //线程停止标志，true停止 ，false运行
//    QImage *dispImg;
//    QThread workerThread;  //人脸检测线程
//    QImage *dispImg_ov5640;
public:
//    char Save_Img_Flag_ov5640;
//    char num_img_ov5640;
//    unsigned char ov5640_data[50][2592*1944];   //??

//    QString file_str_ov5640;
//    QString file_path_str_ov5640;
//    char file_path_name_ov5640[256];

private:
//    pointData            m_Info;  ///人脸检测用
//    IK_Rect                m_lastFaceRect;        //最近一次人脸位置
public:
    bool Save_Img_Flag_ov5640 = false;

};

#endif // DEMOOV5640THREAD_H
