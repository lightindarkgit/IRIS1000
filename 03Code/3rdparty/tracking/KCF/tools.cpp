#include <stdlib.h>
#include <ffttools.h>
//#include <highgui.hpp>
//#include <dft.h>
#include <iostream>
#include <ctime>
//#include <test.h>
#include <dft.hpp>
#define EV 2.718281828459

////////////////////////////////////////////////////////////////////
//计算WN
///////////////////////////////////////////////////////////////////
void getWN(double n,double size_n,std::complex<float> * dst);

int RealFFT(double * src,std::complex<float> * dst,int size_n);

int FFT2D(float *src,std::complex<float> *dst,int size_w,int size_h);

int isBase2(int size_n);


int isBase2(int size_n){
    int k=size_n;
    int z=0;
    while (k/=2) {
        z++;
    }
    k=z;
    if(size_n!=(1<<k))
        return -1;
    else
        return k;
}

namespace  FFTTools{

void fftd(float* srcImg, int srcH, int srcW, int srcChnnel, float* dstImg, bool backwards)
{
    float* dst = new float[srcH*srcW*2];
    if (srcChnnel == 1)
    {
        float* n_image = new float[srcH*2*srcW];
        memset(n_image, 0x00, sizeof(float)*srcH*2*srcW);
        memcpy(n_image, srcImg, sizeof(float)*srcH*srcW);
        //cv::Mat planes[] = {cv::Mat_<float> (src), cv::Mat_<float>::zeros(src.size())};
        //cv::Mat planes[] = {cv::Mat_<double> (src), cv::Mat_<double>::zeros(src.size())};
        //cv::merge(planes, 2, img);
        IK_mergeImageChannel(n_image, srcH*2, srcW, 2, dst);
        delete n_image;
    }else{
        memcpy(dst, srcImg, sizeof(float)*srcH*srcW*2);
        //img = src.clone();
    }

    fbc::Mat_<float, 2> complexI(srcH, srcW, dst);
    fbc::Mat_<float, 2> dft(srcH, srcW);
    fbc::dft(complexI, dft,backwards?(fbc::DFT_INVERSE | fbc::DFT_SCALE) : 0);
    //img.data = dft.data;
    //dft((float*)img.data, img.rows, img.cols, img.channels());
    memcpy(dstImg, dft.data, sizeof(float)*srcH*srcW*2);
    delete dst;
}

//计算互功率谱的分子部分，即公式3中的分子，其中P为输出结果，true表示的是对FF2取共轭，所以得到的结果为：P=FFT1×FFT2*，mulSpectrums函数为通用函数
void mulSpectrums(float* src1, float* src2, float* dst, int rows, int cols, int channel)
{
    assert(src1!=0);
    assert(src2!=0);
    assert(channel==2);
    int inv = -1;
    for(int i=0; i<rows; i++)
    {
        float* src1W = src1 + i*cols*channel;
        float* src2W = src2 + i*cols*channel;
        float* dstW = dst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            //复数相乘运算
            *(dstW + j*channel) = (*(src1W + j*channel)) * (*(src2W + j*channel)) - (*(src1W + j*channel + 1))*(inv)*(*(src2W + j*channel + 1));
            *(dstW + j*channel + 1) = (*(src1W + j*channel)) * (inv)*(*(src2W + j*channel + 1)) + (*(src1W + j*channel + 1))*(*(src2W + j*channel));
        }
    }
}

}


////
/// \brief Matrix_Linner
/// \param src
/// \param rows
/// \param cols
/// \param channel
/// \param plus
/// \param mul
///对图像进行加法和数乘的线性运算
void Matrix_Linner(float* srcDst, int rows, int cols, int channel, float plus, float mul)
{
    for(int i=0; i<rows; i++)
    {
        float* srcDstW = srcDst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float* srcDstWC = srcDstW + j*channel;
            for(int k=0; k<channel; k++)
            {
                *(srcDstWC + k) = (*(srcDstWC +k))*mul + plus;
            }
        }
    }
}

