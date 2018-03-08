﻿//1：PWM周期 T=20ms；
//2：PWM电压为3.3V；
//3：0°对应PWM占空比为0.5/20 ms(即高电玉0.5ms，低电平19.5ms)，180°时占空比为 2.5/20ms；
//3：舵机转动角为0°～180°，PWM控制精度为1°，即PWM占空比中的高电平（0.5ms～2.5ms）支持细分180等份。
//4：实测数据参考：0°对应0.5/20 ms、52°对应1.05/20 ms、90°对应1.5/20 ms、106°对应1.65/20 ms、180°对应2.5/20 ms。
//5 : added at 20180302 by yqhe，经测试，PWM控制精度至少可以到0.3°

// modified at 20180210 by yqhe
// 一个简单的舵机测试程序，用于测试AI1000设备上的舵机
// 在硬件张勇给出来的测试程序上修改
// 运行后，初始化舵机到一个固定角度74，成功后
// 输入+并回车，增加舵机角度；输入-并回车，减小舵机角度
// 输入q退出

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <QDebug>
#include "pwm.h"

#define pwm_export        "/sys/class/pwm/pwmchip1/export"
#define pwm_enable        "/sys/class/pwm/pwmchip1/pwm0/enable"
#define pwm_period        "/sys/class/pwm/pwmchip1/pwm0/period"
#define pwm_duty_cycle   "/sys/class/pwm/pwmchip1/pwm0/duty_cycle"

const unsigned int PWM_BASE_VALUE = 500000;
const unsigned int PWM_DIV_VALUE = 2000000;
const unsigned int PWM_SUBDIVISION_VALUE = 180;
const char PWM_PERIOD_VALUE[] = "20000000";

//  设置舵机的角度
//  输入参数：
//  angle --  设置的角度，不是相对值
// delay -- 设置完成后，等待多少毫秒，缺省为等待100毫秒
int pwmSetAngle(float angle, int delay=150);

// 输出错误的统一格式
void dumpError(QString title, QString msg, float err)
{
    qDebug() << "[" << title << "] : " << msg << " [ err:" << err << "]";
}

// 等待时间，控制舵机运行一个角度后，都需要暂停一小段时间，100ms左右
// 输入参数：
// ms -- 毫秒值
// seconds -- 秒值，缺省为0
void pwmDelay(unsigned int ms, unsigned int seconds=0);

void pwmDelay(unsigned int ms, unsigned int seconds )
{  
    struct timeval delay; 

    delay.tv_sec = seconds;
    delay.tv_usec = ms * 1000;
    select(0, NULL, NULL, NULL, &delay);

}

// 初始化pwm时，先export，再enable
int pwmExport()
{
    int fd = open(pwm_export, O_WRONLY);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_EXPORT_ERROR);
        return E_PWM_EXPORT_ERROR;
    }

    write(fd, "0", 2);
    close(fd);

    return E_PWM_SUCCESS;
}

// 退出pwm时，先disable，再unexport
int pwmUnexport()
{
    int fd = open(pwm_export, O_WRONLY);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_UNEXPORT_ERROR);
        return E_PWM_UNEXPORT_ERROR;
    }

    write(fd, "1", 2);
    close(fd);

    return E_PWM_SUCCESS;
}

// 初始化pwm时，先export，再enable
int pwmEnable()
{
    int fd = open(pwm_enable, O_WRONLY);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_ENABLE_ERROR);
        return E_PWM_ENABLE_ERROR;
    }

    write(fd, "1", 2);
    close(fd);

    return E_PWM_SUCCESS;
}

// 退出pwm时，先disable，再unexport
int pwmDisable()
{
    int fd = open(pwm_enable, O_WRONLY);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_DISABLE_ERROR);
        return E_PWM_DISABLE_ERROR;
    }

    write(fd, "0", 2);
    close(fd);

    return E_PWM_SUCCESS;
}


// 初始化pwm时，先export，再enable
int pwmInit()
{
    int nret = E_PWM_SUCCESS;

    // export first
    nret = pwmExport();
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    // then, enable
    nret = pwmEnable();
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    return nret;

}

