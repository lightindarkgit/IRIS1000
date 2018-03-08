/*

Tracker based on Kernelized Correlation Filter (KCF) [1] and Circulant Structure with Kernels (CSK) [2].
CSK is implemented by using raw gray level features, since it is a single-channel filter.
KCF is implemented by using HOG features (the default), since it extends CSK to multiple channels.

[1] J. F. Henriques, R. Caseiro, P. Martins, J. Batista,
"High-Speed Tracking with Kernelized Correlation Filters", TPAMI 2015.

[2] J. F. Henriques, R. Caseiro, P. Martins, J. Batista,
"Exploiting the Circulant Structure of Tracking-by-detection with Kernels", ECCV 2012.

Authors: Joao Faro, Christian Bailer, Joao F. Henriques
Contacts: joaopfaro@gmail.com, Christian.Bailer@dfki.de, henriques@isr.uc.pt
Institute of Systems and Robotics - University of Coimbra / Department Augmented Vision DFKI


Constructor parameters, all boolean:
    hog: use HOG features (default), otherwise use raw pixels
    fixed_window: fix window size (default), otherwise use ROI size (slower but more accurate)
    multiscale: use multi-scale tracking (default; cannot be used with fixed_window = true)

Default values are set for all properties of the tracker depending on the above choices.
Their values can be customized further before calling init():
    interp_factor: linear interpolation factor for adaptation
    sigma: gaussian kernel bandwidth
    lambda: regularization
    cell_size: HOG cell size
    padding: area surrounding the target, relative to its size
    output_sigma_factor: bandwidth of gaussian target
    template_size: template size in pixels, 0 to use ROI size
    scale_step: scale step for multi-scale estimation, 1 to disable it
    scale_weight: to downweight detection scores of other scales for added stability

For speed, the value (template_size/cell_size) should be a power of 2 or a product of small prime numbers.

Inputs to init():
   image is the initial frame.
   roi is a cv::Rect with the target positions in the initial frame

Inputs to update():
   image is the current frame.

Outputs of update():
   cv::Rect with target positions for the current frame


By downloading, copying, installing or using the software you agree to this license.
If you do not agree to this license, do not download, install,
copy or use the software.


                          License Agreement
               For Open Source Computer Vision Library
                       (3-clause BSD License)

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of the contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and
any express or implied warranties, including, but not limited to, the implied
warranties of merchantability and fitness for a particular purpose are disclaimed.
In no event shall copyright holders or contributors be liable for any direct,
indirect, incidental, special, exemplary, or consequential damages
(including, but not limited to, procurement of substitute goods or services;
loss of use, data, or profits; or business interruption) however caused
and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of
the use of this software, even if advised of the possibility of such damage.
float interp_factor;        // linear interpolation factor for adaptation
                                // 自适应的线性插值因子，会因为hog，lab的选择而变化
    float sigma;                // gaussian kernel bandwidth
                                // 高斯卷积核带宽，会因为hog，lab的选择而变化
    float lambda;               // regularization
                                // 正则化，0.0001
    int cell_size;              // HOG cell size
                                // HOG元胞数组尺寸，4
    int cell_sizeQ;             // cell size^2, to avoid repeated operations
                                // 元胞数组内像素数目，16，为了计算省事
    float padding;              // extra area surrounding the target
                                // 目标扩展出来的区域，2.5
    float output_sigma_factor;  // bandwidth of gaussian target
                                // 高斯目标的带宽，不同hog，lab会不同
    int template_size;          // template size
                                // 模板大小，在计算_tmpl_sz时，
                                // 较大变成被归一成96，而较小边长按比例缩小
    float scale_step;           // scale step for multi-scale estimation
                                // 多尺度估计的时候的尺度步长
    float scale_weight;         // to downweight detection scores of other scales for added stability
                                // 为了增加其他尺度检测时的稳定性，给检测结果峰值做一定衰减，为原来的0.95倍
 */

#ifndef _KCFTRACKER_HEADERS
#include "kcftracker.hpp"
#include "ffttools.h"
#include "fhog.hpp"
//#include "labdata.hpp"
#include <tracker.h>
#endif
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <publicdata.h>
const float param_13 = 1.0f / 3.0f;
const float param_16116 = 16.0f / 116.0f;
const float Xn = 0.950456f;
const float Yn = 1.0f;
const float Zn = 1.088754f;

bool HOG = true;
bool FIXEDWINDOW = false;
bool MULTISCALE = true;
KCFTracker  g_tracker(HOG, FIXEDWINDOW, MULTISCALE);
void IK_trackingInit(const IK_Rect &roi, unsigned char* image, int cols, int rows,int channel)
{
   // cv::Mat matImage(rows, cols, CV_8UC3, image);
    g_tracker.init(roi, image, cols, rows,channel);
}
double  IK_trackingUpdate( unsigned char* image, int cols, int rows, IK_Rect& roi)
{
    //cv::Mat matImage(rows,cols,  CV_8UC3, image);
    IK_Rect ROI;
    double score = g_tracker.update(image,rows,cols,3, ROI);//3通道
    roi = ROI;
    return score;
}