///
/// \brief Matrix_EXP
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///对数据进行e 的指数次幂运算
void Matrix_EXP(float* srcDst, int rows, int cols, int channel)
{
    for(int i=0; i<rows; i++)
    {
        float* srcDstW = srcDst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float* srcDstWC = srcDstW + j*channel;
            for(int k=0; k<channel; k++)
            {
                *(srcDstWC + k) = pow(EV, *(srcDstWC +k));
            }
        }
    }
}

///
/// \brief Matrix_complexDivision
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///复数的除法
void Matrix_complexDivision(float* src1,float* src2, float* dst, int rows, int cols, int channel)
{
    assert(channel==2);
    for(int i=0; i<rows; i++)
    {
        float* src1W = src1 + i*cols*channel;
        float* src2W = src2 + i*cols*channel;
        float* dstW = dst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float src1Real = *(src1W + j*channel);
            float src1Imag = *(src1W + j*channel + 1);
            float src2Real = *(src2W + j*channel);
            float src2Imag = *(src2W + j*channel + 1);
            float divisor = 1.0f/(src2Real*src2Real + src2Imag*src2Imag);
            *(dstW + j*channel) = (src1Real*src2Real + src1Imag* src2Imag)*divisor;
            *(dstW + j*channel + 1) = (src1Imag*src2Real + src1Real* src2Imag)*divisor;
        }
    }
}

///
/// \brief Matrix_complexDivision
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///复数的乘法
void Matrix_complexMultiplication(float* src1,float* src2, float* dst, int rows, int cols, int channel)
{
    assert(channel==2);
    for(int i=0; i<rows; i++)
    {
        float* src1W = src1 + i*cols*channel;
        float* src2W = src2 + i*cols*channel;
        float* dstW = dst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float src1Real = *(src1W + j*channel);
            float src1Imag = *(src1W + j*channel + 1);
            float src2Real = *(src2W + j*channel);
            float src2Imag = *(src2W + j*channel + 1);
            *(dstW + j*channel) = (src1Real*src2Real - src1Imag* src2Imag);
            *(dstW + j*channel + 1) = (src1Real*src2Imag + src1Imag* src2Real);
        }
    }
}

///
/// \brief Matrix_minMaxLoc
/// \param src
/// \param rows
/// \param cols
/// \param channel
/// \param bestVal
/// \param bestX
/// \param bestY
///计算矩阵中最大值以及最大值位置
void Matrix_MaxLoc(float* src, int rows, int cols, int channel, double& bestVal, int& bestX, int& bestY)
{
    //assert(channel==2);
    float score=0;
    int x=0;
    int y=0;
    for(int i=0; i<rows; i++)
    {
        float* srcW = src + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float* stcWC = srcW + j*channel;
            for(int k=0; k<channel; k++)
            {
                float val = *(stcWC + k);
                if(val>score)
                {
                    score = (double)val;
                    x=j;
                    y=i;
                }
            }
        }
    }
    bestX = x;
    bestY = y;
    bestVal = score;
}
//cv::Mat complexMultiplication(cv::Mat a, cv::Mat b)
//{
//    std::vector<cv::Mat> pa;
//    std::vector<cv::Mat> pb;
//    cv::split(a, pa);
//    cv::split(b, pb);

//    std::vector<cv::Mat> pres;
//    pres.push_back(pa[0].mul(pb[0]) - pa[1].mul(pb[1]));
//    pres.push_back(pa[0].mul(pb[1]) + pa[1].mul(pb[0]));

//    cv::Mat res;
//    cv::merge(pres, res);

//    return res;
//}
///
/// \brief Matrix_Max
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
/// \param plus
/// \param mul
///求两个矩阵最大值
void Matrix_Max(float* src1, float* src2, float* dst, int rows, int cols, int channel)
{
    for(int i=0; i<rows; i++)
    {
        float* src1W = src1 + i*cols*channel;
        float* src2W = src2 + i*cols*channel;
        float* dstW = dst + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            float* src1WC = src1W + j*channel;
            float* src2WC = src2W + j*channel;
            float* dstWC = dstW + j*channel;
            for(int k=0; k<channel; k++)
            {
                *(dstWC + k) = std::max(*(src1WC + k), *(src2WC + k));
            }
        }
    }
}
