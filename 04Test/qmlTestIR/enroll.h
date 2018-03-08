#ifndef ENROLL_H
#define ENROLL_H

#include <QObject>
#include "IKUSBSDK.h"

#define g_constMaxEnrollImNum   3
class enroll : public QObject
{
    Q_OBJECT
public:
    explicit enroll(QObject *parent = 0);
    int startEnroll();       // 启动注册
    int stopEnroll();       // 停止注册

signals:
    void enrollState(int state);  //0成功，1失败，2终止，3结束
    void beginEnroll();
    void enrollResult();    ///注册结果信号，参数待定

public slots:
    void doEnroll();  //进行注册的槽函数

private:
    bool g_isEnrollThreadEnd;
    bool s_isEnrollStoped;           //注册是否停止

    IKSDKIrisInfo enrIrisL[g_constMaxEnrollImNum];
    IKSDKIrisInfo enrIrisR[g_constMaxEnrollImNum];

    IKIrisMode     _irisMode;//识别或注册时眼睛模式

    IKSDKIrisInfo   *s_enrIrisL;
    IKSDKIrisInfo   *s_enrIrisR;
    IKResultFlag     s_enrLrFlag;   //注册结果标志
    int     _numEnrL;                       //左眼注册图像个数
    int     _numEnrR;                       //右眼注册图像个数
    int    s_leftEnrNum;
    int    s_rightEnrNum;
};

#endif // ENROLL_H
