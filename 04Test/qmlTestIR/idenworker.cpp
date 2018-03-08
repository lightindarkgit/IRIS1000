#include "idenworker.h"
#include <QDebug>
#include <QTime>

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
idenWorker::idenWorker(QObject *parent) : QObject(parent)
{
    isStop = true;
    connect(this, SIGNAL(startWorker()), this, SLOT(workProcess()));
}

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
void idenWorker::initARG(unsigned char *codeListL, unsigned char *codeListR, int codeNumL, int codeNumR)
{
    idenCodeListL = codeListL;
    idenCodeListR = codeListR;
    idenCodeNumL = codeNumL;
    idenCodeNumR = codeNumR;
}

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
bool idenWorker::getIdenState()
{
    return isStop;
}

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
int idenWorker::startIden()
{
    emit startWorker();
    return 1;
}

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
int idenWorker::stopIden()
{
    return IKUSBSDK_StopIden();
}

/*********************************
功   能：
作   者：
日   期：
修改 人：
修改内容：
修改日期：
参   数：
返回 值：
**********************************/
void idenWorker::workProcess()
{
    qDebug() << "in";
    qDebug() << QTime::currentTime().toString("hh:mm:ss:zzz");
    isStop = false;

    IKSDKIrisInfo *ptr = (IKSDKIrisInfo*)idenCodeListL;

    IKResultFlag resultFlag;
    IKAlgConfigStruct algConfig;
    IKSDKMatchOutput matchOutputL, matchOutputR;
    IKIrisMode irisMode = IrisModeUndef;

    algConfig.minEnrIdenTime = IK_MIN_REC_TIME;
    algConfig.maxEnrIdenTime = IK_MAX_REC_TIME;
    algConfig.reservedPara[IK_RESERVEDPARA_BLINK] = 0;
    algConfig.reservedPara[IK_RESERVEDPARA_I2FMODE] = I2FModeIris;

    int idenRet = IKUSBSDK_StartIrisIden(irisMode, idenCodeListL, idenCodeNumL, &matchOutputL,
                                         idenCodeListR, idenCodeNumR, &matchOutputR, resultFlag, &algConfig);

    if(idenRet == E_USBSDK_ENR_IDEN_INTERRUPT) {
        emit idenResult(-2, EnrRecUnknown);
    }
    else if(idenRet == E_USBSDK_IDEN_OVERTIME) {
        emit idenResult(-3, EnrRecUnknown);
    }
    else if(idenRet == E_USBSDK_ENR_IDEN_FAILED) {
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
        emit idenResult(-4, EnrRecUnknown);
    }

    isStop = true;
    qDebug() << "out";
    qDebug() << QTime::currentTime().toString("hh:mm:ss:zzz");
}


