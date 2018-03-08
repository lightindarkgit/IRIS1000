#include "testclass.h"
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include<sys/time.h>
#include <unistd.h>
#include <iostream>
using namespace std;

#include<sys/time.h>  //gettimeofday
#include <stdio.h>

bool Save_Img_Flag_ov2710 = false;
const int enrNum = 6;

static IKIrisPos g_irisPos;
static int g_leftNum = 0;
static int g_rightNum = 0;
static int g_curDist =0;
static int g_leftRadius = 0;
static int g_rightRadius = 0;
static IKIrisDistFlag g_distEstimation;
static int g_UIUEMsgID = 0;
unsigned char irisImgBuf[IK_IMG_SIZE + IK_BMP_BMP_HEADER_SIZE];
QImage irisImg(IK_DISPLAY_IMG_WIDTH, IK_DISPLAY_IMG_HEIGHT, QImage::Format_Indexed8);
//int ov5640_g_width = 480;
//int ov5640_g_height = 640;
QImage faceImg(640,720,QImage::Format_RGB888);
//QImage tmp_ov2710;
typedef enum
{
    //ImageWidth = IMG_WIDTH,
    ImageWidth = IK_DISPLAY_IMG_WIDTH,
    //ImageHeight = IMG_HEIGHT,
    ImageHeight = IK_DISPLAY_IMG_HEIGHT,
    ImageSize = ImageWidth * ImageHeight,
    GrayBufferSize   = (ImageWidth-1)*(ImageHeight-1),
    PPMHeaderLength = 18,
    DataOffset = 8
} TypeSize;
static char g_grayPpmHeader[PPMHeaderLength];
static unsigned char g_grayImBuffer[ImageSize + PPMHeaderLength];

ImagePaintEvent imPaintEvent;
void ImagePaintEvent::RaisePaintEvent()
{
    emit sigPaint();
}

//MyImageProvider myImageProvider;
int qtnum=0;
int qttimediff;
struct timeval qtbegintv;
struct timeval qtendtv;
void IrisStatusInfoCallback(IKEnrIdenStatus* enrIdenStatus)
{
    int timediff;
    if(qtnum==0) gettimeofday(&qtbegintv,NULL);
    qtnum = qtnum+1;
    if(qtnum >=20)
    {
        qtnum = 0;
        gettimeofday(&qtendtv,NULL);
        timediff=  (qtendtv.tv_sec-qtbegintv.tv_sec)*1000000+qtendtv.tv_usec-qtbegintv.tv_usec;
        timediff = timediff/20;
        printf("Demo framerate is %.2f \n",1000000.0/timediff);
    }

    //printf("IrisStatusInfoCallback.............................\n");
    g_irisPos.leftIrisPos.xPixel = enrIdenStatus->irisPos.leftIrisPos.xPixel;
    g_irisPos.leftIrisPos.yPixel = enrIdenStatus->irisPos.leftIrisPos.yPixel;
    g_irisPos.rightIrisPos.xPixel = enrIdenStatus->irisPos.rightIrisPos.xPixel;
    g_irisPos.rightIrisPos.yPixel = enrIdenStatus->irisPos.rightIrisPos.yPixel;
    g_curDist = enrIdenStatus->irisPos.dist;
    g_leftRadius = enrIdenStatus->irisPos.leftIrisPos.radius;
    g_rightRadius = enrIdenStatus->irisPos.rightIrisPos.radius;

    //for test
    g_leftNum = enrIdenStatus->leftIrisProgress;
    g_rightNum = enrIdenStatus->rightIrisProgress;
    g_distEstimation = enrIdenStatus->distEstimation;
    g_UIUEMsgID = enrIdenStatus->uiueID;
    //printf("IrisStatusInfoCallback :g_leftNum=%d g_rightNum=%d\n",g_leftNum,g_rightNum)

    memcpy(irisImgBuf, enrIdenStatus->imageData, IK_DISPLAY_IMG_SIZE);
    QImage *dispImg_ov2710 = new QImage(irisImgBuf, IK_DISPLAY_IMG_WIDTH, IK_DISPLAY_IMG_HEIGHT, QImage::Format_Indexed8);
    QVector<QRgb> my_table;
    for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
    dispImg_ov2710->setColorTable(my_table);
    irisImg = *dispImg_ov2710;
    irisImg = irisImg.mirrored(false, true);
    //    if(!irisImg.isNull())
    //    {
    //        tmp_ov2710 = irisImg.scaled(ui->imageView->width(), ui->imageView->height());
    //        tmp_ov2710 = tmp_ov2710.mirrored(false, true);
    //    }
    if(Save_Img_Flag_ov2710)
    {
        QString filename = QTime::currentTime().toString("hh-mm-ss-zzz");
        bool res = irisImg.save("ov2710_tz/"+filename+".bmp","bmp");
        if(res == true)
        printf("dispImg_ov2710 save image res is %d\n",res);
    }

    imPaintEvent.RaisePaintEvent();
}

