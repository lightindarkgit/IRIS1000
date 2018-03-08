/*************************************************
Copyright: 中科虹霸
作者: lhc, gw, tz, hyq
创建日期: 2018-02-09
描述: QML和C++中间处理的主代码
**************************************************/
#include "mainclass.h"
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUuid>
#include <QDir>
#include <QList>
#include <QFileInfo>
#include <QProcess>
#include <QMutexLocker>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

#include<sys/time.h>  //gettimeofday
#include <stdio.h>

#include "ThreadEnroll.h"
#include "idenworker.h"
#include "irisManager.h"
#include "ptzbase.h"
#include "playsounds.h"
//#include <QSound>

bool Save_Img_Flag_ov2710 = false;

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
bool  g_isAble2710SendImage = true;   ///允许2710采集到的图发送给界面显示.true允许,false不允许
bool  g_usePP = false;  //2710乒乓判断
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
//static char g_grayPpmHeader[PPMHeaderLength];
//static unsigned char g_grayImBuffer[ImageSize + PPMHeaderLength];

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

int nnnnn = 0;

/*****************************************************************************
 *                         IKUSBSDK_Init需要的回调函数
 *  函 数 名： IrisStatusInfoCallback
 *  功    能：回调函数，获取sdk返回参数，特别是虹膜数据
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
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
        printf("IrisStatusInfoCallback framerate is %.2f \n",1000000.0/timediff);
        qDebug() << "IrisStatusInfoCallback framerate is " << 1000000.0/timediff;
    }

    //printf("IrisStatusInfoCallback.............................\n");
    if(enrIdenStatus == NULL)
    {
//        qDebug() << "enrIdenStatus is null";
        return;
    }
    g_irisPos.leftIrisPos.xPixel = enrIdenStatus->irisPos.leftIrisPos.xPixel;
    g_irisPos.leftIrisPos.yPixel = enrIdenStatus->irisPos.leftIrisPos.yPixel;
    g_irisPos.rightIrisPos.xPixel = enrIdenStatus->irisPos.rightIrisPos.xPixel;
    g_irisPos.rightIrisPos.yPixel = enrIdenStatus->irisPos.rightIrisPos.yPixel;
    g_curDist = enrIdenStatus->irisPos.dist;
    g_leftRadius = enrIdenStatus->irisPos.leftIrisPos.radius;
    g_rightRadius = enrIdenStatus->irisPos.rightIrisPos.radius;

    if(enrIdenStatus->distEstimation != 100)
    {
//        qDebug() << "enter  IrisStatusInfoCallback ..... call" << enrIdenStatus->distEstimation << enrIdenStatus->uiueID << enrIdenStatus->irisPos.dist;
//        qDebug() << enrIdenStatus->rightIrisProgress << enrIdenStatus->leftIrisProgress;
//        LPro = enrIdenStatus->leftIrisProgress;
//        RPro = enrIdenStatus->rightIrisProgress;
//        Dis = enrIdenStatus->irisPos.dist;
        int m_dist = enrIdenStatus->irisPos.dist;
        int m_distEstimation = enrIdenStatus->distEstimation;
//        qDebug() << "irisPos dist" << m_dist<< "estimation" << m_distEstimation;
    }
    //for test
    g_leftNum = enrIdenStatus->leftIrisProgress;
    g_rightNum = enrIdenStatus->rightIrisProgress;
    g_distEstimation = enrIdenStatus->distEstimation;
    g_UIUEMsgID = enrIdenStatus->uiueID;
    //printf("IrisStatusInfoCallback :g_leftNum=%d g_rightNum=%d\n",g_leftNum,g_rightNum)
    nnnnn++;
        unsigned char irisImgBufA[IK_IMG_SIZE + IK_BMP_BMP_HEADER_SIZE];
        unsigned char irisImgBufB[IK_IMG_SIZE + IK_BMP_BMP_HEADER_SIZE];
        if(g_usePP)
        {
            qDebug() << "g_usePP is true to false" << nnnnn;
            memcpy(irisImgBufA, enrIdenStatus->imageData, IK_DISPLAY_IMG_SIZE);
        }
        else if(!g_usePP)
        {
            qDebug() << "g_usePP is false to true" << nnnnn;
            memcpy(irisImgBufB, enrIdenStatus->imageData, IK_DISPLAY_IMG_SIZE);
        }
        if(g_isAble2710SendImage)
        {
            g_isAble2710SendImage = false;
        if(g_usePP)
        {
            g_usePP = false;
            memcpy(irisImgBuf, irisImgBufA, IK_DISPLAY_IMG_SIZE);
            qDebug() << "cpy  buf A" << nnnnn;
        }
        else if(!g_usePP)
        {
            g_usePP = true;
            memcpy(irisImgBuf, irisImgBufB, IK_DISPLAY_IMG_SIZE);
            qDebug() << "cpy  buf B" << nnnnn;
        }
//        if(Save_Img_Flag_ov2710)
//        {
//            QString fullFilePath = "tzimage_demo_ov2710/";
//            QDir dir(fullFilePath);
//            if(!dir.exists())
//            {
//                QDir dir1;
//                bool ok = dir1.mkdir(fullFilePath);
//                if( ok )
//                    printf("create path successful.\n");
//                else
//                    printf("create path failed.\n");
//            }
//                QString filename = QTime::currentTime().toString("hh-mm-sszzz");
//                bool res = zDispImg_ov2710.save(filename+".bmp","bmp");
//                if(res == true)
//                {
////                printf("demo saveing image ok!\n");
//                }
//        }
        imPaintEvent.RaisePaintEvent();
    }
    else
    {
        qDebug() << " ................................................" << nnnnn;
    }

}

/*****************************************************************************
 *                         构造函数
 *  函 数 名： mainClass
 *  功    能：初始化必要参数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：
 *  创建时间：2018-02-09
 *  修 改 人：lhc,gw,tz,hyq
 *  修改时间：20180302 by yqhe，增加初始化舵机
 *****************************************************************************/
