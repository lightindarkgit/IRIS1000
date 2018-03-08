/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2017-12-14
描述: 人脸检测类，要放到子线程里运行
**************************************************/
#include "facetrack.h"
#include <QDebug>
#include "Exectime.h"
#include "ptzbase.h"
/*********************************
功   能：人脸检测构造函数
作   者：lhc
日   期：2017-12-14
修改 人：
修改内容：
修改日期：
参   数：QObject *parent
返回 值：
**********************************/
FaceTrack::FaceTrack(QObject *parent) :
    QObject(parent),
    m_heartBeat(0),
    m_remainDecimal(0.0f)
{
    qRegisterMetaType<pointData>("pointData");

    // 在5#设备上，325是个比较合适的位置值
    m_ptCenter = QPoint(300, 325);
    m_checkFlag = false;
}

void FaceTrack::setCheckFlag(bool flag)
{
    m_checkFlag = flag;
}

/*********************************
功   能：检测人脸图像的槽函数
作   者：lhc
日   期：2017-12-14
修改 人：
修改内容：
修改日期：
参   数：Qimage img，传入图像
返回 值：
**********************************/
//#include <pthread.h>
//pthread_mutex_t dealmutex;

void FaceTrack::dealFace(QImage img)
{
//    if (pthread_mutex_trylock(&dealmutex)!=0)
//    {
//        qDebug() << "face detect busy now..., return";
//        return;
//    }
    if(!m_checkFlag)
    {
        qDebug() << "face detect busy now..., return";
        return;
    }
//    qDebug() << "dealface.........";
    Exectime etm(__FUNCTION__);
    IK_Rect rect = m_lastFaceRect;
     int channel = 0;
//     qDebug() << img.format();
//     QMatrix leftmatrix;
//     leftmatrix.rotate(90);
//     QImage timg = img.transformed(leftmatrix,Qt::SmoothTransformation);
     img = img.mirrored(true, false);
     switch(img.format())
     {
     case QImage::Format_ARGB32:
     case QImage::Format_RGB32:
     case QImage::Format_ARGB32_Premultiplied:
         channel = 4;
         break;
     case QImage::Format_RGB888:
         channel = 3;
         break;
     case QImage::Format_Indexed8:
     case QImage::Format_Mono:
         channel = 1;
         break;
     default:
         break;
     }

     float curAngle = ptzBase::get_Instance()->getSteeringAngle();

    detectTracking(img.bits(), img.height(), img.width(), channel, rect, m_Info);
//    qDebug() << m_Info.flag << m_Info.pupilLX << m_Info.pupilLY  << ret;
    m_lastFaceRect = rect;
    // emit result(m_Info);
    controlSteering(m_Info, curAngle);
    //    pthread_mutex_unlock(&dealmutex);
}

void FaceTrack::controlSteering(const pointData& info, float curAngle)
{
    QPointF p_center(0, 0);

    /*****  云台的运动控制   *****/
    if (info.flag) // 人脸检测成功
    {
        qDebug() << "detect face : flag=" << info.flag << "("<< info.pupilLX << ", " << info.pupilLY << ")";
        p_center = QPointF(info.browCX-m_ptCenter.x(), info.browCY-m_ptCenter.y());

        m_heartBeat = 0;
        //如果有目标物，云台就运动
        steeringPTZ(p_center.y(), false, curAngle);
    }
    else
    {
//        ptzBase::get_Instance()->m_pupilDist = 0;
//        ptzBase::get_Instance()->m_faceBrowCenter = QPoint();
        m_heartBeat++;//心跳包

        //连续30张图像没检测到目标，则拉回镜头，功能关闭
        if (m_heartBeat>30 )//&& quality_roll>2.0f)
        {
            m_heartBeat = 0;
            steeringPTZ(p_center.y(), true, curAngle);
        } // end of ptz homing
    }

    return;
}

const static int g_cameraFOVWidth = 50;     // 相机宽度方向视场角
const static int g_cameraFOVHeight = 67;     // 相机高度方向视场角
/*********************************
功   能：根据云台机械结构，使用PID算法进行控制云台运动
作   者：yqhe
日   期：20180228
修改 人：yqhe
修改内容：经测试，舵机不是一定要转动整数角度，
                  可以转动小数的角度，例如0.3的差异是可以看出来的
                  因此，修改角度设置的接口，改为float类型
修改日期：20180301
参   数：
     1.Face_center_ABS为眉心与标定点像素差额
     2.homing为云台返航控制符
**********************************/
extern int ov5640_g_height;
void FaceTrack::steeringPTZ(float faceCenterY, bool homing, float curAngle)
{
    //云台运动的运算
    // float offsetX = 0;
    float offsetY = 0.0f;
    /************************************************************
     * 计算需要转动的角度, 根据公式l =R*θ， 半径= 弧长/角度, 图像高度近似弧长，
     * 图像高度 = 图像像素高度* 单位像素物理尺寸，
     * 则得出 图像高度/高度方向FOV = 半径 =  运动距离/舵机运动角度
     * 可得舵机运动角度 = (像素运动距离*FOV)/图像高度
     ************************************************************/
    // offsetX = faceCenterX*g_cameraFOVWidth/(ov5640_g_width);
    //选用1/7步长进行行进,减少在最有点振荡的可能性，发送给云台模块
    offsetY = 0.0f - faceCenterY*g_cameraFOVHeight/(ov5640_g_height)/1.9f;//公式转动像素步长x(y)*视场角/图像高度

//    int integerPart = (int)offsetY;
//    m_remainDecimal += (offsetY - integerPart);

//    int remainPart = (int)m_remainDecimal;
//    integerPart += remainPart;
//    m_remainDecimal -= integerPart;

//    float setAngle = curAngle + integerPart;
    float setAngle = curAngle + offsetY;

    qDebug() << "setSteeringAngle angle= " << setAngle << ", offsetY=" << offsetY  << ", curAngle" << curAngle;
    ptzBase::get_Instance()->setSteeringAngle(setAngle, homing);

}