// Constructor
KCFTracker::KCFTracker(bool hog, bool fixed_window, bool multiscale, bool lab):m_hann(0),_alphaf(0),_prob(0),m_tmpl_szW(0),m_tmpl_szH(0),m_tmpl(0)
{

    // Parameters equal in all cases
    lambda = 0.0001;
    padding = 1.1;  //目标扩展出来的区域
    //output_sigma_factor = 0.1;
    output_sigma_factor = 0.125;


    if (hog) {    // HOG
        // VOT
        interp_factor = 0.012;
        sigma = 0.6;
        // TPAMI
        //interp_factor = 0.02;
        //sigma = 0.5; 
        cell_size = 3;
        _hogfeatures = true;
    }
    else {   // RAW
        interp_factor = 0.075;
        sigma = 0.2;
        cell_size = 3;
        _hogfeatures = false;
    }


    if (multiscale) { // multiscale
        template_size = 20;
        //template_size = 100;
        scale_step = 1.1f;
        scale_weight = 0.95;
        if (!fixed_window) {
            //printf("Multiscale does not support non-fixed window.\n");
            fixed_window = true;
        }
    }
    else if (fixed_window) {  // fit correction without multiscale
        template_size = 24;
        //template_size = 100;
        scale_step = 1;
    }

}
KCFTracker::~KCFTracker()
{
    if(_prob!=0)
    {
        delete _prob;
        _prob = 0;
    }
    if(_alphaf!=0)
    {
        delete _alphaf;
        _alphaf = 0;
    }
    delete m_hann;
    delete m_tmpl;
}
// Initialize tracker 
void KCFTracker::init(const IK_Rect &roi, unsigned char* image, int cols, int rows, int channel)
{
    delete _prob;
    _prob = 0;
    delete _alphaf;
    _alphaf = 0;
    delete m_hann;
    m_hann = 0;
    m_roi = roi;//cv::Rect(roi.m_x, roi.m_y, roi.m_width, roi.m_height);
    //cv::Mat ximage(rows, cols, CV_8UC3, image);
    delete m_tmpl;
    assert(m_roi.m_width >= 0 && m_roi.m_height >= 0);
    createFeatures(image, rows, cols, channel,  &m_tmpl,  m_templH, m_templW, 1,true, 1);
    _prob = new float[size_patch[0]*size_patch[1]*2];
    createGaussianPeak(size_patch[0], size_patch[1], _prob);
    //_alphaf = cv::Mat(size_patch[0], size_patch[1], CV_32FC2, float(0));
    _alphaf = new float[size_patch[0]*size_patch[1]*2];
    memset(_alphaf, 0x00, sizeof(float)*size_patch[0]*size_patch[1]*2);

    //单通道的特征图像
    train(m_tmpl, m_templH, m_templW, 1, 1.0); // train with initial frame
    //delete templ;
 }
// Update position based on the new frame
double KCFTracker::update(unsigned char* image, int rows, int cols, int channel, IK_Rect& roi)
{
    IK_Rect _roi(m_roi.m_x, m_roi.m_y, m_roi.m_width, m_roi.m_height);
    if (_roi.m_x + _roi.m_width <= 0) _roi.m_x = -_roi.m_width + 1;
    if (_roi.m_y + _roi.m_height <= 0) _roi.m_y = -_roi.m_height + 1;
    if (_roi.m_x >= cols - 1) _roi.m_x = cols - 2;
    if (_roi.m_y >= rows - 1) _roi.m_y = rows - 2;

    float cx = _roi.m_x + _roi.m_width / 2.0f;
    float cy = _roi.m_y + _roi.m_height / 2.0f;


    float peak_value;
    //cv::Mat templ(m_templH, m_templW,CV_32FC1,m_tmpl);
    float * tmpl=0;
    int templH=m_templH, templW=m_templW;
    createFeatures(image, rows, cols, channel,&tmpl, templH,templW, 1,  false, 1.0f);
    //cv::Mat templ2(templH, templW, CV_32FC1,tmpl);
    float X=0;
    float Y=0;
    peak_value = detect(m_tmpl , tmpl, templH, templW, 1,X,Y);
    delete tmpl;
    if (scale_step != 1) {
        // Test at a smaller _scale
        float * tmpl2 = 0;
        float newX=0;
        float newY=0;
        createFeatures(image, rows, cols, channel, &tmpl2, templH, templW, 1,false,  1.0f/scale_step);
        //templ2 = cv::Mat( templH,templW, CV_32FC1,tmpl2);
        double new_peak_value = detect(m_tmpl , tmpl2, templH, templW,1, newX, newY);
        delete tmpl2;
        if (scale_weight * new_peak_value > peak_value) {
            X = newX;
            Y = newY;
            peak_value = new_peak_value;
            _scale /= scale_step;
            _roi.m_width /= scale_step;
            _roi.m_height /= scale_step;
        }

        // Test at a bigger _scale
        //cv::Mat templ(TEMPLATES_SIZE,TEMPLATES_SIZE,CV_32FC1);
        float * tmpl3=0;
        createFeatures(image, rows, cols, channel, &tmpl3, templH, templW, 1, false, scale_step);
        //templ2 = cv::Mat(templH, templW, CV_32FC1,tmpl3);
        new_peak_value = detect(m_tmpl , tmpl3, templH,templW, 1,newX, newY);
        delete tmpl3;
        if (scale_weight * new_peak_value > peak_value) {
            X = newX;
            Y = newY;
            peak_value = new_peak_value;
            _scale *= scale_step;
            _roi.m_width *= scale_step;
            _roi.m_height *= scale_step;
        }
    }

    // Adjust by cell size and _scale
    _roi.m_x = cx - _roi.m_width / 2.0f + (X * cell_size * _scale);
    _roi.m_y = cy - _roi.m_height / 2.0f + (Y * cell_size * _scale);

    if (_roi.m_x >= cols - 1) _roi.m_x = cols - 1;
    if (_roi.m_y >= rows - 1) _roi.m_y = rows - 1;
    if (_roi.m_x + _roi.m_width <= 0) _roi.m_x = -_roi.m_width + 2;
    if (_roi.m_y + _roi.m_height <= 0) _roi.m_y = -_roi.m_height + 2;

    assert(_roi.m_width >= 0 && _roi.m_height >= 0);
    //cv::Mat templ(TEMPLATES_SIZE,TEMPLATES_SIZE,CV_32FC1);
    float * tmpl4 = 0;
    createFeatures(image, rows, cols, channel, &tmpl4, templH, templW, 1, false);
    //templ2 = cv::Mat(templH, templW, CV_32FC1,tmpl4);
    //cv::Mat x = getFeatures(image.data, image.rows, image.cols, image.channels(), 0);
    //train(templ2, interp_factor);
    train(tmpl4,templH, templW, 1, interp_factor);
    delete tmpl4;
	roi = _roi;
    //templ.release();
	return peak_value;
}