// 退出pwm时，先disable，再unexport
int pwmUninit()
{
    int nret = E_PWM_SUCCESS;

    // 退出程序时，设置角度为90度
    pwmSetAngle(90.0f);

    // disable first
    nret = pwmDisable();
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    // then, unexport
    nret = pwmUnexport();
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    return nret;
}

// 设置周期，单位是ns
// 先设置周期，再设置duty(pwmDutyCycle)
// duty指的是在一个周期内低电平持续的时间
// duty必须小于等于period
int pwmPeriod()
{
    int nret = E_PWM_SUCCESS;

    int fd = open(pwm_period, O_RDWR);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_PERIOD_ERROR);
        return E_PWM_PERIOD_ERROR;
    }

    int writelen = write(fd, PWM_PERIOD_VALUE, strlen(PWM_PERIOD_VALUE));
    close(fd);

    if (writelen!=strlen(PWM_PERIOD_VALUE))
    {
        dumpError(__FUNCTION__, "write failed", E_PWM_WRITE_ERROR);
        return E_PWM_WRITE_ERROR;
    }

    return nret;
}

// 设置周期为0，避免总是通电
int pwmZeroPeriod()
{
    int nret = E_PWM_SUCCESS;

    int fd = open(pwm_period, O_RDWR);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_PERIOD_ERROR);
        return E_PWM_PERIOD_ERROR;
    }

    write(fd, "0", 2);
    close(fd);

    return nret;
}

// 设置duty
// duty指的是在一个周期内低电平持续的时间
// duty必须小于等于period
int pwmDutyCycle(float angle)
{
    int nret = E_PWM_SUCCESS;

    int fd = open(pwm_duty_cycle,O_RDWR);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_DUTYCYCLE_ERROR);
        return E_PWM_DUTYCYCLE_ERROR;
    }

    unsigned int pwmdutycycle;
    char writestr[100];
    pwmdutycycle = (unsigned int)(PWM_BASE_VALUE + (PWM_DIV_VALUE/PWM_SUBDIVISION_VALUE)*angle);
    // 注意：这里一定是十进制的
    sprintf(writestr,"%d", pwmdutycycle);

    unsigned int writelen =  write(fd, writestr, strlen(writestr));
    close(fd);

    qDebug() << "pwmDutyCycle : " << writestr << "##############################";

    if (writelen!=strlen(writestr))
    {
        dumpError(__FUNCTION__, "write failed", angle);
        return E_PWM_WRITE_ERROR;
    }

    return nret;
}

static PWMParam pwmParam;
static float m_curAngle = 70.0f;


// 规范舵机运动角度到一个合理的值
// 受最大值和最小值控制
// 输入参数：
// angle -- 希望设置的角度
// 返回值：
//  整合后的，规范的角度
float pwmConformAngle(float angle)
{
    float settingAngle;
    settingAngle = angle;

   if (angle<pwmParam.m_minAngle)
   {
       settingAngle = pwmParam.m_minAngle;
   }

   if (angle>pwmParam.m_maxAngle)
   {
       settingAngle = pwmParam.m_maxAngle;
   }

   return settingAngle;
}

int pwmSetAngle(float angle, int delay)
{
    int nret = E_PWM_SUCCESS;

    nret = pwmPeriod();
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    // 确保设置的角度在安全范围内
    float settingAngle = pwmConformAngle(angle);

    nret = pwmDutyCycle(settingAngle);
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    pwmDelay(delay);

    return nret;
}

