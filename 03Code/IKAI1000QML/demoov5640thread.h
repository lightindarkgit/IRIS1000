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
#include "tracker.h"

class FaceTrack;
class DemoOv5640Thread : public QThread
{
    Q_OBJECT

public:
    explicit DemoOv5640Thread(QObject *parent = 0);  //构造函数
    ~DemoOv5640Thread();           //析构函数IK_Rect
    void stopThread();   //停止线程运行
    void startThread();   //开始线程运行
    void setThreadPaused(bool flag);  //设置线程状态，true线程暂停，false线程继续
    void setAbleCap(bool flag);  //界面显示完上一帧图像后，允许发送下一帧图像，true允许发送， false暂停发送

signals:
    void newFrameGetted(QImage img);  //获得到新的图像的信号 ，供外部使用

private slots:

protected:
    void run();   //线程

private:
    volatile bool m_stopped;    //线程停止标志，true停止 ，false运行
    volatile bool m_paused;  //线程暂停 ，true 暂停中， false恢复运行
    bool  m_ableCapImage;  //允许继续获取图像，避免横线
//    QImage *dispImg;
    QThread workerThread;  //人脸检测线程
    FaceTrack *m_work;
//    QImage *dispImg_ov5640;
public:
//    char Save_Img_Flag_ov5640;
//    char num_img_ov5640;
//    unsigned char ov5640_data[50][2592*1944];   //??

//    QString file_str_ov5640;
//    QString file_path_str_ov5640;
//    char file_path_name_ov5640[256];

public:
    bool Save_Img_Flag_ov5640 = false;
private:
};

#endif // DEMOOV5640THREAD_H
