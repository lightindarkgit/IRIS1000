#pragma once
#ifndef LDMARKMODEL_H_
#define LDMARKMODEL_H_

#  ifdef Q_OS_WIN
#    define Q_DECL_EXPORT     __declspec(dllexport)
#    define Q_DECL_IMPORT     __declspec(dllimport)
#  else
#    define Q_DECL_EXPORT     __attribute__((visibility("default")))
#    define Q_DECL_IMPORT     __attribute__((visibility("default")))
#    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  endif

#if defined(SDM_ALIGN_LIBRARY)
#  define SDM_ALIGNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SDM_ALIGNSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <iostream>
#include <vector>
#include <fstream>
#define LandmarkPointsNum  68
#define SDM_NO_ERROR        0       //无错误
//#define SDM_ERROR_FACEDET   200     //重新通过CascadeClassifier检测到人脸
//#define SDM_ERROR_FACEPOS   201     //人脸位置变化较大，可疑
//#define SDM_ERROR_FACESIZE  202     //人脸大小变化较大，可疑
//#define SDM_ERROR_FACENO    203     //找不到人脸
#define SDM_ERROR_IMAGE     204     //图像错误

//#define SDM_ERROR_ARGS      400     //参数传递错误
//#define SDM_ERROR_MODEL     401     //模型加载错误

struct HoGParam;
struct IK_Rect;

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
    IK_Rect& operator =(const IK_Rect& str)//赋值运算符
        {
            m_x = str.m_x;
            m_y = str.m_y;
            m_width = str.m_width;
            m_height = str.m_height;
            return *this;
        }
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};



class SDM_ALIGNSHARED_EXPORT ldmarkmodel{

public:
    ldmarkmodel();
    ~ldmarkmodel();

      void predict(unsigned char* grayImage, int width, int height, IK_Rect crop);

      int track(unsigned char* srcData, int width, int height,  float* current_shape, int current_shapeNum, IK_Rect face_Rect);

      void  EstimateHeadPose(float* current_shape, int current_shapeNum, float* eav, int eavNum);

      IK_Rect enclosing_bbox(float* current_shape, int current_shapeNum);
private:
    IK_Rect faceBox;
    //cv::Mat meanShape;
    float* meanShape;
    bool isNormal;
};

#endif


