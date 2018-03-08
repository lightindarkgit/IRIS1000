#include <stdlib.h>
#include <kcftracker.hpp>
#ifdef Q_OS_UNIX
//#include "ikAlgoFaceDetectionlinux.h"
#include "ikAlgoFaceDetection.h"
#elif defined(Q_OS_WIN)
#include "ikAlgoFaceDetection.h"
#endif
#include <algorithm>
#include <iostream>
#include <assert.h>
//#include <ldmarkmodel.h>
#include <string.h>
#include <math.h>
#include <tracker.h>
#include <publicdata.h>
//#include <imdebug.h>
#include <thread.hpp>
//#include <sdmlib.h>
//#include <kdKeyPointsDetector.h>
#include <kdFaceKeyPointDetect.h>
#define DETECT_BUFFER_SIZE 0x20000       //定义人脸检测需要分配的内存大小
#define IMAGEWIDTH 480
#define IMAGEHEIGHT 640
#define CHANNEL 3
struct ImageData{
   unsigned char data[IMAGEWIDTH*IMAGEHEIGHT*CHANNEL];
   int usedWidth;
   int usedHeight;
   int usedChannel;
   bool valid;
};

pthread_t tid;
int counter = 0;
pthread_mutex_t lock;
bool  threadStart = false;
ImageData  img;
/*********************************
功   能：人脸检测,使用于仕琪算法API
作   者：zhangyp
日   期：20170514
修改 人：
修改内容：
修改日期：
参   数：
     1.cv::Mat&  face_img: 输入图像
     2.cv::Rect& crop:输入/获得的人脸区域
     3.Face  :人脸检测到的人脸区域
返回 值：0为检测成功， 1位检测失败
**********************************/
int  softFaceDetect(unsigned char* face_img, int rows, int cols, int channel, IK_Rect& crop, IK_Rect& Face);
//彩色转灰度
void RGB2Gray(unsigned char* srcData, unsigned char* dst, int srcRows, int srcCols, int srcChannel);
//unsigned char version
int kdKeyImResize(const unsigned char* srcData, int srcW, int srcH, int srcChannels, unsigned char* dstData, int dstW, int dstH, int dstChannels);

/*********************************
功   能：人脸检测
作   者：zhangyp
日   期：20170514
修改 人：
修改内容：
修改日期：
参   数：
     1.cv::Mat&  face_img: 输入图像
     2.cv::Rect& crop:获得的人脸区域
返回 值：0为检测成功， 1位检测失败
**********************************/
int  Face_detect(unsigned char* srcImg, int rows, int cols, int channel, IK_Rect& crop);
///*********************************
//功   能：按矩形提取ROI图像

//作   者：zhangyp
//日   期：20170525
//修改 人：
//修改内容：
//修改日期：
//参   数：
//     1.const cv::Mat& img：原图
//     2.cv::Rect rect:矩形框
//返回 值： 返回ROI图像
//**********************************/
//void cropBigImage(const unsigned char* img, unsigned char* dst, int rows, int cols, int channel, IK_Rect rect);

/*********************************
功   能：解析对齐后的关键点矩阵，i7上13ms

作   者：zhangyp
日   期：20170514
修改 人：
修改内容：
修改日期：
参   数：
     1.cv::Mat 图像：原始图像

返回 值：
**********************************/
void parseLandmark(unsigned char* faceImage, int rows, int cols, int channel, IK_Rect& ROI, pointData& data);

