#ifndef PTZBASE_H
#define PTZBASE_H

#include <QObject>
#include "pwmdata.h"

class ptzBase : public QObject
{
    Q_OBJECT
private:
    explicit ptzBase(QObject *parent=0);
    ~ptzBase();

public:
    static ptzBase* get_Instance();
    static int initARG(const PWMParam& pwmParam);

// signals:

public slots:
    int setSteeringAngle(float angle, bool homing=false);    // 设置舵机角度，homing=true时，舵机归位
    int setSteeringFrame(float offsetAngle, int id=0);           // 设置舵机偏移角度，为了与之前的舵机运动控制函数保持一致
                                                                                              // id=0，为了与之前的舵机运动控制函数保持一致，使用时直接使用缺省值即可

    float getSteeringAngle(); // 获取舵机当前角度

private:
    int steeringInit(); // 初始化舵机配置，转动到初始位置等

private:
    static ptzBase* m_instance;
    static PWMParam m_pwmParam;
    bool m_init;

};

#endif // PTZBASE_H
