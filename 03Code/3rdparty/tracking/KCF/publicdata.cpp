#include "publicdata.h"
#include <time.h>
#  ifdef Q_OS_WIN
#include <Windows.h>
//static LARGE_INTEGER litmp;                           //精确计算时差
//static LONGLONG Qpart1,Qpart2,Useingtime;
//static double dfMinus,dfFreq,dfTime;

timeElapsed::timeElapsed()
{
    count = 1;
    addTime = 0;
}
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
void timeElapsed::startTime()
{
#ifdef Q_OS_WIN
    //获得CPU计时器的时钟频率
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;
    count++;
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart1 = litmp.QuadPart; //开始计时
#elif defined Q_OS_UNIX
    gettimeofday( &start, NULL );
#endif
}

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
long timeElapsed::stopTime()
{
#ifdef Q_OS_WIN
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart2 = litmp.QuadPart; //终止计时
    dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
    dfTime = dfMinus / dfFreq;//获得对应时间。单位为秒,可以乘精确到微秒级（us）
    Useingtime = dfTime*1000000;
    return Useingtime;
#elif defined Q_OS_UNIX
    gettimeofday( &end, NULL );
    return end.tv_usec - start.tv_usec;
#endif
}

/*********************************
功   能：平均时间

作   者：zhangyp
日   期：20170918
修改 人：
修改内容：
修改日期：
参   数：
     1.
返回 值：时差值
**********************************/
long timeElapsed::avgTime()
{
    addTime+=stopTime();
    return addTime/count;
}
///*********************************
//功   能：开始计时

//作   者：zhangyp
//日   期：20170605
//修改 人：
//修改内容：
//修改日期：
//参   数：
//     1.
//返回 值：
//**********************************/
//void publicData::startTime()
//{
//#ifdef Q_OS_WIN
//    //获得CPU计时器的时钟频率
//    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
//    dfFreq = (double)litmp.QuadPart;

//    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
//    Qpart1 = litmp.QuadPart; //开始计时
//#elif defined Q_OS_UNIX
//    gettimeofday( &start, NULL );
//#endif
//}


///*********************************
//功   能：停止计时并返回时差

//作   者：zhangyp
//日   期：20170605
//修改 人：
//修改内容：
//修改日期：
//参   数：
//     1.
//返回 值：时差值
//**********************************/
//long publicData::stopTime()
//{
//#ifdef Q_OS_WIN
//    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
//    Qpart2 = litmp.QuadPart; //终止计时
//    dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
//    dfTime = dfMinus / dfFreq;//获得对应时间。单位为秒,可以乘精确到微秒级（us）
//    Useingtime = dfTime*1000000;
//    return Useingtime;
//#elif defined Q_OS_UNIX
//    gettimeofday( &end, NULL );
//    return end.tv_usec - start.tv_usec;
//#endif
//}

#endif