// Detect object in the current frame.
double KCFTracker::detect(float* srcZ, float* SrcX, int rows, int cols, int channel,  float& peak_x, float& peak_y)
{
    using namespace FFTTools;
    assert(size_patch[1]*size_patch[0]*7<30240);
    float dataMemory[30240];
    int pos = 0;
    float* kVal = dataMemory + pos;//float[size_patch[1]*size_patch[0]];
    pos += size_patch[1]*size_patch[0];
    float* fftK = dataMemory + pos;//float[size_patch[1]*size_patch[0]*2];//用来保存fft结果，双通道
    pos += size_patch[1]*size_patch[0]*2;
    float* KComplex = dataMemory + pos;//float[size_patch[1]*size_patch[0]*2];
    pos += size_patch[1]*size_patch[0]*2;
    float* fftKComplex = dataMemory + pos;//float[size_patch[1]*size_patch[0]*2];
    pos += size_patch[1]*size_patch[0]*2;
    //计算
    gaussianCorrelation(SrcX,srcZ, rows,cols,channel, kVal,size_patch[1], size_patch[0],1);
    fftd(kVal, size_patch[1], size_patch[0], 1, fftK);
    Matrix_complexMultiplication(_alphaf, fftK,KComplex, size_patch[1], size_patch[0], 2);
    fftd(KComplex,size_patch[1], size_patch[0], 2,fftKComplex,  true);

    //计算最佳位置
    int pX=0;
    int pY=0;
    float fpX=0;
    float fpY=0;
    double peak_value; //得分
    //求取实部
    float* real=0;
    float* imag=0;
    Matrix_imag(fftKComplex,&real,&imag, size_patch[1], size_patch[0], 2);

    // 计算最佳位置
    Matrix_MaxLoc(real, size_patch[1], size_patch[0], 1, peak_value, pX, pY);

    //计算亚像素的位置
    fpX = pX;
    fpY = pY;


    //minMaxLoc only accepts doubles for the peak, and integer points for the coordinates

    //subpixel peak estimation, coordinates will be non-integer

    if (pY > 0 && pY < size_patch[0]-1) {
        fpY += subPixelPeak(*(real + (pY-1)*size_patch[0] + pX), peak_value, *(real + (pY+1)*size_patch[0] + pX));
    }

    if (pX > 0 && pX < size_patch[1]-1) {
        fpX += subPixelPeak(*(real + (pY)*size_patch[1] + pX-1), peak_value, *(real + (pY)*size_patch[1] + pX+1));
    }


    fpX -= (size_patch[1]) / 2;
    fpY -= (size_patch[0]) / 2;

    //回收傅立叶FFT产生的内存
    delete real;
    delete imag;
    peak_x = fpX;
    peak_y = fpY;

    return peak_value;
}

// train tracker with a single image
void KCFTracker::train(float* srcImg, int rows, int cols, int channel, float train_interp_factor)
{
    using namespace FFTTools;
    //cv::Mat k = gaussianCorrelation(x, x);
    float* kVal = new float[size_patch[1]*size_patch[0]];
    float* fft = new float[size_patch[1]*size_patch[0]*2];//用来保存fft结果，双通道
    //cv::Mat k(size_patch[1], size_patch[0], CV_32FC1);
    gaussianCorrelation(srcImg,srcImg, rows,cols,channel, kVal,size_patch[1], size_patch[0],1);
    fftd(kVal, size_patch[1], size_patch[0], 1, fft);
    Matrix_Linner(fft, size_patch[1], size_patch[0], 2, lambda);
    //cv::Mat xx = (fft + lambda);
    float* alp = new float[size_patch[1]*size_patch[0]*2];
    //计算两个二维傅立叶除法
    Matrix_complexDivision(_prob,fft, alp, size_patch[1], size_patch[0],2);
    //float
//    cv::Mat alpM(size_patch[1], size_patch[0], CV_32FC2, alp);
//    cv::Mat alphaf = alpM.clone();


    float* tempAlp = new float[size_patch[1]*size_patch[0]*2];
    memcpy(tempAlp, _alphaf, sizeof(float)*size_patch[1]*size_patch[0]*2);
    //对_alphaf 和 alphaf 乘以系数
    Matrix_Linner(tempAlp,size_patch[1], size_patch[0],2, 0, (1 - train_interp_factor));
    Matrix_Linner(alp, size_patch[1], size_patch[0],2, 0, train_interp_factor);
    Matrix_Add(tempAlp,alp, _alphaf, size_patch[1], size_patch[0],2);
    //m_tmpl 的更新计算
    delete tempAlp;

    float* tempTmpl = new float[m_templH*m_templW];
    memcpy(tempTmpl, m_tmpl, sizeof(float)*m_templH*m_templW);
    //对_alphaf 和 alphaf 乘以系数
    Matrix_Linner(tempTmpl,m_templH, m_templW,1, 0, (1 - train_interp_factor));
    Matrix_Linner(srcImg, m_templH, m_templW,1, 0, train_interp_factor);
    Matrix_Add(tempTmpl,srcImg, m_tmpl, m_templH, m_templW,1);
    //m_tmpl 的更新计算
    delete tempTmpl;

//    cv::Mat tmp(m_templH,  m_templW, CV_32FC1, m_tmpl);
//    tmp = (1 - train_interp_factor) * tmp + (train_interp_factor) * x;
    //_alphaf = (1 - train_interp_factor) * _alphaf + (train_interp_factor) * alphaf;


    delete alp;
    delete fft;
    delete kVal;
    /*cv::Mat kf = fftd(gaussianCorrelation(x, x));
    cv::Mat num = complexMultiplication(kf, _prob);
    cv::Mat den = complexMultiplication(kf, kf + lambda);
    
    _tmpl = (1 - train_interp_factor) * _tmpl + (train_interp_factor) * x;
    _num = (1 - train_interp_factor) * _num + (train_interp_factor) * num;
    _den = (1 - train_interp_factor) * _den + (train_interp_factor) * den;

    _alphaf = complexDivision(_num, _den);*/

}