// 控制舵机运动到指定角度，这是最终角度，有对角度的检查
// 输入参数：
// angle -- 目标角度
int pwmMoveToDestAngle(float angle)
{
    int nret = E_PWM_SUCCESS;

    if (angle==m_curAngle)
    {
        return nret;
    }

    // int localAngle = m_curAngle;

    // dumpError(__FUNCTION__, "dest angle" , angle);

    // 规范设置的角度，不能过大，不能过小
    float settingAngle = pwmConformAngle(angle);

    float step = pwmParam.m_stepAngle;
    int delay = pwmParam.m_msDelay;

   bool downward =m_curAngle>settingAngle ? true : false;
   if (downward)
   {
       // modified at 20180301 by yqhe
       // 当从大往小调节时，调节到比需要的小1度，最后再向上加1度
       settingAngle--;
   }

   float delta = step;
   int movecount =  (settingAngle-m_curAngle)/delta;

   // 开始步进调整角度，直至最终设置值
    while (movecount>0)
    {
        movecount--;
        m_curAngle += delta;
        nret = pwmSetAngle(m_curAngle, delay);
        if (nret!=E_PWM_SUCCESS)
        {
            m_curAngle -= delta;
            return nret;
        }

        dumpError(__FUNCTION__, "local angle" , m_curAngle);
    }

    // 最后将角度调整到目标角度
    // 前面的步进，是接近目标角度，不一定是目标角度
    if (m_curAngle!=settingAngle)
    {
        nret = pwmSetAngle(settingAngle, delay);
        if (nret!=E_PWM_SUCCESS)
        {
            return nret;
        }

        m_curAngle = settingAngle;
        // dumpError(__FUNCTION__, "current angle-success" , m_curAngle);
    }

    // 从大往小调节时，目标角度比实际的小1度，最后调回去
    // 在实际使用中，这样可以尽量避免舵机啸叫（虽然不能完全避免）
    if (downward)
    {
        settingAngle++;
        nret = pwmSetAngle(settingAngle, delay);
        if (nret!=E_PWM_SUCCESS)
        {
            return nret;
        }

        m_curAngle = settingAngle;
    }

    // 最终完成，再多等待100毫秒
    pwmDelay(pwmParam.m_msDelay);

    // 利刚说加上这个，可以使得舵机不运动的时候不过电流
    // 但实际测试发现，会导致舵机不正常运动，跑到最下面
//    pwmZeroDutyCycle();

   return nret;
}

// 设置舵机的初始化角度
// 不知道舵机当前角度的情况下设置初始角度
// 输入参数：无
int pwmInitAngle()
{
    int nret = E_PWM_SUCCESS;

    int angle = pwmParam.m_homeAngle;

    // 如果角度未变，不做舵机运动
    if (m_curAngle==angle)
    {
        return nret;
    }

    int m_curAngle = pwmConformAngle(angle);

    //  初始化舵机，等待时间稍长一点
    nret = pwmSetAngle(m_curAngle-1, 500);
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    nret = pwmSetAngle(m_curAngle, 500);
    if (nret!=E_PWM_SUCCESS)
    {
        return nret;
    }

    qDebug() << "homing angle " << m_curAngle;

    return nret;
}

// 设置舵机参数
void pwmSetParam(const PWMParam& param)
{
    memcpy(&pwmParam, &param, sizeof(PWMParam));
}

// 获取舵机当前参数
void pwmGetParam(PWMParam& param)
{
    memcpy(&param, &pwmParam, sizeof(PWMParam));
}

// 获取当前角度
float pwmGetCurAngle()
{
//    return m_curAngle;

    int fd = open(pwm_duty_cycle,O_RDONLY);
    if (fd<0)
    {
        dumpError(__FUNCTION__, "open failed", E_PWM_DUTYCYCLE_ERROR);
        return E_PWM_DUTYCYCLE_ERROR;
    }

    unsigned int pwmdutycycle;
    char readstr[8];
    memset(readstr, 0, 8);
//    pwmdutycycle = (unsigned int)(PWM_BASE_VALUE + (PWM_DIV_VALUE/PWM_SUBDIVISION_VALUE)*angle);
//    // 注意：这里一定是十进制的
//    sprintf(writestr,"%d", pwmdutycycle);

    unsigned int readlen =  read(fd, readstr, 8);
    close(fd);

    qDebug() << "pwmGetCurAngle read : " << readstr << "++++++++++++++++++";

    if (readlen<=0)
    {
        dumpError(__FUNCTION__, "read failed", 888);
        return E_PWM_WRITE_ERROR;
    }

    pwmdutycycle = atol(readstr);
    float angle = (pwmdutycycle*1.0f-PWM_BASE_VALUE)/(PWM_DIV_VALUE/PWM_SUBDIVISION_VALUE);
    qDebug() << "pwmGetCurAngle  get : " << angle << "++++++++++++++++++";


    return angle;

}