mainClass::mainClass(QObject *parent) : QObject(parent),m_pOv5640framesThread(nullptr), m_pEnrollWork(nullptr),
    m_pIdenWork(nullptr), m_pPlaySound(nullptr)
{
     // added at 20180302 by yqhe, 初始化舵机
    initSteering();

    msqldatabase::get_Instance()->open();
    imgProviderRGB = new ScreenImageProvider();
    imgProviderIris = new ScreenImageProvider();
    imgProIrisImgL = new ScreenImageProvider();
    imgProIrisImgR = new ScreenImageProvider();
    connect(&imPaintEvent, SIGNAL(sigPaint()), this, SLOT(slotUpdateImageov2710()), Qt::UniqueConnection);
    slotOnBtnOpenRGBDevClicked();
    slotOnBtnOpenIrisDevClicked();

    m_isSuspect = false;    //存疑标志
    oldMonthStr = QDateTime::currentDateTime().toString("yyyy-MM");

    m_pIdenWork = new idenWorker;
    m_pIdenWork->moveToThread(&m_idenThread);
    connect(m_pIdenWork, SIGNAL(idenResult(long,int)), this, SLOT(showIdenState(long,int)), Qt::UniqueConnection);
    m_idenThread.start();

    m_pCodeListL = nullptr;
    m_pCodeListR = nullptr;
    m_leftNum = 0;
    m_rightNum = 0;
    loadIrisCodeList();  //加载特征
    m_pIdenWork->initARG(m_pCodeListL, m_pCodeListR, m_codeNumL, m_codeNumR);  //初始化识别线程参数
//    m_pIdenWork->startIden();

    m_pSwipeCard = new ThreadSwipeCard;
    connect(m_pSwipeCard,SIGNAL(sigSendCarNum(int,int)),this,SLOT(slotReciveCarNum(int,int)));
    m_pSwipeCard->start();

    m_pPlaySound = new playSounds;
}

/*****************************************************************************
 *                         初始化 sdk 槽函数
 *  函 数 slotOnBtnOpenIrisDevClicked
 *  功    能：初始化 sdk 槽函数，获取虹膜图像的前提
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::slotOnBtnOpenIrisDevClicked()
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
            qDebug() << "设备初始化失败！";
        }
        else
        {
            qDebug() <<  "算法初始化失败！";
        }
    }
}
/*****************************************************************************
 *                         将距离提示信息发送到界面进行显示的槽函数
 *  函 数 slotUpdateImageov2710
 *  功    能：将距离提示信息发送到界面进行显示的槽函数
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::slotUpdateImageov2710()
{
    {
        QMutex mutex;
        QMutexLocker locker(&mutex);
        unsigned char irisImgBufZ[IK_IMG_SIZE + IK_BMP_BMP_HEADER_SIZE];
        memcpy(irisImgBufZ, irisImgBuf, IK_DISPLAY_IMG_SIZE);
        QImage  zDispImg_ov2710(irisImgBufZ, IK_DISPLAY_IMG_WIDTH, IK_DISPLAY_IMG_HEIGHT, QImage::Format_Indexed8);
        if(!zDispImg_ov2710.isNull())
        {
            QImage irisImgTmp(IK_DISPLAY_IMG_WIDTH, IK_DISPLAY_IMG_HEIGHT, QImage::Format_Indexed8);
            QVector<QRgb> my_table;
            for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
            zDispImg_ov2710.setColorTable(my_table);

        //        QString filename = QTime::currentTime().toString("111hh-mm-sszzz");
        //        zDispImg_ov2710.save(filename+".bmp","bmp");
            irisImgTmp = zDispImg_ov2710.copy();
            irisImg = irisImgTmp.mirrored(false, true);
        }
    }

//    if(g_usePP)
//    {
    qDebug() << "send image to QML" << nnnnn;
        imgProviderIris->setimage(irisImg);  //这句是为了暂时查看虹膜图像，正式产品不需要
//    }
//    else if(!g_usePP)
//    {
//         imgProviderIris->setimage(irisImgA);
//    }

    setleftNum(g_leftNum);
    setrightNum(g_rightNum);

    switch (g_UIUEMsgID)
    {
    case UIUE_MsgID_EYE_TOO_CLOSE:
        setmsgText(QString::fromUtf8("请退后"));
        break;
    case UIUE_MsgID_EYE_TOO_FAR:
        setmsgText(QString::fromUtf8("请靠近"));
        break;
    case UIUE_MsgID_SUITABLE:
        setmsgText(QString::fromUtf8("距离合适"));
        break;
    case UIUE_MsgID_EYE_NOT_FOUND:
    case UIUE_MsgID_EYE_TOO_UP:
    case UIUE_MsgID_EYE_TOO_DOWN:
    case UIUE_MsgID_EYE_TOO_LEFT:
    case UIUE_MsgID_EYE_TOO_RIGHT:
    case UIUE_MsgID_BAD_IMAGE_QUALITY:
        setmsgText(QString::fromUtf8("请将双眼对准取景框"));
        break;
    case UIUE_MsgID_MOTION_BLUR:
    case UIUE_MsgID_FOCUS_BLUR:
        setmsgText(QString::fromUtf8("正在扫描，请保持手机稳定"));
        break;
    case UIUE_MsgID_WITH_GLASS:
        setmsgText(QString::fromUtf8("尝试调整下角度或摘掉眼镜"));
        break;
    case UIUE_MsgID_BAD_EYE_OPENNESS:
        setmsgText(QString::fromUtf8("请睁大眼睛或调整下角度"));
        break;
    default:
        setmsgText(QString::fromUtf8("距离......."));
        break;
    }
//    setmsgID(1234);
    emit sigUpdateImageIris();
}
void mainClass::slotOnBtnOpenRGBDevClicked()
{
//    IKUSBSDK_Release();
    if(m_pOv5640framesThread == nullptr)
    {
        m_pOv5640framesThread = new DemoOv5640Thread(this);
        connect(m_pOv5640framesThread, SIGNAL(newFrameGetted(QImage)),
                this, SLOT(ov5640imageUpdated(QImage)), Qt::UniqueConnection);
        m_pOv5640framesThread->startThread();
    }
}
/*****************************************************************************
 *                         获取图像后刷新处理槽函数
 *  函 数 ov5640imageUpdated
 *  功    能：将获取的5640数据发送QML，进行显示
 *  说    明：
 *  参    数：QImage img
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-09
 *  修 改 人：tz，gw，hyq
 *  修改时间：
 *****************************************************************************/