// 使用带宽SIGMA计算高斯卷积核以用于所有图像X和Y之间的相对位移
// 必须都是MxN大小。二者必须都是周期的（即，通过一个cos窗口进行预处理）
// Evaluates a Gaussian kernel with bandwidth SIGMA for all relative shifts between input images X and Y, which must both be MxN. They must    also be periodic (ie., pre-processed with a cosine window).
void KCFTracker::gaussianCorrelation(float* src1, float* src2, int srcRows, int srcCols, int srcChannel, float* dst, int dstRows, int dstCols, int dstChannel)
//cv::Mat KCFTracker::gaussianCorrelation(cv::Mat x1, cv::Mat x2)
{
    using namespace FFTTools;
    float dataMemory[202400]={0};
    int pos=0;
    //cv::Mat c = cv::Mat( cv::Size(dstRows, dstCols), CV_32F, cv::Scalar(0) );
    float* cMat;
    cMat = dataMemory + pos;
    pos += dstRows* dstCols;
    //memset(cMat, 0x00, sizeof(float)*dstRows* dstCols);
    // HOG features
    if (_hogfeatures) {
        int auxW = size_patch[0];
        int auxH = size_patch[1];

        float* x1aux = dataMemory + pos;
        pos += auxW*auxH;
        float* x2aux = dataMemory + pos;
        pos += auxW*auxH;
        float* caux = dataMemory + pos;
        pos += auxW*auxH*2;
        float* x1auxFFt = dataMemory + pos;
        pos += auxW*auxH*2;
        float* x2auxFFt = dataMemory + pos;
        pos += auxW*auxH*2;
        float* cauxM = dataMemory + pos;
        pos += auxW*auxH*2;


        //real 和 imag两个通道
        for (int i = 0; i < size_patch[2]; i++) {
            memcpy(x1aux, src1 + i*srcCols*srcChannel, auxW*auxH*sizeof(float));
            memcpy(x2aux, src2 + i*srcCols*srcChannel, auxW*auxH*sizeof(float));
            //计算傅立叶变换
            fftd(x1aux, auxH, auxW,1, x1auxFFt);
            fftd(x2aux, auxH, auxW,1, x2auxFFt);

            //计算互功率谱的分子部分，即公式3中的分子，其中P为输出结果，true表示的是对FF2取共轭，所以得到的结果为：P=FFT1×FFT2*，mulSpectrums函数为通用函数
            //mulSpectrums((float*)fftX1.data, (float*)fftX2.data, caux, auxH, auxW, 2);
            mulSpectrums(x1auxFFt, x2auxFFt, caux, auxH, auxW, 2);
            fftd(caux,auxH, auxW,2, cauxM, true);
            //cv::imshow("b", caux);
            //对角线分割交换，使峰值点移到中心
            IK_rearrange(cauxM, auxH, auxW, 2);
            //rearrange(caux);
            //cauxM.convertTo(cauxM,CV_32F);
            float* mReal=0;
            float* mImag=0;
            Matrix_imag(cauxM, &mReal, &mImag, auxH, auxW, 2);
            //cv::Mat mm = cv::Mat( auxH, auxW, CV_32FC1, Mreal );
            //C与实部累积求和
            Matrix_Add(cMat, mReal,cMat, auxH, auxW,1);
            delete mReal;
            delete mImag;
        }
    }
    // Gray features
    else {
        int auxW = size_patch[1];
        int auxH = size_patch[0];

        float* x1FFt = dataMemory + pos;
        pos += auxW*auxH*2;
        float* x2FFt = dataMemory + pos;
        pos += auxW*auxH*2;
        float* caux = dataMemory + pos;
        pos += auxW*auxH*2;
        float* cauxM = dataMemory + pos;
        pos += auxW*auxH*2;
        fftd(src1, srcRows, srcCols, srcChannel,x1FFt, false);
        fftd(src2, srcRows, srcCols, srcChannel,x2FFt, false);
        //计算互功率谱的分子部分，即公式3中的分子，其中P为输出结果，true表示的是对FF2取共轭，所以得到的结果为：P=FFT1×FFT2*，mulSpectrums函数为通用函数
        mulSpectrums(x1FFt, x2FFt, caux, auxH, auxW, 2);

        fftd(caux,auxH, auxW,2, cauxM, true);
        //cv::imshow("b", caux);
        //对角线分割交换，使峰值点移到中心
        IK_rearrange(cauxM, auxH, auxW, 2);
        //rearrange(caux);
        //cauxM.convertTo(cauxM,CV_32F);
        float* mReal=0;
        float* mImag=0;
        Matrix_imag(cauxM, &mReal, &mImag, auxH, auxW, 2);
        //cv::Mat mm = cv::Mat( auxH, auxW, CV_32FC1, Mreal );
        //实部赋值给cMat
        memcpy(cMat, mReal, sizeof(float)*auxH*auxW);
        delete mReal;
        delete mImag;
    }
    //int x=x1.channels();
    float* d = dataMemory + pos;//new float[dstRows*dstCols];
    pos += dstRows*dstCols;
    //cv::Mat d(size_patch[1], size_patch[0], CV_32FC1);
    float* x1Mul = dataMemory + pos;//new float[srcRows*srcCols];
    pos += srcRows*srcCols;
    float* x2Mul = dataMemory + pos;//new float[srcRows*srcCols];
    pos += srcRows*srcCols;
    Matrix_Mul(src1, srcRows, srcCols, src1, srcRows, srcCols, x1Mul);
    Matrix_Mul(src2, srcRows, srcCols, src2, srcRows, srcCols, x2Mul);
    //对x1 mul x1后的矩阵求累积和
    double value1[1]={0};
    double value2[1]={0};
    Matrix_Sum(x1Mul, value1, srcRows, srcCols, 1);
    Matrix_Sum(x2Mul, value2, srcRows, srcCols, 1);

    //线性运算
    Matrix_Linner(cMat, dstRows, dstCols, 1, value1[0] + value2[0], -2.0f);
    Matrix_Linner(cMat, dstRows, dstCols, 1, 0, 1.0f/(size_patch[0]*size_patch[1]*size_patch[2]));

    //与0阵求最大值矩阵
    float* zero = dataMemory + pos;//new float[dstRows*dstCols];
    memset(zero, 0x00, sizeof(float)*dstRows* dstCols);
    pos += dstRows*dstCols;
    Matrix_Max(cMat, zero, d, dstRows, dstCols, 1);
    //cv::max(c , 0, d);

    //sigma的线性运算
    Matrix_Linner(d, dstRows, dstCols,1, 0, -1.0f/(sigma*sigma));
    //指数运算 dst(I)=EXP(src(I))。以自然数底数e为底的指数
    Matrix_EXP(d,  dstRows, dstCols,1);
    memcpy(dst, d, sizeof(float)*dstRows*dstCols);

}

