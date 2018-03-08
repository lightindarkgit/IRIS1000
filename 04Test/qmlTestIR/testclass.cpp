#include "testclass.h"
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include "enroll.h"
#include "idenworker.h"

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
int LPro;
int RPro;
int Dis;
//int ov5640_g_width = 480;
//int ov5640_g_height = 640;
QImage faceImg(480,640,QImage::Format_RGB888);
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
    if(enrIdenStatus->distEstimation != 100)
    {
        qDebug() << "enter  enroll ..... call" << enrIdenStatus->distEstimation << enrIdenStatus->uiueID << enrIdenStatus->irisPos.dist;
        qDebug() << enrIdenStatus->rightIrisProgress << enrIdenStatus->leftIrisProgress;
        LPro = enrIdenStatus->leftIrisProgress;
        RPro = enrIdenStatus->rightIrisProgress;
        Dis = enrIdenStatus->irisPos.dist;
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
    irisImg = dispImg_ov2710->copy(0, 0, dispImg_ov2710->width(), dispImg_ov2710->height());
    irisImg = irisImg.mirrored(true, true);
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
    delete dispImg_ov2710;
    dispImg_ov2710 = nullptr;
    imPaintEvent.RaisePaintEvent();
}

void testclass::setTipInfo(const QString &a)
{
    if (a != m_tipInfo)
    {
        m_tipInfo = a;
        emit tipInfoChanged();
    }
//    qDebug() << m_tipInfo.toLocal8Bit() << m_tipInfo.toUtf8() << "set info 1";
}

QString testclass::tipInfo() const
{
    return m_tipInfo;
}

void testclass::setTipInfo2(const QString &a)
{
    if (a != m_tipInfo2)
    {
        m_tipInfo2 = a;
        emit tipInfo2Changed();
    }
//    qDebug() << m_tipInfo2.toLocal8Bit() << m_tipInfo2.toUtf8() << "set info2";
}

QString testclass::tipInfo2() const
{
    return m_tipInfo2;
}

testclass::testclass(QObject *parent) : QObject(parent)/*,ov5640framesThread(NULL)*/
  ,ov2710framesThread(nullptr)
{    
    imgProviderRGB = new ScreenImageProvider();
    imgProviderIris = new ScreenImageProvider();
    connect(&imPaintEvent, SIGNAL(sigPaint()), this, SLOT(slotUpdateImageov2710()));

    memset(irisImgBuf, 0x0, IK_DISPLAY_IMG_HEIGHT * IK_DISPLAY_IMG_WIDTH);

m_tipInfo = "提示";
m_tipInfo2 = "提示2";

    idenState = false;
    codeNumL = codeNumR = 3;
    codeListL = new unsigned char[codeNumL*IK_ENROLL_FEATURE_SIZE];
    codeListR = new unsigned char[codeNumR*IK_ENROLL_FEATURE_SIZE];

    enroll *work = new enroll;
    work->moveToThread(&enrollThread);
    connect(&enrollThread, &QThread::finished, work, &QObject::deleteLater);
    connect(this, SIGNAL(startEnroll()), work, SIGNAL(beginEnroll()));
    connect(work, SIGNAL(enrollState(int)), this, SLOT(showEnrollState(int)));
    enrollThread.start();

    idenWork = new idenWorker;
    idenWork->moveToThread(&idenThread);
    connect(idenWork, SIGNAL(idenResult(long,int)), this, SLOT(showIdenState(long,int)));
    idenThread.start();

}