///检测+跟踪
int detectTracking(unsigned char* srcImg, int rows, int cols, int channel, IK_Rect& crop, pointData& data)
{
    memset(&data, 0x00, sizeof(pointData));
    if(channel!=3)
        return -1001;
    //////////如果连续多帧无数据则跳帧///////////////////////
    static int g_noPersonCount = 0;//无人帧数
    static long g_frameCount = 0; //总帧数
    static long g_frameRate = 1; //帧率
    g_frameCount++;
    if(g_noPersonCount>50)
    {
        g_frameRate = 20;
    }else{
        g_frameRate = 1;
    }
    if(!(g_frameCount%g_frameRate == 0))
    {
        return -1;
    }
    ///////////////////////////////////////////////////
    float ratio = 2;
    int smallRows = rows/ratio;
    int smallCols = cols/ratio;
    //unsigned char* m_Gray_small = new unsigned char[smallRows*smallCols*channel];
    //给图像赋值
    img.usedChannel = channel;
    img.usedHeight = smallRows;
    img.usedWidth = smallCols;
    img.valid = true;
    //cv::Mat smallFace(m_gray.rows/ratio, m_gray.cols/ratio,m_gray.type());
    kdKeyImResize(srcImg, cols, rows, channel, img.data, smallCols, smallRows, channel);
    //IK_Rect m_FaceRect;
    IK_Rect m_firstFaceRect;

//    static timeElapsed ts;
//    ts.startTime();
    int ret = softFaceDetect(img.data, smallRows, smallCols, channel, crop,m_firstFaceRect);

//   std::cout<<"total time: "<<ts.avgTime()<<" total:"<<ts.getCount()<<std::endl;
    std::cout << "softFaceDetect ret=" << ret;


    img.valid = false;

    /*****   关键点对齐与解析  *****/

    if(0 == ret)
    {
        //std::cout<<" count2 rate: "<<(float)count2/(float)count<<std::endl;
        data.flag = true;
        crop.m_x = crop.m_x*ratio;
        crop.m_y = crop.m_y*ratio;
        crop.m_width = crop.m_width*ratio;
        crop.m_height = crop.m_height*ratio;
         //检测赋值
        data.track_cropX = crop.m_x;
        data.track_cropY = crop.m_y;
        data.track_cropWidth = crop.m_width;
        data.track_cropHeight = crop.m_height;

        data.detect_cropX = m_firstFaceRect.m_x*ratio;
        data.detect_cropY = m_firstFaceRect.m_y*ratio;
        data.detect_cropWidth = m_firstFaceRect.m_width*ratio;
        data.detect_cropHeight = m_firstFaceRect.m_height*ratio;

        //std::cout<<"ret:"<<ret<<std::endl;
        //publicData::startTime();
        unsigned char* grayImage = new unsigned char[rows*cols];
        if(channel == 3)
        {
            RGB2Gray(srcImg, grayImage, rows, cols, channel);
        }else if(channel == 1)
        {
            memcpy(grayImage, srcImg, rows*cols*sizeof( unsigned char));
        }
        //init KD
        IKKeyPoint kd;
        kd.startX = crop.m_x+crop.m_width*0.25;
        kd.startY = crop.m_y + crop.m_height*0.2;
        kd.rectWidth = crop.m_width*0.55;
        kd.rectHeight = crop.m_height*0.55;
        IKFR_KeyPointDetect(grayImage, rows, cols, &kd, 1,0,0);
        for(int k=0; k<LANDMARKNUM; k++)
        {
            data.landmarks[2*k] = kd.landmarks_x[k];
            data.landmarks[2*k+1] = kd.landmarks_y[k];
        }
        data.browCX = (kd.landmarks_x[0] + kd.landmarks_x[1] + kd.landmarks_x[2] + kd.landmarks_x[3])/4;
        data.browCY = (kd.landmarks_y[0] + kd.landmarks_y[1] + kd.landmarks_y[2] + kd.landmarks_y[3])/4;
        data.pupilLX = (kd.landmarks_x[0] + kd.landmarks_x[1])/2;
        data.pupilLY = (kd.landmarks_y[0] + kd.landmarks_y[1])/2;
        data.pupilRX = ( kd.landmarks_x[2] + kd.landmarks_x[3])/2;
        data.pupilRY = ( kd.landmarks_y[2] + kd.landmarks_y[3])/2;
        //std::cout<<"avg time: "<<tl.avgTime()<< "  count:"<<tl.getCount()<<"\n"<<std::endl;
        delete grayImage;
        g_noPersonCount = 0;
        return 0;
    }else{
        //data[0] = 0;
        data.flag = false;
        g_noPersonCount++;
        //memset(data, 0x00, sizeof(float)*dataNum);
        //m_FaceRect = crop;
        return -1;
    }

}

