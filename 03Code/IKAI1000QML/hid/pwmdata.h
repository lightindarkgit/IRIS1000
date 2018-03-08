#ifndef PWMDATA_H
#define PWMDATA_H

const int E_PWM_SUCCESS = 0;
const int E_PWM_ERROR_BASE = 0- 0x2000;
const int E_PWM_EXPORT_ERROR = E_PWM_ERROR_BASE - 1;
const int E_PWM_UNEXPORT_ERROR = E_PWM_ERROR_BASE - 2;
const int E_PWM_ENABLE_ERROR = E_PWM_ERROR_BASE - 3;
const int E_PWM_DISABLE_ERROR = E_PWM_ERROR_BASE - 4;
const int E_PWM_PERIOD_ERROR = E_PWM_ERROR_BASE - 5;
const int E_PWM_DUTYCYCLE_ERROR = E_PWM_ERROR_BASE - 6;

const int E_PWM_WRITE_ERROR = E_PWM_ERROR_BASE - 7;
const int E_PWM_PARAM_ERROR = E_PWM_ERROR_BASE - 8;
const int E_PWM_UNINIT_ERROR = E_PWM_ERROR_BASE - 9;

const int PWM_MIN_ANGLE = 55;
const int PWM_MAX_ANGLE = 110;
const int PWM_MIN_STEP = 5;
const int PWM_MIN_DELAY=50;

typedef struct __PWMParam
{
    int m_minAngle;     // 最小转动角度
    int m_maxAngle;     // 最大转动角度

    int m_homeAngle;    // 初始化角度（归位）
    int m_stepAngle;    // 步进角度
    int m_msDelay;      // 每次角度设置完成后的等待时间，单位：毫秒

    __PWMParam()
    {
        m_minAngle = PWM_MIN_ANGLE;
        m_maxAngle = PWM_MAX_ANGLE;

        m_homeAngle = 90;
        m_stepAngle = PWM_MIN_STEP;
        m_msDelay = 100;
    }

}PWMParam, *PPWMParam;

#endif // PWMDATA_H
