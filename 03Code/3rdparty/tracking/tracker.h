/*
 * File:   BasicTracker.h
 * Author: Joao F. Henriques, Joao Faro, Christian Bailer
 * Contact address: henriques@isr.uc.pt, joaopfaro@gmail.com, Christian.Bailer@dfki.de
 * Instute of Systems and Robotics- University of COimbra / Department Augmented Vision DFKI
 *
 * This source code is provided for for research purposes only. For a commercial license or a different use case please contact us.
 * You are not allowed to publish the unmodified sourcecode on your own e.g. on your webpage. Please refer to the official download page instead.
 * If you want to publish a modified/extended version e.g. because you wrote a publication with a modified version of the sourcecode you need our
 * permission (Please contact us for the permission).
 *
 * We reserve the right to change the license of this sourcecode anytime to BSD, GPL or LGPL.
 * By using the sourcecode you agree to possible restrictions and requirements of these three license models so that the license can be changed
 * anytime without you knowledge.
 */

#pragma once
#  ifdef Q_OS_WIN
#    define Q_DECL_EXPORT     __declspec(dllexport)
#    define Q_DECL_IMPORT     __declspec(dllimport)
#  else
#    define Q_DECL_EXPORT     __attribute__((visibility("default")))
#    define Q_DECL_IMPORT     __attribute__((visibility("default")))
#    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif


#if defined(KCF_ALIGN_LIBRARY)
#  define KCF_ALIGNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KCF_ALIGNSHARED_EXPORT Q_DECL_IMPORT
#endif
#include <string>
#define FACE_INFO_LEN 158
#define LANDMARKNUM 6
struct IK_Rect{
    IK_Rect()
    {
        m_x = 0;
        m_y = 0;
        m_width = 0;
        m_height = 0;
    }
    IK_Rect(int x, int y, int width, int height)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }
    IK_Rect& operator =(const IK_Rect& other)//赋值运算符
        {
            m_x = other.m_x;
            m_y = other.m_y;
            m_width = other.m_width;
            m_height = other.m_height;
            return *this;
        }
    bool operator ==(const IK_Rect& other)//赋值运算符
        {
            return (this->m_x==other.m_x && this->m_y == other.m_y && this->m_width==other.m_width && this->m_height==other.m_height);
        }
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};
//输出的结构体数据
struct pointData{
    bool flag; //0无1有
    float browCX; //眉心x
    float browCY; //眉心Y
    float pupilLX; //左瞳孔X
    float pupilLY; //左瞳孔Y
    float pupilRX; //右瞳孔X
    float pupilRY; //右瞳孔Y
    float cropX;   //cropX
    float cropY;   //cropY
    float cropW;   //crop宽
    float cropH;   //crop高
    float pitch;   //倾斜
    float yaw;     //旋转
    float roll;    //俯仰
    float track_cropX;  //track的X
    float track_cropY;   //Track 的Y
    float track_cropWidth;  //track 的宽
    float track_cropHeight; //track 的高
    float detect_cropX;     //检测的X
    float detect_cropY;     //检测的Y
    float detect_cropWidth;  //检测的宽
    float detect_cropHeight;  //检测的高
    float landmarks[LANDMARKNUM*2];//68个关键点136个值
};

///检测+跟踪
//KCF_ALIGNSHARED_EXPORT  int detectTracking(unsigned char* srcImg, int rows, int cols, int channel, IK_Rect& crop, float* data, int dataNum);
KCF_ALIGNSHARED_EXPORT  int detectTracking(unsigned char* srcImg, int rows, int cols, int channel, IK_Rect& crop, pointData& data);