void testclass::loadIrisCodeList()
{
    QFile file("/home/root/enrIris.txt");
    if(file.open(QIODevice::ReadOnly) < 0) {
        qDebug() << "feature open failed.";
    }
    else {
        QDataStream in(&file);
        QByteArray byte;
        byte.resize(codeNumL+codeNumR);
        in >> byte;
        char *buffer = byte.data();
        IKSDKIrisInfo irisInfoL[codeNumL];
        IKSDKIrisInfo irisInfoR[codeNumR];
        memset((char*)&irisInfoL, 0, sizeof(IKSDKIrisInfo)*codeNumL);
        memcpy((char *)&irisInfoL, buffer, sizeof(IKSDKIrisInfo)*codeNumL);
        memset((char*)&irisInfoR, 0, sizeof(IKSDKIrisInfo)*codeNumR);
        memcpy((char *)&irisInfoR, buffer+sizeof(IKSDKIrisInfo)*codeNumL, sizeof(IKSDKIrisInfo)*codeNumR);

        for(int i = 0; i < codeNumL; i++) {
            memcpy(codeListL + i*IK_ENROLL_FEATURE_SIZE, irisInfoL[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
            memcpy(codeListR + i*IK_ENROLL_FEATURE_SIZE, irisInfoR[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
        }
    }

}

void testclass::showEnrollState(int state)
{
    QString tmp;
    switch(state)
    {
    case 0:
        tmp = "注册成功";
        break;
    case 1:
        tmp = "注册失败";
        break;
    case 2:
        tmp = "注册终止";
        break;
    case 3:
        tmp = "注册结束";
        break;
    }
    setTipInfo(tmp);
}

void testclass::showIdenState(long index, int flag)
{
    QString tmp;
    switch (flag) {
    case EnrRecLeftFailed:
    case EnrRecRightFailed:
    case EnrRecBothFailed:
//        ui->LB_State->setText("识别失败");
//        ui->PB_Ident->setText("开始识别");
        tmp = "识别失败";
        break;
    case EnrRecLeftSuccess:
    case EnrRecRightSuccess:
    case EnrRecBothSuccess:
//        ui->LB_State->setText("识别成功");
//        ui->PB_Ident->setText("开始识别");
        tmp = "识别成功";
        break;
    case EnrRecUnknown:
        if(index == -2) {
            tmp = "识别中止";
        }
        else if(index == -3) {
            tmp = "识别超时";
//            ui->LB_State->setText("识别超时");
            idenWork->startIden();
//            ui->LB_State->setText("正在识别");
            tmp = "正在识别";
        }
        break;
    default:
        break;
    }
    setTipInfo(tmp);
}

void testclass::slotStartEnroll()
{
    setTipInfo("startEnroll");
    setTipInfo2("startEnroll");
    emit startEnroll();
}

void testclass::slotStartIden()
{
    setTipInfo("startIden");
    setTipInfo2("startIden");
    loadIrisCodeList();
    idenWork->initARG(codeListL, codeListR, codeNumL, codeNumR);
    idenWork->startIden();
}

void testclass::slotOnBtnOpenIrisDevClicked()
{
//    if(ov5640framesThread != NULL)
//    {
//        ov5640framesThread->stopThread();
//        ov5640framesThread->deleteLater();
//        ov5640framesThread = NULL;
//    }
    usleep(50000);
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

void testclass::slotUpdateImageov2710()
{
    imgProviderIris->setimage(irisImg);
    emit sigUpdateImageIris();
    QString tmp = QString("左眼%1\n右眼%2\n距离 %3").arg(LPro).arg(RPro).arg(Dis);
    setTipInfo2(tmp);
}

void testclass::slotOnBtnOpenRGBDevClicked()
{
    IKUSBSDK_Release();
//    ov5640framesThread = new DemoOv5640Thread(this);
//    connect(ov5640framesThread, SIGNAL(newFrameGetted(QImage)), this, SLOT(ov5640imageUpdated(QImage)));
//    ov5640framesThread->startThread();
}

//void testclass::ov5640imageUpdated(QImage img)
//{
//    int timediff_ov5640;

//    if(qtnum_ov5640==0) gettimeofday(&qtbegintv_ov5640,NULL);
//    qtnum_ov5640++;
//    if(qtnum_ov5640 >=20)
//    {
//        qtnum_ov5640 = 0;
//        gettimeofday(&qtendtv_ov5640,NULL);
//        timediff_ov5640 =  (qtendtv_ov5640.tv_sec-qtbegintv_ov5640.tv_sec)*1000000+qtendtv_ov5640.tv_usec-qtbegintv_ov5640.tv_usec;
//        timediff_ov5640 = timediff_ov5640/20;
//        //        qDebug() << "qt 0v5640 framerate is  " << 1.0 * 1000000.0 / timediff_ov5640 << endl;
//        printf("qt 0v5640 framerate is %.2f aaaa\n", 1000000.0/timediff_ov5640);
//    }

////    imgProvider->setimage(faceImg);
//    imgProviderRGB->setimage(img);
//    emit sigUpdateImageRGB();
//}

void testclass::slotOnBtnSaveImgIrisDevClicked()
{
    Save_Img_Flag_ov2710 = true;
}

void testclass::slotOnBtnSaveImgRGBDevClicked()
{
//    ov5640framesThread->Save_Img_Flag_ov5640 = true;
}