testclass::testclass(QObject *parent) : QObject(parent),ov5640framesThread(NULL)
{    
    imgProviderRGB = new ScreenImageProvider();
    imgProviderIris = new ScreenImageProvider();
    connect(&imPaintEvent, SIGNAL(sigPaint()), this, SLOT(slotUpdateImageov2710()));
    slotOnBtnOpenRGBDevClicked();
    slotOnBtnOpenIrisDevClicked();

}

void testclass::slotOnBtnOpenIrisDevClicked()
{
//    if(ov5640framesThread != NULL)
//    {
//        ov5640framesThread->stopThread();
//        ov5640framesThread->deleteLater();
//        ov5640framesThread = NULL;
//    }
//    usleep(50000);
    int funFlag = E_USBSDK_DEFAULT_ERROR;
    funFlag = IKUSBSDK_Init(IrisStatusInfoCallback);
    if (E_USBSDK_OK != funFlag)
    {
        if (E_USBSDK_INVALID_DEV_STATUS == funFlag)
        {
            cout << "设备初始化失败！" << endl;
        }
        else
        {
            cout << "算法初始化失败！" << endl;
        }
    }
}
int i = 0;
void testclass::slotUpdateImageov2710()
{    
    imgProviderIris->setimage(irisImg);

    if(i < 30)
    {
        g_UIUEMsgID = UIUE_MsgID_EYE_TOO_CLOSE;
    }
    else if(i >= 30 && i < 60)
    {
        g_UIUEMsgID = UIUE_MsgID_EYE_TOO_FAR;
    }
    else if(i >= 60 && i < 120)
    {
        g_UIUEMsgID = 0;
    }
    else if( i == 120)
    {
        i = 0;
    }
    i++;

    switch (g_UIUEMsgID)
    {
    case UIUE_MsgID_EYE_TOO_CLOSE:
        setmsgText(QString::fromUtf8("请退后"));
        break;
    case UIUE_MsgID_EYE_TOO_FAR:
        setmsgText(QString::fromUtf8("请靠近"));
        break;
    default:
        setmsgText(QString::fromUtf8("距离合适"));
        break;
    }
//    setmsgID(1234);
    emit sigUpdateImageIris();
}

void testclass::slotOnBtnOpenRGBDevClicked()
{
//    IKUSBSDK_Release();

    ov5640framesThread = new DemoOv5640Thread(this);
    connect(ov5640framesThread, SIGNAL(newFrameGetted(QImage)), this, SLOT(ov5640imageUpdated(QImage)));
    ov5640framesThread->startThread();
}

void testclass::ov5640imageUpdated(QImage img)
{
    int timediff_ov5640;
    QImage tmp_ov5640;
    tmp_ov5640 = img.scaled(640,720,Qt::KeepAspectRatioByExpanding).mirrored(true, false);

    if(qtnum_ov5640==0) gettimeofday(&qtbegintv_ov5640,NULL);
    qtnum_ov5640++;
    if(qtnum_ov5640 >=20)
    {
        qtnum_ov5640 = 0;
        gettimeofday(&qtendtv_ov5640,NULL);
        timediff_ov5640 =  (qtendtv_ov5640.tv_sec-qtbegintv_ov5640.tv_sec)*1000000+qtendtv_ov5640.tv_usec-qtbegintv_ov5640.tv_usec;
        timediff_ov5640 = timediff_ov5640/20;
        //        qDebug() << "qt 0v5640 framerate is  " << 1.0 * 1000000.0 / timediff_ov5640 << endl;
        printf("qt 0v5640 framerate is %.2f aaaa\n", 1000000.0/timediff_ov5640);
    }

//    imgProvider->setimage(faceImg);
    imgProviderRGB->setimage(tmp_ov5640);
    emit sigUpdateImageRGB();
}
void testclass::slotOnBtnSaveImgIrisDevClicked()
{
    Save_Img_Flag_ov2710 = true;
}

void testclass::slotOnBtnSaveImgRGBDevClicked()
{
    ov5640framesThread->Save_Img_Flag_ov5640 = true;
}

QString testclass::getmsgText() const
{
    return m_msgText;
}

void testclass::setmsgText(const QString &tmp)
{
    if(m_msgText != tmp)
    {
        m_msgText = tmp;
        msgTextChanged();
    }
}
