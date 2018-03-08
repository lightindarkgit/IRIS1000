/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-02-09
描述: 注册线程
**************************************************/
#include "ThreadEnroll.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

/*****************************************************************************
 *                         ThreadEnroll构造函数
 *  函 数 名： ThreadEnroll
 *  功    能：注册构造函数，初始化参数
 *  说    明：
 *  参    数：QObject *parent
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
ThreadEnroll::ThreadEnroll(QObject *parent) : QObject(parent),
    m_isEnrollThreadEnd(true), m_irisMode(IrisModeBoth),m_enrIrisL(nullptr),m_enrIrisR(nullptr)
{
    qRegisterMetaType<IKResultFlag>("IKResultFlag");
    m_leftEnrNum = 0;
    m_rightEnrNum = 0;
    connect(this, SIGNAL(beginEnroll()), this, SLOT(doEnroll()), Qt::UniqueConnection);
    qDebug() << "  init thread enroll";
}

/*****************************************************************************
 *                         注册线程参数设置
 *  函 数 名： initARG
 *  功    能：设置注册模式
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：郭文
 *  创建时间：2018-03-01
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void ThreadEnroll::initARG(IKIrisMode mode)
{
    m_irisMode = mode;
}

/*****************************************************************************
 *                         开始注册接口函数
 *  函 数 名： startEnroll
 *  功    能：开始注册接口函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int ThreadEnroll::startEnroll()
{
    emit beginEnroll();
    return 0;
}
/*****************************************************************************
 *                         停止注册接口函数
 *  函 数 名： stopEnroll
 *  功    能：停止注册接口函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int ThreadEnroll::stopEnroll()
{
    int ret = IKUSBSDK_StopEnroll();
    return ret;
}
/*****************************************************************************
 *                         注册槽函数
 *  函 数 名： doEnroll
 *  功    能：注册槽函数，在此进行实际的注册操作
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-02-09
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void ThreadEnroll::doEnroll()
{
    qDebug() << "enter thread enroll";
    m_isEnrollThreadEnd = false;
    IKResultFlag  flag;
    IKAlgConfigStruct algConfig;

    algConfig.minEnrIdenTime = IK_MIN_ENR_TIME;
    algConfig.maxEnrIdenTime = IK_MAX_ENR_TIME;
    algConfig.reservedPara[IK_RESERVEDPARA_BLINK] = 0;
    algConfig.reservedPara[IK_RESERVEDPARA_I2FMODE] = I2FModeIris;
    m_isEnrollStoped = false;
    for(int i = 0; i < g_constMaxEnrollImNum; i++)
    {
        memset(&enrIrisL[i], 0, sizeof(IKSDKIrisInfo));
        memset(&enrIrisR[i], 0, sizeof(IKSDKIrisInfo));
    }
    int funResult = IKUSBSDK_StartIrisEnroll(enrIrisL, g_constMaxEnrollImNum, enrIrisR, g_constMaxEnrollImNum,
                                             m_irisMode, flag, &algConfig);
    if(E_USBSDK_OK == funResult)
    {
        //注册成功，处理注册结果
        m_enrIrisL    = enrIrisL;
        m_enrIrisR    = enrIrisR;
        m_enrLrFlag   = flag;
        if(m_irisMode == IrisModeLeft)
        {
            m_leftEnrNum  = g_constMaxEnrollImNum;
            m_rightEnrNum = 0;
        }
        else if(m_irisMode == IrisModeRight)
        {
            m_leftEnrNum  = 0;
            m_rightEnrNum = g_constMaxEnrollImNum;
        }
        else
        {
            m_leftEnrNum  = g_constMaxEnrollImNum;
            m_rightEnrNum = g_constMaxEnrollImNum;
        }
//        LOG_INFO("注册成功");
        qDebug() << "enroll success";
        m_isEnrollThreadEnd = true;
//发出信号，由mainclass处理
        enrollResult(m_enrIrisL, m_leftEnrNum, m_enrIrisR, m_rightEnrNum, flag);
//        QFile enrIris("enrIris.txt");
//        if(enrIris.open(QIODevice::WriteOnly))
//        {
//            QDataStream out(&enrIris);
//            QByteArray ba;
//            ba.resize(6 * sizeof(IKSDKIrisInfo)); //设置容量
//            qDebug() << "ImgHeight:" << enrIrisL[0].ImgHeight << "ImgWidth:" << enrIrisL[0].ImgWidth
//                     << "ImgType:" << enrIrisL[0].ImgType << "IrisRow:" << enrIrisL[0].IrisRow
//                     << "IrisRow:" << enrIrisL[0].IrisRow << "IrisCol:" << enrIrisL[0].IrisCol
//                     << "IrisRadius:" << enrIrisL[0].IrisRadius << "FocusScore:" << enrIrisL[0].FocusScore
//                     << "PercentVisible:" << enrIrisL[0].PercentVisible << "saturation:"<< enrIrisL[0].saturation
//                     << "InterlaceValue:" << enrIrisL[0].InterlaceValue << "QualityScore:" << enrIrisL[0].QualityScore;

//            //序列化
//            for(int i = 0; i < g_constMaxEnrollImNum; i++)
//            {
//                memcpy(ba.data() + i * sizeof(IKSDKIrisInfo), &enrIrisL[i], sizeof(IKSDKIrisInfo)); //指针移动,写入多个数据
//            }
//            for(int i = 0; i < g_constMaxEnrollImNum; i++)
//            {
//                memcpy(ba.data() + (g_constMaxEnrollImNum + i) * sizeof(IKSDKIrisInfo), &enrIrisR[i], sizeof(IKSDKIrisInfo)); //指针移动,写入多个数据
//            }
//            out << ba;
//            enrIris.close();
//        }
//        else
//        {//文件打开失败
//        }
        emit enrollState(0);
        return;
    }
    else if(E_USBSDK_DEFAULT_ERROR == funResult)
    {
        //注册失败，在界面显示注册失败
        m_isEnrollThreadEnd = true;
        qDebug() << "enroll falied";
        emit enrollState(1);
        return;
    }
    else if(funResult == E_USBSDK_ENR_IDEN_INTERRUPT)
    {
//        LOG_WARN("注册被终止");
        m_isEnrollThreadEnd = true;
        emit enrollState(2);
        return;
    }
//    s_enrollInteraction->ClearResult();
//    LOG_INFO("注册结果 funResult=%d",funResult);
//    imPaintEvent.RaisePaintEnrollResultEvent(funResult, enrIrisL, 3, enrIrisR, 3, flag);
    m_isEnrollThreadEnd = true;
    qDebug() << "enroll  end";
//    emit enrollState(3);    //注册结束?
}