void mainClass::ov5640imageUpdated(QImage img)
{
    int timediff_ov5640;
    QImage tmp_ov5640;
    tmp_ov5640 = img.scaled(640,720,Qt::KeepAspectRatioByExpanding);//.mirrored(true, false);
    if(!tmp_ov5640.isNull())
    {
        tmp_ov5640 = tmp_ov5640.copy(160, 180, 320, 360);
        if(!tmp_ov5640.isNull())
        {
            if(m_isSuspect) {
                m_isSuspect = false;
                saveQuestionerFaceHandle();
                QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
                QString fileName = questionerFaceDir + currentDateTime + ".jpg";
                if(tmp_ov5640.save(fileName, "JPG"))
                    printf("Save questionerFace success.\n");
                else
                    printf("Save questionerFace failed.\n");
            }
            tmp_ov5640 = tmp_ov5640.scaled(640,720);
            if(!tmp_ov5640.isNull())
            {
                if(qtnum_ov5640==0) gettimeofday(&qtbegintv_ov5640,NULL);
                qtnum_ov5640++;
                if(qtnum_ov5640 >=20)
                {
                    qtnum_ov5640 = 0;
                    gettimeofday(&qtendtv_ov5640,NULL);
                    timediff_ov5640 =  (qtendtv_ov5640.tv_sec-qtbegintv_ov5640.tv_sec)*1000000+qtendtv_ov5640.tv_usec-qtbegintv_ov5640.tv_usec;
                    timediff_ov5640 = timediff_ov5640/20;
                    qDebug() << "qt 0v5640 framerate is  " << 1.0 * 1000000.0 / timediff_ov5640;
                    printf("qt ov5640 framerate is %.2f aaaa\n", 1000000.0/timediff_ov5640);
                }

                //    imgProvider->setimage(faceImg);
                if(!tmp_ov5640.isNull())
                {
                    imgProviderRGB->setimage(tmp_ov5640);
                    emit sigUpdateImageRGB();
                }
                else
                {
                    qDebug() << "tmp_ov5640 is Null";
                }
            }
        }
    }
}
void mainClass::slotOnBtnSaveImgIrisDevClicked()
{
    Save_Img_Flag_ov2710 = true;
}

