/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-12
描述: RGB采图线程
**************************************************/
#include "demoov5640thread.h"
#include <QImage>
#include <QDebug>
#include <QTime>
#include "include/OV5640MipiApi.h"
//#include "tracker.h"
//#include "ikAlgoFaceDetection.h"
//#include "Exectime.h"
#include "facetrack.h"

// modified at 20180228 by yqhe
// 所有舵机控制放到facetrack.cpp中
// 图像采集线程中，只负责将采集到的图像发送到facetrack中进行处理即可

#define OV5640_DATA_LEN			2592*1944*2
unsigned char ov5640_testdata[OV5640_DATA_LEN];
unsigned char ov5640_testdataA[OV5640_DATA_LEN];
//int ov5640_g_width = 480;
//int ov5640_g_height = 640;
int ov5640_g_width = 640;
int ov5640_g_height = 720;

#define OV5640_15FPS_640x480
#define OV5640_30FPS_640x480_NO

/*****************************************************************************
 *                         RGB采图线程构造函数
 *  函 数 名：DemoOv5640Thread
 *  功    能：RGB采图线程构造函数
 *  说    明：
 *  参    数：QObject *parent
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
DemoOv5640Thread::DemoOv5640Thread(QObject *parent)
    : QThread(parent)
{
    m_stopped = false;
    m_paused = false;
    m_ableCapImage = true;
//    dispImg = NULL;
    char ov5640_g_v4l_device[100] = "/dev/video1";
    int ov5640_imge_format = OV5640_IMAGE_FORMAT_RGB;
    int ov5640_g_rotate = 4;
#ifdef OV5640_15FPS_640x480
    int ov5640_framerate = 15;
    int ov5640_mode = 0;
    int ov5640_input = 1;
    int ov5640_width = 640;
    int ov5640_height = 480;
#endif
#ifdef OV5640_30FPS_640x480
    int ov5640_framerate = 30;
    int ov5640_mode = 0;
    int ov5640_input = 1;
    int ov5640_width = 640;
    int ov5640_height = 480;
    int ov5640_fps = 9;
#endif

    IKOV5640YUV_SetParmMIPICamera(ov5640_framerate,ov5640_mode,ov5640_input,ov5640_g_rotate,ov5640_imge_format);
    IKOV5640YUV_SetOutSize(ov5640_g_width,ov5640_g_height);
    IKOV5640YUV_OpenMIPICamera(ov5640_g_v4l_device,ov5640_width,ov5640_height);

    m_work = new FaceTrack;
    m_work->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, m_work, &QObject::deleteLater, Qt::UniqueConnection);
    connect(this, SIGNAL(newFrameGetted(QImage)), m_work, SLOT(dealFace(QImage)),
            Qt::UniqueConnection);
    m_work->setCheckFlag(true);
//    connect(work, SIGNAL(result(pointData)), this, SLOT(getResult(pointData)));
    workerThread.start();
}

/*****************************************************************************
 *                         RGB采图线程析构函数
 *  函 数 名：~DemoOv5640Thread
 *  功    能：RGB采图线程析构函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
DemoOv5640Thread::~DemoOv5640Thread()
{
    workerThread.quit();
    workerThread.wait();

    IKOV5640YUV_CloseMIPICamera();
    stopThread();
    quit();
    wait();
}
/*****************************************************************************
 *                         停止RGB线程运行函数
 *  函 数 名：stopThread
 *  功    能：停止RGB线程运行函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void DemoOv5640Thread::stopThread()
{
    m_stopped = true;
    this->terminate();
}
/*****************************************************************************
 *                         开始线程运行函数
 *  函 数 名：startThread
 *  功    能：开始线程运行函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void DemoOv5640Thread::startThread()
{
    m_stopped = false;
    this->start();
}
/*****************************************************************************
 *                         设置线程状态函数
 *  函 数 名： setThreadPaused
 *  功    能：设置线程状态，true线程暂停采图，false线程继续采图
 *  说    明：
 *  参    数：bool flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void DemoOv5640Thread::setThreadPaused(bool flag)
{
    m_paused = flag;    
    if(m_paused)
    {
        qDebug() << "set pause...........................................";
        disconnect(this, SIGNAL(newFrameGetted(QImage)), m_work, SLOT(dealFace(QImage)));
        m_work->setCheckFlag(false);
    }
    else
    {
        qDebug() << "set continue.......................................";
        connect(this, SIGNAL(newFrameGetted(QImage)), m_work, SLOT(dealFace(QImage)),
                Qt::UniqueConnection);
        m_work->setCheckFlag(true);
    }
}
/*****************************************************************************
 *                         设置继续采图函数
 *  函 数 名： setAbleCap
 *  功    能：界面显示完上一帧图像后，允许发送下一帧图像，true允许发送， false暂停发送
 *  说    明：
 *  参    数：bool flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void DemoOv5640Thread::setAbleCap(bool flag)
{
    m_ableCapImage = flag;
}

/*****************************************************************************
 *                         获得图像的实际线程函数
 *  函 数 名： run
 *  功    能：获得图像的实际线程
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2017-12-12
 *  修 改 人：
 *  修改时间：2018-02-09
 *  修改内容：改为乒乓方式读取图像数据
 *****************************************************************************/
void DemoOv5640Thread::run()
{
    QImage *dispImg_ov5640 = new QImage(ov5640_testdata, ov5640_g_width,ov5640_g_height,QImage::Format_RGB888);
    QImage *dispImg_ov5640A = new QImage(ov5640_testdataA, ov5640_g_width,ov5640_g_height,QImage::Format_RGB888);
    bool usePP = true;
//    QVector<QRgb> my_table;
//    for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
//    dispImg_ov5640->setColorTable(my_table);
    while(!m_stopped)
    {
        while(m_paused)
        {
            usleep(10000);
        }
        if(usePP)
        {
            IKOV5640YUV_GetMIPIImage(ov5640_testdata);
        }
        else
        {
            IKOV5640YUV_GetMIPIImage(ov5640_testdataA);
        }
        while(!m_paused)
        {
            if(m_ableCapImage == true)
            {
                m_ableCapImage = false;
                if(usePP)
                {
                    emit newFrameGetted(*dispImg_ov5640);
                    usePP = false;
//                    qDebug() << "dispImg_ov5640.......................";
                }
                else if(!usePP)
                {
                    emit newFrameGetted(*dispImg_ov5640A);
                    usePP = true;
//                    qDebug() << "dispImg_ov5640A.......................";
                }
                break;
            }
            else
            {
                usleep(5000);
            }
        }
    }
//    while(!stopped)
//    {
//        IKOV5640YUV_GetMIPIImage(ov5640_testdata);
////        if(Save_Img_Flag_ov5640)
////        {
////            QString filename = QTime::currentTime().toString("hh-mm-ss-zzz");
////            bool res = dispImg_ov5640->save("ov5640_tz/"+filename+".bmp","bmp");
////            if(res == true)
////            printf("dispImg_ov5640 save image res is %d\n",res);
////        }
//        emit newFrameGetted(*dispImg_ov5640);
//        usleep(30000);
//    }
    delete dispImg_ov5640;
    dispImg_ov5640 = nullptr;
    delete dispImg_ov5640A;
    dispImg_ov5640A = nullptr;
}
