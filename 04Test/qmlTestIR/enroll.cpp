#include "enroll.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

enroll::enroll(QObject *parent) : QObject(parent),
    g_isEnrollThreadEnd(true),_irisMode(IrisModeBoth),s_enrIrisL(nullptr),s_enrIrisR(nullptr)
{
    qRegisterMetaType<IKResultFlag>("IKResultFlag");
    _numEnrL = 0;                       //左眼注册图像个数
    _numEnrR = 0;                       //右眼注册图像个数
    s_leftEnrNum = 0;
    s_rightEnrNum = 0;
    connect(this, SIGNAL(beginEnroll()), this, SLOT(doEnroll()));
}

int enroll::startEnroll()
{
    emit beginEnroll();
    return 0;
}

int enroll::stopEnroll()
{
    int ret = IKUSBSDK_StopEnroll();
    return ret;
}

void enroll::doEnroll()
{
////    LOG_INFO("进入注册线程");
    g_isEnrollThreadEnd = false;
    IKResultFlag  flag;
    IKAlgConfigStruct algConfig;

    algConfig.minEnrIdenTime = IK_MIN_ENR_TIME;
    algConfig.maxEnrIdenTime = IK_MAX_ENR_TIME;
    algConfig.reservedPara[IK_RESERVEDPARA_BLINK] = 0;
    algConfig.reservedPara[IK_RESERVEDPARA_I2FMODE] = I2FModeIris;
    s_isEnrollStoped = false;
    for(int i=0;i<g_constMaxEnrollImNum;i++)
    {
        memset(&enrIrisL[i],0,sizeof(IKSDKIrisInfo));
        memset(&enrIrisR[i],0,sizeof(IKSDKIrisInfo));
    }
    int funResult = IKUSBSDK_StartIrisEnroll(enrIrisL, 3, enrIrisR, 3, _irisMode, flag, &algConfig);
    if(E_USBSDK_OK == funResult)
    {
        //注册成功，处理注册结果
        s_enrIrisL    = enrIrisL;
        s_enrIrisR    = enrIrisR;
        s_enrLrFlag   = flag;
        if(_irisMode == IrisModeLeft)
        {
            s_leftEnrNum  = 3;
            s_rightEnrNum = 0;
        }
        else if(_irisMode == IrisModeRight)
        {
            s_leftEnrNum  = 0;
            s_rightEnrNum = 3;
        }
        else
        {
            s_leftEnrNum  = 3;
            s_rightEnrNum = 3;
        }
//        s_enrollInteraction->PlayInteraction(EnrollSuccess, DistSuitable ,false);
//        LOG_INFO("注册成功");
        qDebug() << "enroll success";
        g_isEnrollThreadEnd = true;

        QFile enrIris("enrIris.txt");
        if(enrIris.open(QIODevice::WriteOnly))
        {
            QDataStream out(&enrIris);
            QByteArray ba;
            ba.resize(6 * sizeof(IKSDKIrisInfo)); //设置容量
            qDebug() << "ImgHeight:" << enrIrisL[0].ImgHeight << "ImgWidth:" << enrIrisL[0].ImgWidth
                     << "ImgType:" << enrIrisL[0].ImgType << "IrisRow:" << enrIrisL[0].IrisRow
                     << "IrisRow:" << enrIrisL[0].IrisRow << "IrisCol:" << enrIrisL[0].IrisCol
                     << "IrisRadius:" << enrIrisL[0].IrisRadius << "FocusScore:" << enrIrisL[0].FocusScore
                     << "PercentVisible:" << enrIrisL[0].PercentVisible << "saturation:"<< enrIrisL[0].saturation
                     << "InterlaceValue:" << enrIrisL[0].InterlaceValue << "QualityScore:" << enrIrisL[0].QualityScore;

            //序列化
            for(int i = 0; i < 3; i++)
            {
                memcpy(ba.data() + i * sizeof(IKSDKIrisInfo), &enrIrisL[i], sizeof(IKSDKIrisInfo)); //指针移动,写入多个数据
            }
            for(int i = 0; i < 3; i++)
            {
                memcpy(ba.data() + (3 + i) * sizeof(IKSDKIrisInfo), &enrIrisR[i], sizeof(IKSDKIrisInfo)); //指针移动,写入多个数据
            }
            out << ba;
            enrIris.close();
        }
        else
        {//文件打开失败

        }
        emit enrollState(0);
        return;
    }
    else if(E_USBSDK_DEFAULT_ERROR == funResult)
    {
        //注册失败，在界面显示注册失败
//        s_enrollInteraction->PlayInteraction(EnrollFailed, DistSuitable ,false);
//        LOG_INFO("注册失败");
        g_isEnrollThreadEnd = true;
        qDebug() << "enroll falied";
        emit enrollState(1);
        return;
    }
    else if(funResult == E_USBSDK_ENR_IDEN_INTERRUPT)
    {
//        LOG_WARN("注册被终止");
        g_isEnrollThreadEnd = true;
        emit enrollState(2);
        return;
    }
//    s_enrollInteraction->ClearResult();
//    LOG_INFO("注册结果 funResult=%d",funResult);
//    imPaintEvent.RaisePaintEnrollResultEvent(funResult, enrIrisL, 3, enrIrisR, 3, flag);
    g_isEnrollThreadEnd = true;
    qDebug() << "enroll  end";
    emit enrollState(3);
}
