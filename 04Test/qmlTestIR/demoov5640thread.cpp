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
//#include "facetrack.h"

#define OV5640_DATA_LEN			2592*1944*2
unsigned char ov5640_testdata[OV5640_DATA_LEN];
int ov5640_g_width = 480;
int ov5640_g_height = 640;

#define OV5640_15FPS_640x480_NO
#define OV5640_30FPS_640x480
/*********************************
功   能：RGB采图线程构造函数
作   者：lhc
日   期：2017-12-12
修改 人：
修改内容：
修改日期：
参   数：QObject *parent
返回 值：
**********************************/
DemoOv5640Thread::DemoOv5640Thread(QObject *parent)
    : QThread(parent)
{
    stopped = false;
//    dispImg = NULL;
    char ov5640_g_v4l_device[100] = "/dev/video1";
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

    int ov5640_imge_format = OV5640_IMAGE_FORMAT_RGB;
    int ov5640_g_rotate = 4;
    IKOV5640YUV_SetParmMIPICamera(ov5640_framerate,ov5640_mode,ov5640_input,ov5640_g_rotate,ov5640_imge_format);
    IKOV5640YUV_OpenMIPICamera(ov5640_g_v4l_device,ov5640_width,ov5640_height);

//    FaceTrack *work = new FaceTrack;
//    work->moveToThread(&workerThread);
//    connect(&workerThread, &QThread::finished, work, &QObject::deleteLater);
//    connect(this, SIGNAL(newFrameGetted(QImage)), work, SLOT(dealFace(QImage)));
//    connect(work, SIGNAL(result(pointData)), this, SLOT(getResult(pointData)));
//    workerThread.start();
}
/*********************************
功   能：RGB采图线程析构函数
作   者：lhc
日   期：2017-12-12
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
DemoOv5640Thread::~DemoOv5640Thread()
{
//    workerThread.quit();
//    workerThread.wait();
    IKOV5640YUV_CloseMIPICamera();
    stopThread();
    quit();
    wait();
}

/*********************************
功   能：停止线程运行
作   者：lhc
日   期：2017-12-12
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
void DemoOv5640Thread::stopThread()
{
    stopped = true;
    this->terminate();
}
/*********************************
功   能：开始线程运行
作   者：lhc
日   期：2017-12-12
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
void DemoOv5640Thread::startThread()
{
    stopped = false;
    this->start();
}
/*********************************
功   能：获得人脸检测结果的槽函数
作   者：lhc
日   期：2017-12-14
修改 人：
修改内容：
修改日期：
参   数：  pointData info
返回 值：
**********************************/
//void DemoOv5640Thread::getResult(pointData info)
//{
//    qDebug() << info.flag << info.pupilLX;
//}

/*********************************
功   能：获得图像的实际线程
作   者：lhc
日   期：2017-12-12
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
void DemoOv5640Thread::run()
{
    QImage *dispImg_ov5640 = new QImage(ov5640_testdata, ov5640_g_width,ov5640_g_height,QImage::Format_RGB888);
//    QVector<QRgb> my_table;
//    for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
//    dispImg_ov5640->setColorTable(my_table);
    while(!stopped)
    {
        IKOV5640YUV_GetMIPIImage(ov5640_testdata);
        if(Save_Img_Flag_ov5640)
        {
            QString filename = QTime::currentTime().toString("hh-mm-ss-zzz");
            bool res = dispImg_ov5640->save("ov5640_tz/"+filename+".bmp","bmp");
            if(res == true)
            printf("dispImg_ov5640 save image res is %d\n",res);
        }

        emit newFrameGetted(*dispImg_ov5640);
        usleep(10000);
    }
}
