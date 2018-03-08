#ifndef PUBLICDATA_H
#define PUBLICDATA_H
#  ifdef Q_OS_WIN
#include <Windows.h>
class timeElapsed
{
private:
    LARGE_INTEGER litmp;                           //精确计算时差
    long long Qpart1,Qpart2,Useingtime;
    double dfMinus,dfFreq,dfTime;
    long count;
    long addTime;
public:
    timeElapsed();
    /*********************************
    功   能：开始计时

    作   者：zhangyp
    日   期：20170605
    修改 人：
    修改内容：
    修改日期：
    参   数：
         1.
    返回 值：
    **********************************/
    void startTime();
    /*********************************
    功   能：停止计时并返回时差

    作   者：zhangyp
    日   期：20170605
    修改 人：
    修改内容：
    修改日期：
    参   数：
         1.
    返回 值：时差值
    **********************************/
    long stopTime();

    /*********************************
    功   能：停止计时并返回时差

    作   者：zhangyp
    日   期：20170605
    修改 人：
    修改内容：
    修改日期：
    参   数：
         1.
    返回 值：时差值
    **********************************/
    long avgTime();

    /*********************************
    功   能：运行次数

    作   者：zhangyp
    日   期：20170605
    修改 人：
    修改内容：
    修改日期：
    参   数：
         1.
    返回 值：时差值
    **********************************/
    long getCount(){return count;}
};
//class publicData
//{
//public:
//    /*********************************
//    功   能：开始计时

//    作   者：zhangyp
//    日   期：20170605
//    修改 人：
//    修改内容：
//    修改日期：
//    参   数：
//         1.
//    返回 值：
//    **********************************/
//    static void startTime();


//    /*********************************
//    功   能：停止计时并返回时差

//    作   者：zhangyp
//    日   期：20170605
//    修改 人：
//    修改内容：
//    修改日期：
//    参   数：
//         1.
//    返回 值：时差值
//    **********************************/
//    static long stopTime();
//};

#endif // PUBLICDATA_H

#endif