// Create Gaussian Peak. Function called only in the first frame.
///
/// \brief KCFTracker::createGaussianPeak
/// \param sizey
/// \param sizex
/// \param res
/// \return
///宽为 sizex 高为 sizey
void KCFTracker::createGaussianPeak(int sizey, int sizex, float* resDst)
{
    //cv::Mat_<float> res(sizey, sizex);
    float* res = new float[sizey*sizex];
    memset(res, 0x00, sizeof(float)*sizey*sizex);
    int syh = (sizey) / 2;
    int sxh = (sizex) / 2;

    float output_sigma = std::sqrt((float) sizex * sizey) / padding * output_sigma_factor;
    float mult = -0.5 / (output_sigma * output_sigma);

    for (int i = 0; i < sizey; i++)
    {
        float* resW = res + i*sizex;
        for (int j = 0; j < sizex; j++)
        {
            int ih = i - syh;
            int jh = j - sxh;
            *(resW + j) = std::exp(mult * (float) (ih * ih + jh * jh));
        }
    }

    FFTTools::fftd(res, sizey, sizex, 1, resDst, false);
    delete res;
//    cv::Mat resMat = FFTTools::fftd((float*)res.data, res.rows, res.cols, res.channels(), false);
//    return resMat.clone();
}

// Obtain sub-window from image, with replication-padding and extract features
int KCFTracker::createFeatures(const unsigned char* image, int imH, int imW, int channel, float** templ, int& TemplH, int& TemplW, int templChannel, bool init,  float scale_adjust)
{
    //assert(subWinHeight*subWinWidth*channel*5<102400);
    float dataMemory[102400]={0};
    int pos = 0;
    //float template_size = getTemplH;
    IK_Rect extracted_roi;
    IK_Rect tRoi(m_roi);
    float cx = tRoi.m_x + tRoi.m_width / 2;
    float cy = tRoi.m_y + tRoi.m_height / 2;

    //判断ROI 初始化各种参数
    if (init) {
        int padded_w = tRoi.m_width * padding;
        int padded_h = tRoi.m_height * padding;

        if (template_size > 1) {  // Fit largest dimension to the given template size
            if (padded_w >= padded_h)  //fit to width
                _scale = padded_w / (float) template_size;
            else
                _scale = padded_h / (float) template_size;

            m_tmpl_szW = template_size;//padded_w / template_size;
            m_tmpl_szH = template_size;//padded_h / template_size;
        }
        else {  //No template size given, use ROI size
            m_tmpl_szW = padded_w;
            m_tmpl_szH = padded_h;
            _scale = 1;

        }

        if (_hogfeatures) {
            // Round to cell size and also make it even
            m_tmpl_szW = ( ( (int)(m_tmpl_szW / (2 * cell_size)) ) * 2 * cell_size ) + cell_size*2;
            m_tmpl_szH = ( ( (int)(m_tmpl_szH / (2 * cell_size)) ) * 2 * cell_size ) + cell_size*2;
        }
        else {  //Make number of pixels even (helps with some logic involving half-dimensions)
            m_tmpl_szW = (m_tmpl_szW / 2) * 2;
            m_tmpl_szH = (m_tmpl_szH / 2) * 2;
        }
    }
    //模板size
    int t_templH = m_tmpl_szH;
    int t_templW = m_tmpl_szW;

    extracted_roi.m_width = scale_adjust * _scale * m_tmpl_szW;
    extracted_roi.m_height = scale_adjust * _scale * m_tmpl_szH;

    // center roi with new size
    extracted_roi.m_x = cx - extracted_roi.m_width / 2;
    extracted_roi.m_y = cy - extracted_roi.m_height / 2;

    int subWinHeight = extracted_roi.m_height;
    int subWinWidth = extracted_roi.m_width;

    //cv::Mat FeaturesMap(t_templW, t_templH, CV_32F);
    //cv::Mat z(extracted_roi.m_height, extracted_roi.m_width, image.type());
    float* FeaturesMap = 0;
    unsigned char* subWin = new unsigned char[subWinHeight*subWinWidth*channel];
    //pos += subWinHeight*subWinWidth*channel;
    memset(subWin, 0x00, sizeof(unsigned char)*subWinHeight*subWinWidth*channel);

    unsigned char* tmplWin = new unsigned char[t_templW*t_templH*channel];
    memset(tmplWin, 0x00, sizeof(unsigned char)*t_templW*t_templH*channel);
    //pos += t_templW*t_templH*channel;
    dipImCrop(image, imH, imW, channel, extracted_roi.m_y, extracted_roi.m_x, subWin, subWinHeight, subWinWidth, channel);
    if (extracted_roi.m_width != t_templW || extracted_roi.m_height != t_templH) {
        resize_bilinear(subWin, subWinWidth, subWinHeight, channel, tmplWin, t_templW, t_templH, channel);
        //cv::resize(z, z, _tmpl_sz);
    }   
    //cv::Mat z(tmplHeight, tmplWidth,CV_8UC3, tmplWin);
    delete subWin;
    // HOG features
    if (_hogfeatures) {
        //static timeElapsed hogT;
        //hogT.startTime();
        CvLSVMFeatureMapCaskade *map;
        getFeatureMaps(tmplWin,t_templH, t_templW, channel, cell_size, &map);
        normalizeAndTruncate(map,0.2f);
        PCAFeatureMaps(map);
        size_patch[0] = map->sizeY;
        size_patch[1] = map->sizeX;
        size_patch[2] = map->numFeatures;

        //特征赋值
        TemplH = size_patch[2];
        TemplW = size_patch[0]*size_patch[1];
        FeaturesMap = dataMemory + pos;//new float[TemplW*TemplH];
        pos += TemplW*TemplH;
        Matrix_Trans(map->map, map->sizeX*map->sizeY, map->numFeatures, FeaturesMap);
        //free  map
        freeFeatureMapObject(&map);
        //std::cout<<"hog t:"<<hogT.avgTime()<<std::endl;
    }
    else {
        size_patch[0] = m_tmpl_szH;
        size_patch[1] = m_tmpl_szW;
        size_patch[2] = 1;  
        TemplH = size_patch[0];
        TemplW = size_patch[1];
        //转成 float 且灰度
        float* map = dataMemory + pos;//new float[TemplH*TemplW];
        pos += TemplH*TemplW;
        RGB2GrayFloat(tmplWin, map, TemplH,TemplW, channel, 0.5f);

        FeaturesMap = dataMemory + pos;//new float[TemplW*TemplH];
        pos += TemplW*TemplH;
        memcpy(FeaturesMap, map, sizeof(float)*TemplH*TemplW);
        //std::cout<<"nohog t:"<<nohogT.avgTime()<<std::endl;
        //delete map;
    }
    
    if (init) {
        createHanningMats();
    }
    //汉宁窗与map相乘得到特征
    Matrix_Mul(m_hann, m_hannW, m_hannH, FeaturesMap, TemplW, TemplH, FeaturesMap);
    *templ = new float[TemplH*TemplW];
    memcpy(*templ, FeaturesMap, sizeof(float)*TemplH*TemplW*templChannel);
//    delete FeaturesMap;
    delete tmplWin;
    return 0;
}
    
