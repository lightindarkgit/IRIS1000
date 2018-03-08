#ifndef PWM_H_
#define PWM_H_

#include "pwmdata.h"

// 舵机初始化
int pwmInit();

// 退出
int pwmUninit();

// 设置舵机的初始化角度
// 不知道舵机当前角度的情况下设置初始角度
// 输入参数：无
// 初始角度值在总的参数结构PWMParam中已设置
int pwmInitAngle();

// 设置舵机参数
void pwmSetParam(const PWMParam& param);

// 获取舵机当前参数
void pwmGetParam(PWMParam& param);

// 获取当前角度
int pwmGetCurAngle();

// 控制舵机运动到指定角度，这是最终角度，有对角度的检查
// 输入参数：
// angle -- 目标角度
int pwmMoveToDestAngle(int angle);


#endif
