/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-02-09
描述: 注册线程
**************************************************/
#ifndef THREADENROLL_H
#define THREADENROLL_H

#include <QObject>
#include "IKUSBSDK.h"

#define g_constMaxEnrollImNum   3
class ThreadEnroll : public QObject
{
    Q_OBJECT
public:
    explicit ThreadEnroll(QObject *parent = 0);  //构造函数
    void initARG(IKIrisMode mode);
    int startEnroll();       // 启动注册
    int stopEnroll();       // 停止注册

signals:
    void enrollState(int state);  //0成功，1失败，2终止，3结束
    void beginEnroll();  //开始注册的信号
//注册结果信号
    void enrollResult(IKSDKIrisInfo* enrIrisL, int numEnrL, IKSDKIrisInfo* enrIrisR, int numEnrR, IKResultFlag IKflag);

public slots:
    void doEnroll();  //进行注册的槽函数

private:
    bool   m_isEnrollThreadEnd;    //注册线程结束标志
    bool   m_isEnrollStoped;           //注册是否停止

    IKSDKIrisInfo enrIrisL[g_constMaxEnrollImNum];   //注册时开辟的左眼虹膜数据空间
    IKSDKIrisInfo enrIrisR[g_constMaxEnrollImNum];   //注册时开辟的右眼虹膜数据空间

    IKIrisMode     m_irisMode;//识别或注册时眼睛模式

    IKSDKIrisInfo   *m_enrIrisL;   //注册成功后保存的左眼虹膜数据
    IKSDKIrisInfo   *m_enrIrisR;   //注册成功后保存的右眼虹膜数据
    IKResultFlag     m_enrLrFlag;   //注册结果标志
    int     m_leftEnrNum;          //左眼实际注册图像个数
    int     m_rightEnrNum;       //右眼实际注册图像个数
};

#endif // THREADENROLL_H