// Initialize Hanning window. Function called only in the first frame.
void KCFTracker::createHanningMats()
{   
    float dataMemory[102400]={0};
    int pos =0;


    float* hann1t = dataMemory + pos;    //1*size_patch[1]
    pos += size_patch[1];
    float* hann2t = dataMemory + pos;     //size_patch[0]*1
    pos += size_patch[0];

    for (int i = 0; i < size_patch[1]; i++)
        hann1t[i] = 0.5 * (1 - std::cos(2 * 3.14159265358979323846 * i / (size_patch[1] - 1)));
    for (int i = 0; i < size_patch[0]; i++)
        hann2t[i] = 0.5 * (1 - std::cos(2 * 3.14159265358979323846 * i / (size_patch[0] - 1)));

    float* hann2d = dataMemory + pos; //[size_patch[1]*size_patch[0]];
    pos += size_patch[1]*size_patch[0];
    //multi
    Matrix_StarMul(hann2t,size_patch[0], hann1t, size_patch[1], 1, hann2d);

    // HOG features
    if (_hogfeatures) {

        m_hannW = size_patch[0]*size_patch[1];
        m_hannH = size_patch[2];
        m_hann = new float[m_hannW*m_hannH];//width  size_patch[0]*size_patch[1], height size_patch[2]
        //memset(m_hann, 0x00, sizeof(float)*m_hannW*m_hannH);
        //pos += m_hannW*m_hannH;
        for (int i = 0; i < m_hannH; i++) {
            float* hannW = m_hann + i*m_hannW;
            for (int j = 0; j<m_hannW; j++) {
                *(hannW + j) = hann2d[j];//hann1d.at<float>(0,j);
            }
        }
    }else {
      // Gray features
      if(m_hann!=0)
      {
          delete m_hann;
          m_hann = 0;
      }
      m_hannW = size_patch[0];
      m_hannH = size_patch[1];
      m_hann = new float[m_hannW*m_hannH];
      pos += m_hannW*m_hannH;
      memcpy(m_hann, hann2d, sizeof(float)*m_hannW*m_hannH);
    }
}

// Calculate sub-pixel peak for one dimension
float KCFTracker::subPixelPeak(float left, float center, float right)
{   
    float divisor = 2 * center - right - left;

    if (divisor == 0)
        return 0;
    
    return 0.5 * (right - left) / divisor;
}

