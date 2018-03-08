/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-14
描述: 人脸检测类，要放到子线程里运行
**************************************************/
#ifndef FACETRACK_H
#define FACETRACK_H

#include <QObject>
#include <QImage>
#include "tracker.h"
#include "ikAlgoFaceDetection.h"
class FaceTrack : public QObject
{
    Q_OBJECT
public:
    explicit FaceTrack(QObject *parent = 0);   //构造函数
    void setCheckFlag(bool flag);    ///true  可以检测，false，不可以检测

signals:
//    void result(pointData);   // 信号，发送检测到的结果

public slots:
    void dealFace(QImage img);  //检测人脸图像的槽函数

private:
    bool  m_checkFlag;/// /true  可以检测，false，不可以检测
    pointData           m_Info;     //人脸检测用
    IK_Rect               m_lastFaceRect;        //最近一次人脸位置

    QPointF             m_ptCenter;
    int                     m_heartBeat;

    float                 m_remainDecimal;  //  计算出来的角度，剩余的小数部分

private:
    void controlSteering(const pointData& info, float curAngle);
    void steeringPTZ(float faceCenterY, bool homing, float curAngle);
};

#endif // FACETRACK_H