/*********************************
功   能：人脸检测,使用于仕琪算法API
作   者：zhangyp
日   期：20170514
修改 人：
修改内容：
修改日期：
参   数：
     1.cv::Mat&  face_img: 输入图像
     2.cv::Rect& crop:最终获得的人脸区域
     3.cv::Rect& face:检测到的人脸区域
返回 值：0为检测成功， 1位检测失败
**********************************/
int  softFaceDetect(unsigned char* face_img, int rows, int cols, int channel,  IK_Rect& crop, IK_Rect& detectFace)
{
    static IK_Rect      l_LastRectFace = IK_Rect();
    IK_Rect             RectFace;//检测到的人脸矩形

    static bool         m_trackerInitialized = false;
    //static int          m_faceLostCount = 0;
    static int          m_trackCount = 0;
    int refineFaceCols = 0;
    int refineFaceRows = 0;
    int offsetX = 0;
    int offsetY = 0;
    float extend = 1.5f;
    //cv::Mat m_img2;
    unsigned char* refineFace = 0;
    //图像判断ROI
    int ret = -1;
    if(l_LastRectFace == IK_Rect())
    {
        refineFaceCols = cols;
        refineFaceRows = rows;
        offsetX = 0;
        offsetY = 0;
        refineFace = new unsigned char[refineFaceRows* refineFaceCols*channel];
        memcpy(refineFace,face_img, sizeof(unsigned char)*rows* cols*channel );
    }else{
        refineFaceCols = l_LastRectFace.m_width * extend;
        refineFaceRows = l_LastRectFace.m_height * extend;
        offsetX = l_LastRectFace.m_x - l_LastRectFace.m_width*(extend-1)*0.5;
        offsetY = l_LastRectFace.m_y - l_LastRectFace.m_height*(extend-1)*0.5;
        refineFace = new  unsigned char[refineFaceRows* refineFaceCols*channel];
        dipImCrop(face_img, rows, cols, channel, offsetY, offsetX, refineFace, refineFaceRows, refineFaceCols, channel);
        //cropBigImage(face_img, refineFace, rows, cols, channel, l_LastRectFace);
    }
    //imdebug("rgb w=%d h=%d %p", refineFaceCols, refineFaceRows, refineFace);
    //如果跟踪已初始化
    if(m_trackerInitialized)
    {
        IK_Rect  getRoi;
        double score = IK_trackingUpdate(refineFace, refineFaceCols, refineFaceRows, getRoi);
        //std::cout<<"track time: "<<tTrack.avgTime()<<" score:"<<score<<" m_trackCount:"<<m_trackCount<<std::endl;
        if (score >0.65 && m_trackCount<20)
        {
            RectFace = getRoi;
            detectFace = IK_Rect(0,0,0,0);
            ret = 0; //跟得上
            m_trackCount++;
        }else{//分低并且跟踪次数也足够多
            //m_trackerInitialized = false;
            ret  = -1;
            m_trackCount =0;
        }
    }
    //否则进行人脸检测
    if(-1 == ret)
    {
        ret = Face_detect(refineFace, refineFaceRows, refineFaceCols, channel, RectFace);
        //std::cout<<"detect time: "<<tDetect.avgTime()<< " us count:"<<tDetect.getCount()<<" RectFace:"<<RectFace.m_width<<","<<RectFace.m_height<<std::endl;
        if (0 == ret)
        {
            detectFace = IK_Rect(RectFace.m_x + offsetX, RectFace.m_y + offsetY, RectFace.m_width, RectFace.m_height);
            //检测成功更新跟踪模板
            IK_Rect rect(RectFace);
            IK_trackingInit(rect, refineFace, refineFaceCols, refineFaceRows, channel);//初始化跟踪
            m_trackerInitialized = true;
        }else{
            detectFace = IK_Rect(0,0,0,0);
            m_trackerInitialized = false;
            ret  = -1;
            m_trackCount =0;
        }
    }
    //结果处理
    IK_Rect     FaceWeight = l_LastRectFace;   //人脸均值
    int weightX = ((RectFace.m_x + offsetX) + FaceWeight.m_x)/2;
    int weightY = ((RectFace.m_y + offsetY) + FaceWeight.m_y)/2;
    int weightWidth = (RectFace.m_width + FaceWeight.m_width)/2;
    int weightHeight = (RectFace.m_height + FaceWeight.m_height)/2;
    if(-1 == ret )
    {
        offsetX = 0;
        offsetY = 0;
        weightX = 0;
        weightY = 0;
        weightWidth = 0;
        weightHeight = 0;
    }else if(l_LastRectFace == IK_Rect()){
        weightX = (RectFace.m_x + offsetX);
        weightY = (RectFace.m_y + offsetY);
        weightWidth = RectFace.m_width;
        weightHeight = RectFace.m_height;
    }

    l_LastRectFace = IK_Rect(weightX, weightY, weightWidth, weightHeight);
    //人脸检测
    crop = IK_Rect(weightX, weightY, weightWidth, weightHeight);
    delete refineFace;
    return ret;
}