//#include <imdebug.h>
int dipImCrop(const unsigned char *srcIm, int srcImH, int srcImW, int srcChannel, int startR, int startC, unsigned char *objIm, int objImH, int objImW,int dstChannel)
{
    assert(srcChannel>0);
    if ((startR >= srcImH) || (startR + objImH < 0) || (startC >= srcImW) || (startC + objImW < 0) || srcChannel!=dstChannel )
    {
        return  -1;
    }
    //求两个矩形交集
    int AdjustLeft = (std::max)(0, startC);
    int AdjustRight = (std::min)(srcImW, startC + objImW);
    int AdjustTop = (std::max)(0, startR);
    int AdjustBottom = (std::min)(srcImH, startR + objImH);
    int AdjustWidth = AdjustRight<AdjustLeft?0:(AdjustRight - AdjustLeft);
    int AdjustHeight = AdjustBottom<AdjustTop?0:(AdjustBottom - AdjustTop);
    //起始点偏移
    int offsetObjR = startR<0?(-startR):0;
    int offsetObjC = startC<0?(-startC):0;

    //计算crop的起始位置
    unsigned char* objImData = objIm+ offsetObjR*objImW*srcChannel ;
    unsigned char* data = (unsigned char*)(srcIm + srcImW*AdjustTop*srcChannel);
    //imdebug("rgb w=%d h=%d %p", srcImW, srcImH, srcIm);
    //行遍历
    for(int i=0; i< AdjustHeight; i++)
    {
        unsigned int len = (objImW-offsetObjC)*dstChannel*sizeof(unsigned char);
        memcpy(objImData+dstChannel*(i*objImW+ offsetObjC), data+AdjustLeft*srcChannel, AdjustWidth*srcChannel);
        data+=srcImW*srcChannel;
    }

    unsigned char* objImDataSrc = objIm;

    if(1==srcChannel)
    {
        //左右边界填充
        for(int i=0; i<objImH; i++)
        {
            memset(objImDataSrc+i*objImW*srcChannel, *(objIm+(offsetObjC+i*objImW)*dstChannel), sizeof(unsigned char)*offsetObjC*srcChannel);
            memset(objImDataSrc+(i*objImW + AdjustWidth+offsetObjC)*srcChannel, *(objIm+(offsetObjC+i*objImW + AdjustWidth-1)*dstChannel), sizeof(unsigned char)*(objImW-offsetObjC-AdjustWidth)*dstChannel);
        }
    }else{
        //多通道情况
        for(int i=offsetObjR; i<offsetObjR+AdjustHeight; i++) //高度
        {
            unsigned char* LeftW = objImDataSrc + i*objImW*srcChannel;
//            //左
            for(int j=0; j<offsetObjC; j++)
            {
                for(int k=0; k<srcChannel; k++)
                {
                    *(LeftW +j*srcChannel + k) = *(LeftW +(offsetObjC)*srcChannel + k);
                }
            }
            //右
            for(int j=AdjustWidth+offsetObjC; j<objImW; j++)
            {
                for(int k=0; k<srcChannel; k++)
                {
                    *(LeftW +j*srcChannel + k) = *(LeftW +(AdjustWidth+offsetObjC-1)*srcChannel + k);
                }
            }
        }

    }

    //上边界填充
    for(int i=0; i<offsetObjC; i++)
    {
        memcpy(objImDataSrc+i*objImW*srcChannel, objImDataSrc+(offsetObjC)*objImW*srcChannel, sizeof(unsigned char)*objImW*srcChannel);
    }

    //下边界填充
    for(int i=offsetObjR+AdjustHeight; i<objImH; i++)
    {
        memcpy(objImDataSrc+i*objImW*srcChannel, objImDataSrc+(offsetObjR+AdjustHeight-1)*objImW*srcChannel, sizeof(unsigned char)*objImW*srcChannel);
    }

    return 0;
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_StarMul(float *Mul1, int Mul1_m, float *Mul2, int Mul2_n, int nm, float *Mul)
{
    //Mul1[Mul1_m][nm]*Mul2[nm][Mul2_n]=Mul即矩阵的乘法
    int i, j, k, a, b, c, d;
    for (i = 0, a = 0, c = 0; i<Mul1_m; i++)
    {
        for (j = 0; j<Mul2_n; j++)
        {
            b = a + j;
            Mul[b] = 0;
            for (k = 0, d = 0; k<nm; k++)
            {
                Mul[b] += Mul1[c + k] * Mul2[d + j];
                d += Mul2_n;
            }
        }
        c += nm;
        a += Mul2_n;
    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_Add(float *Mul1, float *Mul2, float* dst, int rows, int cols, int channel)
{
    //dst[cols][rows] = Mul1[Mul1_m][nm]+Mul2[nm][Mul2_n]矩阵的加法
    for (int i = 0; i<rows; i++)
    {
        float* Mul1W = Mul1 + i*cols*channel;
        float* Mul2W = Mul2 + i*cols*channel;
        float* dstW = dst + i*cols*channel;
        for (int j = 0; j<cols; j++)
        {
            float* Mul1WC = Mul1W + j*channel;
            float* Mul2WC = Mul2W + j*channel;
            float* dstWC = dstW + j*channel;
            for (int k = 0; k<channel; k++)
            {
                *(dstWC + k) = *(Mul1WC + k) + *(Mul2WC + k);
            }
        }
    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的转置
////////
void Matrix_Trans(float *Mul1, int Mul1_m, int Mul1_n, float *Mul)
{
    //Mul1[Mul1_m][Mul1_n]  transpose  Nul[Mul1_n][Mul1_m]
    for(int i=0; i< Mul1_m; i++)
    {
        float* Mul1W = Mul1 + i*Mul1_n;
        for(int j=0; j<Mul1_n; j++)
        {
            *(Mul+j*Mul1_m + i) = *(Mul1W +j);
        }
    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_Mul(float *Mul1, int Mul1_m, int Mul1_n, float *Mul2, int Mul2_m, int Mul2_n, float *Mul)
{
    assert(Mul1_m==Mul2_m && Mul1_n==Mul2_n);
    for(int i=0; i<Mul1_m; i++)
    {
        float* MulW = Mul + i*Mul1_n;
        float* Mul1W = Mul1 + i*Mul1_n;
        float* Mul2W = Mul2 + i*Mul1_n;
        for(int j=0; j<Mul1_n; j++)
        {
            MulW[j] = Mul1W[j]*Mul2W[j];
        }

    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 分离复数矩阵  实部第一通道，虚部第二通道
////////
void Matrix_imag(float *Mul, float** real, float** imag, int rows, int cols, int channel)
{
    assert(channel==2);
    *real = new float[rows*cols];
    *imag = new float[rows*cols];
    for(int i=0; i<rows; i++)
    {
        float* MulW = Mul + i*cols*channel;
        float* realW = *real + i*cols;
        float* imagW = *imag + i*cols;
        for(int j=0; j<cols; j++)
        {
            *(realW + j) = *(MulW + j*channel);
            *(imagW + j) = *(MulW + j*channel + 1);
        }

    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵累加和 多通道分别求和
////////
void Matrix_Sum(float *Mul, double* Val, int rows, int cols, int channel)
{
    for(int i=0; i<rows; i++)
    {
        float* MulW = Mul + i*cols*channel;
        for(int j=0; j<cols; j++)
        {
            for(int k=0; k<channel; k++)
            {
                Val[k] += *(MulW + j*channel +k);
            }
        }

    }
}

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的卷积
////////
int IK_conv(unsigned char *Mul1, int Mul1_cols, int Mul1_rows, int channel, float *Mul2, int Mul2_cols, int Mul2_rows, float* value)
{
    assert(Mul1_cols==Mul2_cols && Mul1_rows==Mul2_rows);
    //Mul1[Mul1_m][Mul1_n]*Mul2[Mul2_m][Mul2_n]=Mul即矩阵的乘法

    for (int k =0; k<channel; k++)
    {
        float sum=0;
        for(int i=0; i< Mul1_rows; i++)
        {
            for(int j=0; j<Mul1_cols; j++)
            {
                int data = Mul1[(i*Mul1_cols +j)*channel + k];
                float data2 = Mul2[(i*Mul1_cols +j)];
                sum +=  data*data2 ;
            }
        }
        value[k] = sum;///(Mul1_rows*Mul1_cols);
    }
    return 0;
}

int IK_filterConv(unsigned char* srcDstIm, int srcImH, int srcImW, int srcChannel, float* kernel, int kernelH, int kernelW, float* dstIm)
{
    unsigned char* win = new unsigned char[kernelW*kernelH*srcChannel];
    memset(win, 0x00, sizeof(unsigned char)*kernelW*kernelH*srcChannel);
    float* dstF = new float[sizeof(float)*srcImH*srcImW*srcChannel];
    memset(dstF, 0x00, sizeof(float)*srcImH*srcImW*srcChannel);
    float* conValue = new float[srcChannel];
    for(int i=0; i<srcImH; i++)
    {
        float* dataH = dstF + i*srcImW*srcChannel;
        for(int j=0; j<srcImW; j++)
        {
            //unsigned char* dataW = dataH +j*srcChannel;
            memset(conValue, 0x00, sizeof(float)*srcChannel);
            dipImCrop(srcDstIm, srcImH, srcImW, srcChannel, i-kernelW/2,j-kernelH/2,win,  kernelH, kernelW, srcChannel);

            IK_conv(win, kernelW, kernelH, srcChannel, kernel, kernelW, kernelH,conValue);
            memcpy(dataH +j*srcChannel, conValue, srcChannel*sizeof(float));
        }
    }
    delete conValue;
    delete win;
    memcpy(dstIm, dstF, sizeof(float)*srcImH*srcImW*srcChannel);
    delete dstF;
    return 0;
}


void RGB2XYZ(float R, float G, float B, float *X, float *Y, float *Z)
{
    *X = 0.412453f * R + 0.357580f * G + 0.180423f * B;
    *Y = 0.212671f * R + 0.715160f * G + 0.072169f * B;
    *Z = 0.019334f * R + 0.119193f * G + 0.950227f * B;
}

void XYZ2Lab(float X, float Y, float Z, float *L, float *a, float *b)
{
    float fX, fY, fZ;

    X /= Xn;
    Y /= Yn;
    Z /= Zn;

    if (Y > 0.008856f)
        fY = pow(Y, param_13);
    else
        fY = 7.787f * Y + param_16116;

    *L = 116.0f * fY - 16.0f;
    *L = *L > 0.0f ? *L : 0.0f;

    if (X > 0.008856f)
        fX = pow(X, param_13);
    else
        fX = 7.787f * X + param_16116;

    if (Z > 0.008856)
        fZ = pow(Z, param_13);
    else
        fZ = 7.787f * Z + param_16116;

    *a = 500.0f * (fX - fY);
    *b = 200.0f * (fY - fZ);
}

void RGB2Lab(float R, float G, float B, float *L, float *a, float *b)
{
    float X = 0.0f, Y = 0.0f, Z = 0.0f;
    RGB2XYZ(R, G, B, &X, &Y, &Z);
    XYZ2Lab(X, Y, Z, L, a, b);
}

void IK_RGBImage2Lab(unsigned char* srcDstIm, int srcImH, int srcImW, int srcChannel)
{
    assert(srcChannel==3);
    unsigned char* dstIm = new unsigned char[srcImH*srcImW*srcChannel*sizeof(unsigned char)];
    memset(dstIm, 0x00, srcImH*srcImW*srcChannel*sizeof(unsigned char));
    for(int i=0; i< srcImH; i++)
    {
        unsigned char* srcDataW = srcDstIm + i*srcImW*srcChannel;
        unsigned char* dstImW = dstIm + i*srcImW*srcChannel;
        for(int j=0; j<srcImW; j++)
        {
            float B = (float)(*(srcDataW + j*srcChannel));
            float G = float (*(srcDataW + j*srcChannel + 1));
            float R = float(*(srcDataW + j*srcChannel + 2));
            float L=0, a=0, b=0;
            //进行转换
            RGB2Lab(R, G, B, &L, &a, &b);
            *(dstImW + j*srcChannel) = L;
            *(dstImW + j*srcChannel + 1) = a;
            *(dstImW + j*srcChannel + 2) = b;
        }
    }
    memcpy(srcDstIm, dstIm, srcImH*srcImW*srcChannel*sizeof(unsigned char));
    delete dstIm;
}

//resize function
int resize_bilinear(const unsigned char* srcData, int srcW, int srcH, int srcChannels, unsigned char* dstData, int dstW, int dstH, int dstChannels)
{
    std::vector<int> tabsx(dstH);
    std::vector<int> tabsy(dstW);
    std::vector<float> tabrx(dstH);
    std::vector<float> tabry(dstW);

    const float fx = (float)(dstH) / srcH;
    const float fy = (float)(dstW) / srcW;
    const float ifx = 1.f / fx;
    const float ify = 1.f / fy;
    for (int dx = 0; dx < dstH; ++dx)
    {
        float rx = (dx + 0.5f) * ifx - 0.5f;
        int sx = (int)floor(rx);
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
        int sy = (int)floor(ry);
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
                float res = rx * (pc11[c] * ry + pc10[c] * iry) + irx * (pc01[c] * ry + pc00[c] * iry);
                pcdst[c] = res;
            }
        }
    }
    return 0;
}


//转灰度
int RGB2GrayFloat(unsigned char* srcIm, float* dstIm, int ImH, int ImW, int srcChannel, float sub)
{
    assert(srcChannel==3);
    for(int i=0; i< ImH; i++)
    {
        unsigned char* srcImW = srcIm + i*ImW*srcChannel;
        float* dstImW = dstIm + i*ImW;
        for(int j=0; j<ImW; j++)
        {
            unsigned char B = *(srcImW + j*srcChannel);
            unsigned char G = *(srcImW + j*srcChannel + 1);
            unsigned char R = *(srcImW + j*srcChannel + 2);
            //*(dstImW+ j) = (R*30 + G*59 + B*11 + 50) / 100.0f;
             *(dstImW+ j) = (R*0.299f + G*0.587f + B*0.114f)/255.0f - sub;
        }
    }
    return 0;
}