void mainClass::slotOnBtnSaveImgRGBDevClicked()
{
    m_pOv5640framesThread->Save_Img_Flag_ov5640 = true;
}
/*****************************************************************************
 *                         将注册人员信息及虹膜信息保存到数据库
 *  函 数 名：saveEnrollIrisData
 *  功    能：保存人员信息到数据库，成功后继续保存虹膜数据到数据库，并更新内存数据
 *  说    明：错误处理待完善
 *  参    数：DBPersonInfo personInfo
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-24
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::savePersonIrisData(DBPersonInfo personInfo)
{
    qDebug() << "continue save iris data";
    QString personID = personInfo.m_personid;

    for(int i = 0; i < m_infoLis.length(); i++)
    {
        m_infoLis[i]->m_personid = personID;
    }
    for(int i = 0; i < m_enrollInfoList.length(); i++)
    {
        m_enrollInfoList[i]->m_personid = personID;
    }
    personInfo.m_hasirisdata = true;
    if(E_MSQL_SUCCESS == msqldatabase::get_Instance()->addPersonInfo(&personInfo))
    {
        qDebug() << "AddPersonInfo is successful.";
        emit sigPersonTableUpdated();
        if(m_infoLis.length() > 0)
        {
            if(E_MSQL_SUCCESS == msqldatabase::get_Instance()->insertIrisInfos(m_infoLis))
            {
                qDebug() << "insertIrisInfos is successful.";
                InfoData oneInfo;
                oneInfo.PeopleData.CardID = personInfo.m_cardid.toStdString();
                oneInfo.PeopleData.IsSuper = personInfo.m_superid;
                oneInfo.PeopleData.Name = personInfo.m_name.toStdString();
                oneInfo.PeopleData.PersonID = personInfo.m_personid.toStdString();
                oneInfo.PeopleData.Sex = personInfo.m_sex.toStdString();
                oneInfo.PeopleData.UserID = personInfo.m_id.toStdString();

                for(int i = 0; i < m_infoLis.length(); i++)
                {
                    memcpy(oneInfo.FeatureData, m_infoLis[i]->m_iriscode, IK1000_ENROLL_FEATURE_SIZE);
                    oneInfo.PeopleData.FeatureID = m_infoLis[i]->m_irisdataid.toStdString();
                    oneInfo.ud = oneInfo.PeopleData.FeatureID;
                    oneInfo.TypeControl = m_infoLis[i]->m_eyeflag == 1 ? EyeFlag::Left : EyeFlag::Right ;
                    IrisManager::get_instance()->addFeatureData(oneInfo);  //加入到内存中
                }
                qDebug() << IrisManager::get_instance()->getIrisFeature(EyeFlag::Left, m_pCodeListL, m_codeNumL);
                qDebug() << IrisManager::get_instance()->getIrisFeature(EyeFlag::Right, m_pCodeListR, m_codeNumR);
                m_pIdenWork->initARG(m_pCodeListL, m_pCodeListR, m_codeNumL, m_codeNumR);

                if(m_enrollInfoList.length() > 0)
                {
//                    if(E_MSQL_SUCCESS == msqldatabase::get_Instance()->insertEnrollParas(m_enrollInfoList))
//                    {
//                        qDebug() << "insertEnrollParas is successful.";
//                    }
//                    else
//                    {//保存失败
//                        qDebug() << "InsertEnrollParas is failed.";
//                    }
                }
                else
                {//数据错误？？
                    qDebug() << "InsertEnrollParas data is wrong.";
                }
            }
            else
            {//保存失败
                qDebug() << "InsertIrisInfos is failed.";
            }
        }
        else
        {//数据错误？
            qDebug() << "InsertIrisInfos data is wrong.";
        }
    }
    else
    {
        qDebug() << "AddPersonInfo is failed.";
    }
}
/*****************************************************************************
 *                         接收注册成功槽函数
 *  函 数 名：saveEnrollIrisData
 *  功    能：接收注册成功发过来的虹膜信息，并保存
 *  说    明：
 *  参    数：IKSDKIrisInfo *enrIrisL, int numEnrL, IKSDKIrisInfo *enrIrisR, int numEnrR, IKResultFlag IKflag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-24
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::saveEnrollIrisData(IKSDKIrisInfo *enrIrisL, int numEnrL, IKSDKIrisInfo *enrIrisR, int numEnrR, IKResultFlag IKflag)
{
    Q_UNUSED(IKflag);
    QDateTime cuDT = QDateTime::currentDateTime();
    m_infoLis.clear();
    m_enrollInfoList.clear();
    for(int i = 0; i < numEnrL; i++)
    {
        PIRISUserInfo newIrisInfo = new IRISUserInfo();
        newIrisInfo->m_devsn = "devsn";
        newIrisInfo->m_eyeflag = 1;
        memcpy(newIrisInfo->m_eyepic, enrIrisL[i].imgData, IK_IRIS_IMG_SIZE);
        memcpy(newIrisInfo->m_iriscode, enrIrisL[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
        memcpy(newIrisInfo->m_matchiriscode,enrIrisL[i].irisRecTemplate, IK_IDEN_FEATURE_SIZE);
        newIrisInfo->m_irisdataid = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
        newIrisInfo->m_personid = "personid";
        newIrisInfo->m_regtime = cuDT;
        newIrisInfo->m_iriscodelen = IK_ENROLL_FEATURE_SIZE;
        newIrisInfo->m_matchiriscodelen = IK_IDEN_FEATURE_SIZE;
        newIrisInfo->m_eyepiclen = IK_IRIS_IMG_SIZE;
        m_infoLis.append(newIrisInfo);
        qDebug() << "m_infoLis numEnrL" << i;

        PIRISEnrPara newIrisPara = new IRISEnrPara();
        newIrisPara->m_focusscore = enrIrisL[i].FocusScore;
        newIrisPara->m_interlacevalue = enrIrisL[i].InterlaceValue;
        newIrisPara->m_iriscol = enrIrisL[i].IrisCol;
        newIrisPara->m_irisdataid = newIrisInfo->m_irisdataid;
        newIrisPara->m_irisradius = enrIrisL[i].IrisRadius;
        newIrisPara->m_irisrow = enrIrisL[i].IrisRow;
        newIrisPara->m_memo =  "memo";
        newIrisPara->m_percentvisible = enrIrisL[i].PercentVisible;
        newIrisPara->m_personid = "personid";
        newIrisPara->m_pupilcol = 0;// "pupilcol";
        newIrisPara->m_pupilradius = 0;//"pupilradius"
        newIrisPara->m_pupilrow = 0;//"pupilrow"
        newIrisPara->m_qualitylevel = 0;//"qualitylevel";
        newIrisPara->m_qualityscore = enrIrisL[i].QualityScore;
        newIrisPara->m_regtime = cuDT;
        newIrisPara->m_spoofvalue = 0;//"spoofvalue"
        m_enrollInfoList.append(newIrisPara);
        qDebug() << "m_enrollInfoList L" << i;

    }
    for(int i = 0; i < numEnrR; i++)
    {
        PIRISUserInfo newIrisInfo = new IRISUserInfo();
        newIrisInfo->m_devsn = "devsn";
        newIrisInfo->m_eyeflag = 2;
        memcpy(newIrisInfo->m_eyepic, enrIrisR[i].imgData, IK_IRIS_IMG_SIZE);
        memcpy(newIrisInfo->m_iriscode, enrIrisR[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
        memcpy(newIrisInfo->m_matchiriscode,enrIrisR[i].irisRecTemplate, IK_IDEN_FEATURE_SIZE);
        newIrisInfo->m_irisdataid = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
        newIrisInfo->m_personid = "personid";
        newIrisInfo->m_regtime = cuDT;
        newIrisInfo->m_iriscodelen = IK_ENROLL_FEATURE_SIZE;
        newIrisInfo->m_matchiriscodelen = IK_IDEN_FEATURE_SIZE;
        newIrisInfo->m_eyepiclen = IK_IRIS_IMG_SIZE;
        m_infoLis .append(newIrisInfo);
        qDebug() << "m_infoLis  numEnrR" << i;

        PIRISEnrPara newIrisPara = new IRISEnrPara();
        newIrisPara->m_focusscore = enrIrisR[i].FocusScore;
        newIrisPara->m_interlacevalue = enrIrisR[i].InterlaceValue;
        newIrisPara->m_iriscol = enrIrisR[i].IrisCol;
        newIrisPara->m_irisdataid = newIrisInfo->m_irisdataid;
        newIrisPara->m_irisradius = enrIrisR[i].IrisRadius;
        newIrisPara->m_irisrow = enrIrisR[i].IrisRow;
        newIrisPara->m_memo =  "memo";
        newIrisPara->m_percentvisible = enrIrisR[i].PercentVisible;
        newIrisPara->m_personid ="personid";
        newIrisPara->m_pupilcol = 0;// "pupilcol";
        newIrisPara->m_pupilradius = 0;//"pupilradius"
        newIrisPara->m_pupilrow = 0;//"pupilrow"
        newIrisPara->m_qualitylevel = 0;//"qualitylevel";
        newIrisPara->m_qualityscore = enrIrisR[i].QualityScore;
        newIrisPara->m_regtime = cuDT;
        newIrisPara->m_spoofvalue = 0;//"spoofvalue"
        m_enrollInfoList.append(newIrisPara);
        qDebug() << "m_enrollInfoList R" << i;
    }

    if(numEnrL) {
        QImage irisImgL = GetImg(enrIrisL[numEnrL-1].imgData, IK_IRIS_IMG_SIZE);
        imgProIrisImgL->setimage(irisImgL);
    }
    if(numEnrR) {
        QImage irisImgR = GetImg(enrIrisR[numEnrR-1].imgData, IK_IRIS_IMG_SIZE);
        imgProIrisImgR->setimage(irisImgR);
    }
    emit sigUpdateAddIrisImg(numEnrL, numEnrR);
}

/*****************************************************************************
 *                         接收注册状态槽函数
 *  函 数 showEnrollState
 *  功    能：接收注册状态，并发信号到界面
 *  说    明：
 *  参    数：int state
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-24
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::showEnrollState(int state)
{
    qDebug() << state << " enrollstate";
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
    emit cppEnrollResult(state, tmp);
}
/*****************************************************************************
 *                         接收识别状态槽函数
 *  函 数 名： showIdenState
 *  功    能：接收识别状态， 组织显示文字，并发出信号
 *  说    明：
 *  参    数：long index, int flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-24
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::showIdenState(long index, int flag)
{
    qDebug() << "showIdenState   iden result " << index << flag;
//    m_pPlaySound->Play(SoundID::FARTHER);
    QString tmp;
    PeopleInfo info;
    RecLog recLog;
    switch (flag) {
    case EnrRecLeftFailed:
    case EnrRecRightFailed:
    case EnrRecBothFailed:
        m_isSuspect = true;
        tmp = "识别失败";
        emit cppIdentResult(1, tmp, "");
        break;
    case EnrRecLeftSuccess:
    case EnrRecRightSuccess:
    case EnrRecBothSuccess:
        tmp = "识别成功";
        IrisManager::get_instance()->getPersonInfoByIndex(index, info, EyeFlag::Left);
        tmp = QString::fromStdString(info.Name);
        qDebug() << "id..............." << QString::fromStdString(info.UserID) << info.IsSuper;
        emit cppIdentResult(0, tmp, QString::fromStdString(info.UserID));

        recLog.m_devsn = "sn";
        qDebug() << "id...............ok...............";
        recLog.m_irisdataid = QString::fromStdString(info.FeatureID);
        recLog.m_personid = QString::fromStdString(info.PersonID);
        recLog.m_recogtype = 1;
        recLog.m_recogtime = QDateTime::currentDateTime();
        msqldatabase::get_Instance()->addRecLog(&recLog);
        m_pPlaySound->Play(SoundID::IDENSUCC);
        break;
    case EnrRecUnknown:
        qDebug() << "EnrRecUnknown " << index << flag;
        if(index == -2)
        {
            tmp = "识别中止";
//            emit cppIdentResult(2, tmp);
            qDebug() << "stop" << index << flag;
            return;
        }
        else if(index == -3)
        {
            m_isSuspect = true;
            tmp = "识别超时";
            emit cppIdentResult(3, tmp, "");
            qDebug() << "stop" << index << flag;
            m_pPlaySound->Play(SoundID::RETRY);
            tmp = "正在识别";
        }
        break;
    default:
        break;
    }
//    setTipInfo(tmp);
}

QString mainClass::getmsgText() const
{
    return m_msgText;
}

void mainClass::setmsgText(const QString &tmp)
{
    if(m_msgText != tmp)
    {
        m_msgText = tmp;
        msgTextChanged();
    }
}
/*****************************************************************************
 *                         设置5640采图线程是否可以发送图像函数
 *  函 数 名： setAbleCapImage
 *  功    能：设置5640采图线程是否可以发送图像函数
 *  说    明： 由QML界面传递过来参数，设置5640线程是否可以发送图像给QML进行显示
 *                   一般QML(cpp界面)代码中只需要设置true的过程，不需要对5640线程设置为false，由5640内部处理false
 *  参    数：const bool flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::setAbleCapImage(const bool flag)
{
    m_pOv5640framesThread->setAbleCap(flag);
}

bool mainClass::ableCapImage()
{
    return false;
}

void mainClass::setAbleCapIris(const bool flag)
{
    qDebug() << "g_isAble2710SendImage set true??" << flag << nnnnn;
    g_isAble2710SendImage = flag;
}

bool mainClass::ableCapIris()
{
    return false;
}

/*****************************************************************************
 *                         设置注册线程状态函数
 *  函 数 名： setQmlStartEnroll
 *  功    能：设置注册线程状态函数
 *  说    明： 由QML界面传递过来参数，设置为true开始注册，设置为false停止注册，并设置5640采图线程的运行状态
 *  参    数：const bool flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::setQmlStartEnroll(const bool flag)
{
    m_pOv5640framesThread->setThreadPaused(!flag);
    if(flag)
    {
        if(m_pEnrollWork == nullptr)
        {
            m_pEnrollWork = new ThreadEnroll;
            m_pEnrollWork->moveToThread(&m_enrollThread);
            connect(&m_enrollThread, &QThread::finished, m_pEnrollWork, &QObject::deleteLater, Qt::UniqueConnection);
//            connect(this, SIGNAL(startEnroll()), m_enrollWork, SIGNAL(beginEnroll()));
            connect(m_pEnrollWork, SIGNAL(enrollState(int)), this, SLOT(showEnrollState(int)), Qt::UniqueConnection);
            connect(m_pEnrollWork, SIGNAL(enrollResult(IKSDKIrisInfo*,int,IKSDKIrisInfo*,int,IKResultFlag)),
                    this, SLOT(saveEnrollIrisData(IKSDKIrisInfo*,int,IKSDKIrisInfo*,int,IKResultFlag)), Qt::UniqueConnection);
        }
        m_enrollThread.start();
        m_pEnrollWork->initARG(m_irisEnrMode);
        emit m_pEnrollWork->beginEnroll();
    }
    else if (!flag)
    {
        m_pEnrollWork->stopEnroll();
        m_pEnrollWork->deleteLater();
        m_pEnrollWork = nullptr;
    }
}

bool mainClass::qmlStartEnroll()
{
    return false;
}
void mainClass::setleftNum(const int tmp)
{
    int ln = (tmp * 1.0 / g_constMaxEnrollImNum) *100;
    if(m_leftNum != ln)
    {
        m_leftNum = ln;
        emit leftNumChanged();
        printf("LLLLLLLLLLLLLLLL %d\n",ln);
    }
}

void mainClass::getUserIrisImg(const QString &uid)
{
    QMap<QString, DBPersonInfo> personInfoMap;
    QStringList idList;
    idList.append(uid);
    if(!msqldatabase::get_Instance()->getPersonInfo(personInfoMap, idList)) {
        QMap<QString, DBPersonInfo>::iterator mi = personInfoMap.find(uid);
        if(mi != personInfoMap.end()) {
            DBPersonInfo personInfo = mi.value();
            if(personInfo.m_hasirisdata) {
                QList<PIRISUserInfo> userInfoList;
                QStringList personidList;
                personidList.append(personInfo.m_personid);
                if(!msqldatabase::get_Instance()->getIrisInfo(userInfoList, personidList)) {
                    if(userInfoList.length() == 6) {
                        if(userInfoList[2]->m_eyeflag == 1) {
                            QImage userIrisImgL = GetImg(userInfoList[2]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgL->setimage(userIrisImgL);
                        }
                        else {
                            QImage userIrisImgR = GetImg(userInfoList[2]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgR->setimage(userIrisImgR);
                        }
                        if(userInfoList[5]->m_eyeflag == 1) {
                            QImage userIrisImgL = GetImg(userInfoList[5]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgL->setimage(userIrisImgL);
                        }
                        else {
                            QImage userIrisImgR = GetImg(userInfoList[5]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgR->setimage(userIrisImgR);
                        }
                        emit sigUpdateEditIrisImg(3, 3);
                    }
                    else {
                        if(userInfoList[2]->m_eyeflag == 1) {
                            QImage userIrisImgL = GetImg(userInfoList[2]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgL->setimage(userIrisImgL);
                            emit sigUpdateEditIrisImg(3, 0);
                        }
                        else {
                            QImage userIrisImgR = GetImg(userInfoList[2]->m_eyepic, IK_IRIS_IMG_SIZE);
                            imgProIrisImgR->setimage(userIrisImgR);
                            emit sigUpdateEditIrisImg(0, 3);
                        }
                    }
                }
            }
        }
    }
}

int mainClass::getleftNum()
{
    return m_leftNum;
}

void mainClass::setrightNum(const int tmp)
{
    int rn = (tmp * 1.0 / g_constMaxEnrollImNum) *100;
    if(m_rightNum != rn)
    {
        m_rightNum = rn;
        emit rightNumChanged();
        printf("RRRRRRRRRRRRRRR %d\n",rn);
    }
}

int mainClass::getrightNum()
{
    return m_rightNum;
}

int mainClass::irisEnrMode() const
{
    return m_irisEnrMode;
}

void mainClass::setIrisEnrMode(const int &mode)
{
    m_irisEnrMode = mode;
}
//void mainClass::saveAddUserFromQML(QVariantMap map)
//{
//    qDebug() << "map.userID" << map["userID"].toString();
//    qDebug() << "map.userName" << map["userName"].toString();
//    qDebug() << "map.isAdmin" << map["isAdmin"].toBool();
//}

//void mainClass::setenrollFlage(const bool flag)
//{

//}
/*****************************************************************************
 *                         设置识别线程状态函数
 *  函 数 名： setIdentFlag
 *  功    能：设置识别线程状态函数
 *  说    明： 由QML界面传递过来参数，设置为true开始识别，设置为false停止识别
 *  参    数：const bool flag
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::setIdentFlag(const bool flag)
{
    qDebug() << "--------------------------------------------- flag : " << flag;
    m_pOv5640framesThread->setThreadPaused(!flag);
    if(flag)
    {        
        if(m_pIdenWork->getIdenState())
        {
            m_pIdenWork->startIden();
            qDebug() << "iden start.......";
        }
    }
    else
    {
        m_pIdenWork->stopIden();
        qDebug() << "iden stop.......";
    }
}

bool mainClass::identFlag()
{
    return false;
}
/*****************************************************************************
 *                         加载虹膜特征函数
 *  函 数 名： loadIrisCodeList
 *  功    能：加载虹膜特征函数
 *  说    明： 从数据库中加载虹膜特征，一般只在启动时调用，为全部更新。
 *  参    数：
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::loadIrisCodeList()
{
    IrisManager::get_instance()->loadData();  //从数据库载入数据
//    QFile file("/home/root/enrIris.txt");
//    if(file.open(QIODevice::ReadOnly) < 0)
//    {
//        qDebug() << "feature open failed.";
//    }
//    else
//    {
//        QDataStream in(&file);
//        QByteArray byte;
//        byte.resize(m_codeNumL + m_codeNumR);
//        in >> byte;
//        char *buffer = byte.data();
//        IKSDKIrisInfo irisInfoL[m_codeNumL];
//        IKSDKIrisInfo irisInfoR[m_codeNumR];
//        memset((char*)&irisInfoL, 0, sizeof(IKSDKIrisInfo)*m_codeNumL);
//        memcpy((char *)&irisInfoL, buffer, sizeof(IKSDKIrisInfo)*m_codeNumL);
//        memset((char*)&irisInfoR, 0, sizeof(IKSDKIrisInfo)*m_codeNumR);
//        memcpy((char *)&irisInfoR, buffer+sizeof(IKSDKIrisInfo)*m_codeNumL, sizeof(IKSDKIrisInfo)*m_codeNumR);
//        for(int i = 0; i < m_codeNumL; i++)
//        {
//            memcpy(m_pCodeListL + i*IK_ENROLL_FEATURE_SIZE, irisInfoL[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
//            memcpy(m_pCodeListR + i*IK_ENROLL_FEATURE_SIZE, irisInfoR[i].irisEnrTemplate, IK_ENROLL_FEATURE_SIZE);
//        }
//    }
    qDebug() << IrisManager::get_instance()->getIrisFeature(EyeFlag::Left, m_pCodeListL, m_codeNumL);
    qDebug() << m_codeNumL << "load L num";
    qDebug() << IrisManager::get_instance()->getIrisFeature(EyeFlag::Right, m_pCodeListR, m_codeNumR);
    qDebug() << m_codeNumR << "load R num";
}

QImage mainClass::GetImg(const unsigned char *buffer, int bufferSize)
{
    QImage imageBig;

    if(nullptr == buffer)
    {
        qDebug() << "input ptr buffer is null.";
        return imageBig;
    }

    if(bufferSize < 0 || (bufferSize > 20*1024*1024))
    {
        qDebug() << "bufferSize is too big.";
        return imageBig;
    }

    unsigned char grayImgBuffer[bufferSize + 18];
    sprintf(grayImgBuffer, "P5\n 640 480\n255\n");
    memmove(grayImgBuffer + 18 , buffer , bufferSize);
    imageBig = QImage::fromData(grayImgBuffer,
                                bufferSize + 18,
                                "PGM"
                                ).mirrored(false, true).convertToFormat(QImage::Format_RGB32);

    return imageBig;
}

void mainClass::initSteering()
{
    float angle = ptzBase::get_Instance()->getSteeringAngle();

    qDebug() << "init steering to angle " << angle;
}

/*****************************************************************************
 *
 *  函 数 名：saveQuestionerFaceHandle
 *  功    能：存疑人员人脸图像处理
 *  说    明：
 *  参    数：
 *  返 回 值：
 *  创 建 人：guowen
 *  创建时间：2018-03-02
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void mainClass::saveQuestionerFaceHandle()
{
    //判断目录是否存在
    QDir faceDir(questionerFaceDir);
    if(!faceDir.exists())
        faceDir.mkdir(questionerFaceDir);
    //判断时间
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM");
    if(oldMonthStr != currentDate) {
        //创建月目录
        QString dirName = questionerFaceDir + oldMonthStr;
        QDir monthDir(dirName);
        if(monthDir.mkdir(dirName))
            qDebug("Create Month Dir success.\n");
        else
            qDebug("Create Month Dir failed.\n");
        //移至月目录
        QString cmdStr = "mv " + dirName + "*.jpg " + dirName;
        FILE *stream = popen(cmdStr.toStdString().c_str(), "r");
        pclose(stream);
        //形成月压缩包
        QProcess tarPro;
        QStringList args;
        QString tarName = dirName + ".tar.gz";
        args << "-czf" << tarName << dirName;
        tarPro.execute("tar", args);
        args.clear();
        args << "-rf" << dirName;
        tarPro.startDetached("rm", args);
        oldMonthStr = currentDate;
    }
    //判断容量
    char buf[128];
    QString cmdStr = "du -sh " + questionerFaceDir;
    FILE *stream = popen(cmdStr.toStdString().c_str(), "r");
    memset(buf, 0, sizeof(buf));
    fread(buf, sizeof(char), sizeof(buf), stream);
    pclose(stream);
    QString bufStr(buf);
    int index = bufStr.indexOf("M");
    if(index > 0) {
        QString number = bufStr.left(index);
        int size = number.toInt();
        if(size > 1000) {
            QDir faceDir(questionerFaceDir);
            QStringList filter;
            filter << "*.tar.gz";
            faceDir.setNameFilters(filter);
            QList<QFileInfo> *fileInfo = new QList<QFileInfo>(faceDir.entryInfoList(filter));
            QString earliestFileName;
            for(int i = 0; i < fileInfo->count(); i++) {
                if(i > 0) {
                    earliestFileName = fileInfo->at(i).created() < fileInfo->at(i-1).created() ? fileInfo->at(i).fileName() : fileInfo->at(i-1).fileName();
                    printf("////////////%d//////////\n", fileInfo->at(i).created() > fileInfo->at(i-1).created());
                }
            }
            printf("----------%s---------\n", earliestFileName.toStdString().c_str());
            faceDir.remove(earliestFileName);
        }
    }
}

ThreadSwipeCard::ThreadSwipeCard(QObject *parent)
    : QThread(parent)
{
    startSwipeCardFlg = false;
    stopped = false;
    wiegand = new wiegandrw();
}

void ThreadSwipeCard::run()
{
    while (!stopped) {

        while(startSwipeCardFlg)
        {
            int hid,pid;
            printf("------------------------------------------------------------------ run\n");

            int res = wiegand->wiegandread(hid,pid);
            if(!res)
            {
                printf("read sucess!\n");
                printf("hid = %d,pid = %d\n",hid,pid);
                emit sigSendCarNum(hid,pid);
            }
            else
            {
                printf("read failed!\n");
            }
            sleep(2);
        }
        printf("------------------------------------------------------------------ stop\n");
        sleep(2);
    }

}

bool mainClass::getStartSwipeCard()
{
    return m_pSwipeCard->startSwipeCardFlg;
}

void mainClass::setStartSwipeCard(bool tmp)
{
    if(m_pSwipeCard->startSwipeCardFlg != tmp)
    {
        m_pSwipeCard->startSwipeCardFlg = tmp;
    }
}
void mainClass::slotReciveCarNum(int hid, int pid)
{
    emit sigQmlCarNum(hid,pid);
}