/*********************************
功   能：人脸检测
作   者：zhangyp
日   期：20170514
修改 人：
修改内容：
修改日期：
参   数：
     1.cv::Mat&  face_img: 输入图像
     2.cv::Rect& crop:获得的人脸区域
返回 值：0为检测成功， 1位检测失败
**********************************/
int  Face_detect(unsigned char* srcImg, int rows, int cols, int channel, IK_Rect& crop)
{
    //图像非空判断
    int  ret = 0;
    if(srcImg==0)
        return -1;
    unsigned char* grayImage = new unsigned char[rows*cols];
    if(channel == 3)
    {
        RGB2Gray(srcImg, grayImage, rows, cols, channel);
    }else if(channel == 1)
    {
        memcpy(grayImage, srcImg, rows*cols*sizeof( unsigned char));
    }

    //face detection
    int* pResults = NULL;
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if(!pBuffer)
    {
        delete grayImage;
        //delete m_Gray_small;
        return 1;
    }
//    static timeElapsed faceDetect;
//    faceDetect.startTime();
        //!!! DO NOT RELEASE pResults !!![240*320]
    pResults = facedetect_multiview_reinforce(pBuffer, grayImage, cols, rows, cols,
                                             1.2f, 3, (int)rows*0.1,rows);//facedetect_multiview_reinforce//facedetect_frontal
    //std::cout<<"faceDetect:"<<faceDetect.avgTime()<<std::endl;
//    static int count =0;
//    static float elapsedTime = 0.0f;
//    publicData::startTime();
    ////////////////////////////////////////////////////////////
    if((pResults ? *pResults : 0) >0)
    {
        //std::cout<<"detect:"<<cols<<std::endl;
        //imdebug("lum w=%d h=%d %p", cols, rows, grayImage);
        //单张人脸部分
        int faceToCenterDist = 0, face_AreaWeight = 0, face_dist=0; //人脸距离图像中心距离，人脸面积，人脸距离上一张的距离
        int pos=-1;//游标
        int maxLength = cols/2;
        for(int i = 0; i < (pResults ? *pResults : 0); i++)
        {
            int p_areaWeight=0, p_dist=0;
            short * point = ((short*)(pResults+1))+6*i;
            IK_Rect rect(point[0], point[1], point[2], point[3]);
            faceToCenterDist = std::abs(cols/2 - (rect.m_x + rect.m_width/2));
            p_areaWeight = sqrt(rect.m_width)*(maxLength - faceToCenterDist); //计算优先级面积乘以权重
            p_dist = sqrt((crop.m_x - rect.m_x)*(crop.m_x - rect.m_x) + (crop.m_y - rect.m_y)*(crop.m_y - rect.m_y));
            if(crop.m_width*crop.m_height!=0 && p_dist>face_dist && p_dist<3*rect.m_width)      //已知人脸位置求和上一次位置最近的人脸
            {
                face_dist = p_dist;
                pos = i;
            }else if(crop.m_width*crop.m_height == 0 && p_areaWeight>face_AreaWeight)         //未知人脸位置全局检测找权值最大的一个
            {
                face_AreaWeight = p_areaWeight;
                pos = i;
            }
        }
        //找到人脸
        if (pos>=0)
        {
            short * p = ((short*)(pResults+1))+6*pos;
            crop = IK_Rect(p[0], p[1], p[2], p[3]);
            ret = 0;
        }
    }else{
        std::cout<<"no detect:"<<cols<<std::endl;
        crop = IK_Rect(0,0,0,0);
        ret = 1;
    }
//    count++;
//    elapsedTime+=publicData::stopTime();
//    std::cout<<"time: "<<elapsedTime/count<< " us count:"<<count<<std::endl;
    free(pResults);
    delete grayImage;
    //delete m_Gray_small;
    return ret;
}
//彩色转灰度
void RGB2Gray(unsigned char* srcData, unsigned char* dst, int srcRows, int srcCols, int srcChannel)
{
    if(3 == srcChannel)
    {
        for(int i=0; i<srcRows; i++)
        {
            unsigned char* srcW = srcData + i*srcCols*3;
            unsigned char* dstW = dst + i*srcCols;
            for(int j=0; j<srcCols; j++, srcW+=3,dstW+=1)
            {
                float average = (srcW[0] + srcW[1] + srcW[2])/3;
                *(dstW) = (std::min)(average, 255.0f);
            }
        }
    }
}

