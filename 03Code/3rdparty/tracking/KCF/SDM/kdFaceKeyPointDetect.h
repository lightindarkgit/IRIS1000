#ifndef _IK_FACE_KD_DETECT_
#define _IK_FACE_KD_DETECT_
#define IKALG_PLATFORM_LINUX //_NO
#define IKALG_PLATFORM_ANDROID_NO
#define IKALG_PLATFORM_WINDOWS_NO
#define IKALG_VERSION_X64_NO



#ifdef IKALG_PLATFORM_WINDOWS
#	ifdef IK_ALGO_EXPORTS
#		define IK_ALGO_API extern "C" __declspec(dllexport)
#	else
#		define IK_ALGO_API extern "C" __declspec(dllimport)
#	endif
#else
#		define IK_ALGO_API extern "C"
#endif


#define KD_POINTNUM							6

struct  IKPosture;
struct  IKPosture
{
    int var;
    int openLevel;
    int horizont_angle;
    int slope_angle;
};

struct IKKeyPoint
{
    int startX;                     //做关键点检测的矩形区域
    int startY;
    int rectWidth;
    int rectHeight;
    char type;
    int valid;
    IKPosture ps;
    int landmarks_x[KD_POINTNUM];
    int landmarks_y[KD_POINTNUM];
};
/*****************************************************************************************************************
*               函数介绍 可见光人脸的关键点检测
* 函数声明：int IKFR_InitKeyPoints(IKKeyPoint *kp)
* 函数类型：int
* 输    入：IKKeyPoint *kp：关键点结构体
* 输    出：IKKeyPoint *kp：初始化后的关键点结构体
* 返回类型：int
* 函数功能：对关键点结构体进行初始化
* 创 建 人：李星光
* 创建时间：2017.09.28
* 注    释：
******************************************************************************************************************/
IK_ALGO_API int IKFR_InitKeyPoints(IKKeyPoint *kp);
/*****************************************************************************************************************
*               函数介绍 可见光人脸的关键点检测
* 函数声明：int IKFR_KeyPointDetect(unsigned char *data, int surImH, int surImW, IKKeyPoint *kp, unsigned int kpCount, int deviceType, int algoFlag)
* 函数类型：int
* 输    入：unsigned char *data：	输入的可见光人脸图像
int surImH：			输入的图像的高
int surImW：			输入的图像的宽
unsigned int kpCount：	输入的关键点个数
int deviceType：		输入的设备类型
int algoFlag：			输入的算法类型
* 输    出：IKKeyPoint *kp：		输出的检测的关键点坐标
* 返回类型：int
* 函数功能：检测可见光人脸的关键点坐标
* 创 建 人：李星光
* 创建时间：2017.09.28
* 注    释：
******************************************************************************************************************/
IK_ALGO_API int IKFR_KeyPointDetect(unsigned char *data, int surImH, int surImW, IKKeyPoint *kp, unsigned int kpCount, int deviceType, int algoFlag = 0);


#endif // _IK_FACE_KD_DETECT_
