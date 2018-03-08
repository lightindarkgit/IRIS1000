/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-02-10
描述: 识别工作者线程
**************************************************/
#include "idenworker.h"
#include <QDebug>
#include <QTime>

/*****************************************************************************
 *                         构造函数
 *  函 数 名：idenWorker
 *  功    能：识别工作者线程的初始化
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
idenWorker::idenWorker(QObject *parent) : QObject(parent)
{
    m_isStop = true;
    m_idenCodeListL = nullptr;
    m_idenCodeListR = nullptr;
    m_idenCodeNumL = 0;
    m_idenCodeNumR = 0;
    connect(this, SIGNAL(startWorker()), this, SLOT(workProcess()), Qt::UniqueConnection);
}

/*****************************************************************************
 *                  初始化参数
 *  函 数 名：initARG
 *  功    能：对识别需要的参数进行初始化
 *  说    明：启动识别之前必须调用
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void idenWorker::initARG(unsigned char *codeListL, unsigned char *codeListR, int codeNumL, int codeNumR)
{
    m_idenCodeListL = codeListL;
    m_idenCodeListR = codeListR;
    m_idenCodeNumL = codeNumL;
    m_idenCodeNumR = codeNumR;
}

/*****************************************************************************
 *                  获取识别线程状态
 *  函 数 名：getIdenState
 *  功    能：获取识别线程的状态，false正在识别，true停止识别
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
bool idenWorker::getIdenState()
{
    return m_isStop;
}

/*****************************************************************************
 *                  开始识别接口
 *  函 数 名：startIden
 *  功    能：启动识别
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int idenWorker::startIden()
{
    emit startWorker();
    return 1;
}

/*****************************************************************************
 *                  停止识别接口
 *  函 数 名：stopIden
 *  功    能：停止识别
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
int idenWorker::stopIden()
{
    qDebug() << "end iden";
    m_isStop = true;
    return IKUSBSDK_StopIden();
}

/*****************************************************************************
 *                  识别具体过程
 *  函 数 名：workProcess
 *  功    能：进行识别，并发出识别结果信号
 *  说    明：
 *  参    数：
 *  返 回 值：无
 *  创 建 人：lhc
 *  创建时间：2018-02-10
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void idenWorker::workProcess()
{
    qDebug() << "in " << QTime::currentTime().toString("hh:mm:ss:zzz");
    m_isStop = false;

//    IKSDKIrisInfo *ptr = (IKSDKIrisInfo*)idenCodeListL;

    IKResultFlag resultFlag;
    IKAlgConfigStruct algConfig;
    IKSDKMatchOutput matchOutputL, matchOutputR;
    IKIrisMode irisMode = IrisModeUndef;

    algConfig.minEnrIdenTime = IK_MIN_REC_TIME;
    algConfig.maxEnrIdenTime = IK_MAX_REC_TIME;
    algConfig.reservedPara[IK_RESERVEDPARA_BLINK] = 0;
    algConfig.reservedPara[IK_RESERVEDPARA_I2FMODE] = I2FModeIris;

    printf("m_idenCodeNumL:%d\nm_idenCodeNumR:%d\n", m_idenCodeNumL, m_idenCodeNumR);

    int idenRet = IKUSBSDK_StartIrisIden(irisMode, m_idenCodeListL, m_idenCodeNumL, &matchOutputL,
                                         m_idenCodeListR, m_idenCodeNumR, &matchOutputR, resultFlag, &algConfig);
    qDebug() << "IKUSBSDK_StartIrisIden return " << idenRet;
    if(idenRet == E_USBSDK_ENR_IDEN_INTERRUPT) {
        qDebug() << "E_USBSDK_ENR_IDEN_INTERRUPT";
        emit idenResult(-2, EnrRecUnknown);
    }
    else if(idenRet == E_USBSDK_IDEN_OVERTIME) {
        qDebug() << "E_USBSDK_IDEN_OVERTIME";
        emit idenResult(-3, EnrRecUnknown);
    }
    else if(idenRet == E_USBSDK_ENR_IDEN_FAILED) {
        qDebug() << "E_USBSDK_ENR_IDEN_FAILED";
        switch (resultFlag) {
        case EnrRecLeftFailed:
            emit idenResult(-1, EnrRecLeftFailed);
            break;
        case EnrRecRightFailed:
            emit idenResult(-1, EnrRecRightFailed);
            break;
        case EnrRecBothFailed:
            emit idenResult(-1, EnrRecBothFailed);
            break;
        default:
            emit idenResult(-1, EnrRecUnknown);
            break;
        }
    }
    else if(idenRet == E_USBSDK_OK) {
        qDebug() << "E_USBSDK_OK";
        switch (resultFlag) {
        case EnrRecLeftSuccess:
            emit idenResult(matchOutputL.MatchIndex[0], EnrRecLeftSuccess);
            break;
        case EnrRecRightSuccess:
            emit idenResult(matchOutputR.MatchIndex[0], EnrRecRightSuccess);
            break;
        case EnrRecBothSuccess:
            emit idenResult(matchOutputL.MatchIndex[0], EnrRecLeftSuccess);
        default:
            break;
        }
    }
    else {
        printf("idenRet: %d\n", idenRet);
        emit idenResult(-4, EnrRecUnknown);
    }

    m_isStop = true;
    qDebug() << "out" << QTime::currentTime().toString("hh:mm:ss:zzz");
}