//unsigned char version
int kdKeyImResize(const unsigned char* srcData, int srcW, int srcH, int srcChannels, unsigned char* dstData, int dstW, int dstH, int dstChannels)
{
   //std::vector<int> tabsx(dstH);
   //std::vector<int> tabsy(dstW);
   //std::vector<float> tabrx(dstH);
   //std::vector<float> tabry(dstW);

   int* tabsx = new int[dstH];
   int* tabsy = new int[dstW];
   float* tabrx = new float[dstH];
   float* tabry = new float[dstW];

   const float fx = (float)(dstH) / srcH;
   const float fy = (float)(dstW) / srcW;
   const float ifx = 1.f / fx;
   const float ify = 1.f / fy;
   for (int dx = 0; dx < dstH; ++dx)
   {
       float rx = (dx + 0.5f) * ifx - 0.5f;
       int sx = (int)(floor(rx));
       rx -= sx;
       if (sx < 0)
       {
           sx = 0;
           rx = 0;
       }
       else if (sx + 1 >= srcH)
       {
           sx = srcH - 2;
           rx = 1;
       }
       tabsx[dx] = sx;
       tabrx[dx] = rx;
   }
   for (int dy = 0; dy < dstW; ++dy)
   {
       float ry = (dy + 0.5f) * ify - 0.5f;
       int sy = (int)(floor(ry));
       ry -= sy;
       if (sy < 0)
       {
           sy = 0;
           ry = 0;
       }
       else if (sy + 1 >= srcW)
       {
           sy = srcW - 2;
           ry = 1;
       }
       tabsy[dy] = sy;
       tabry[dy] = ry;
   }

   const int ch = srcChannels;
   for (int dx = 0; dx < dstH; ++dx)
   {
       const unsigned char *p0 = srcData + tabsx[dx] * srcW*ch;
       const unsigned char *p1 = srcData + (tabsx[dx] + 1)*srcW*ch;
       unsigned char *pdst = dstData + (dx)*dstW*dstChannels;
       float rx = tabrx[dx], irx = 1.0f - rx;
       for (int dy = 0; dy < dstW; ++dy)
       {
           unsigned char *pcdst = pdst + dy*ch;
           const unsigned char *pc00 = p0 + (tabsy[dy] + 0)*ch;
           const unsigned char *pc01 = p0 + (tabsy[dy] + 1)*ch;
           const unsigned char *pc10 = p1 + (tabsy[dy] + 0)*ch;
           const unsigned char *pc11 = p1 + (tabsy[dy] + 1)*ch;
           float ry = tabry[dy], iry = 1.0f - ry;
           for (int c = 0; c < ch; ++c)
           {
               unsigned char res = (unsigned char)(rx * (pc11[c] * ry + pc10[c] * iry) + irx * (pc01[c] * ry + pc00[c] * iry));
               pcdst[c] = res;
           }
       }
   }
   delete tabsx;
   delete tabsy;
   delete tabrx;
   delete tabry;
   return 0;
}
