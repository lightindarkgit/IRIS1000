#include "ptzbase.h"
#include "pwm.h"

ptzBase* ptzBase::m_instance = nullptr;
PWMParam ptzBase::m_pwmParam;

ptzBase::ptzBase(QObject *parent) :
    QObject(parent),
    m_init(false)
{
    int ret = steeringInit();

    if (ret==E_PWM_SUCCESS)
    {
        m_init = true;
    }

}

ptzBase::~ptzBase()
{
    pwmUninit();
}

/*********************************
功   能：单例模式
作   者：yqhe
日   期：20180224
修改 人：
修改内容：
修改日期：
参   数：
     1.
**********************************/
ptzBase* ptzBase::get_Instance()
{
    if (nullptr == m_instance)
    {
        m_instance = new ptzBase();
    }

    return m_instance;
}

/*********************************
功   能：设置参数，如最大、最小角度等
作   者：yqhe
日   期：20180224
修改 人：
修改内容：
修改日期：
参   数：
     1.pwmParam --  舵机运动控制参数
返回值：
    E_PWM_SUCCESS(0) -- 成功
    E_PWM_PARAM_ERROR -- 设置的参数有错误
**********************************/
int ptzBase::initARG(const PWMParam& param)
 {
    // 测试param中的数值是否有效

    // 不能小于最小
    if (param.m_minAngle<PWM_MIN_ANGLE)
    {
        return E_PWM_PARAM_ERROR;
    }

    // 不能大于最大
    if (param.m_maxAngle>PWM_MAX_ANGLE)
    {
        return E_PWM_PARAM_ERROR;
    }

    // 归位角度要在有效角度区间
    if ((param.m_homeAngle>param.m_maxAngle)
        ||(param.m_homeAngle<param.m_minAngle))
    {
        return E_PWM_PARAM_ERROR;
    }

    // 步进角度不能过小
    if (param.m_stepAngle<PWM_MIN_STEP)
    {
        return E_PWM_PARAM_ERROR;
    }

    // 延迟等待时间不能过小
    if (param.m_msDelay<PWM_MIN_DELAY)
    {
        return E_PWM_PARAM_ERROR;
    }

    memcpy(&m_pwmParam, &param, sizeof(PWMParam));

    // 设置参数
    pwmSetParam(m_pwmParam);

    return E_PWM_SUCCESS;
 }

/*********************************
功   能：初始化舵机、转动到初始位置等
作   者：yqhe
日   期：20180224
修改 人：
修改内容：
修改日期：
参   数：
     1.
返回值：
    E_PWM_SUCCESS(0) -- 成功
**********************************/
int ptzBase::steeringInit()
{
    pwmUninit();

    // 初始化舵机
    int ret = pwmInit();
    if (ret!=E_PWM_SUCCESS)
    {
        return ret;
    }

    // 转动到初始位置
    ret = pwmInitAngle();

    return ret;
}

/*********************************
功   能：设置舵机角度
作   者：yqhe
日   期：20180224
修改 人：
修改内容：
修改日期：
参   数：
     1.angle -- 转动目标角度
     2.homing -- 是否归位，如果归位，则angle参数无效
                         缺省值为false
返回值：
    E_PWM_SUCCESS(0) -- 成功
**********************************/
#include <QDebug>
int ptzBase::setSteeringAngle(float angle, bool homing)
{
    int ret = E_PWM_SUCCESS;

    if (!m_init)
    {
        return E_PWM_UNINIT_ERROR;
    }

    if (homing)
    {
        ret = pwmInitAngle();
    }
    else
    {
        ret = pwmMoveToDestAngle(angle);
    }

    return ret;
}


/*********************************
功   能：设置舵机偏移角度，为了与之前的舵机运动控制函数保持一致
作   者：yqhe
日   期：20180224
修改 人：
修改内容：
修改日期：
参   数：
     1.offsetAngle -- 转动目标角度与当前角度的偏移值
     2.id -- 为了与之前的舵机运动控制函数保持一致，使用缺省值0即可
返回值：
    E_PWM_SUCCESS(0) -- 成功
**********************************/
int ptzBase::setSteeringFrame(float offsetAngle, int id)
{
    if (id!=0)
    {
        return E_PWM_PARAM_ERROR;
    }

    float curAngle = pwmGetCurAngle();
    float setAngle = curAngle + offsetAngle;
    bool homing = false;

    if (offsetAngle < -900.0f)
    {
        homing = true;
    }

    qDebug() << "set angle = " << setAngle << ", curAngle = " << curAngle;
    int ret = setSteeringAngle(setAngle, homing);

    return ret;
}

/*********************************
功   能：获取舵机当前角度，调试时检查当前舵机角度，平时可以不用
作   者：yqhe
日   期：20180226
修改 人：
修改内容：
修改日期：
参   数：
     1.
返回值：
    舵机当前角度
**********************************/
float ptzBase::getSteeringAngle()
{
    float angle = pwmGetCurAngle();

    return angle;
}

