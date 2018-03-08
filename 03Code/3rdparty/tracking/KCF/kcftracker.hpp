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
    padding: horizontal area surrounding the target, relative to its size
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
 */

#pragma once

#include "tracker.h"
#ifndef _OPENCV_KCFTRACKER_HPP_
#define _OPENCV_KCFTRACKER_HPP_
#endif
#define  TEMPLATES_SIZE 96

class KCFTracker
{
public:
    // Constructor
    KCFTracker(bool hog = true, bool fixed_window = true, bool multiscale = true, bool lab = true);
    ~KCFTracker();
    // Initialize tracker 
    virtual void init(const IK_Rect &roi, unsigned char* image, int cols, int rows, int channel);
    
    // Update position based on the new frame
    //virtual double update(cv::Mat image, cv::Rect& roi);
    double update(unsigned char* image, int rows, int cols, int channel, IK_Rect& roi);
    float interp_factor; // linear interpolation factor for adaptation
    float sigma; // gaussian kernel bandwidth
    float lambda; // regularization
    int cell_size; // HOG cell size
    int cell_sizeQ; // cell size^2, to avoid repeated operations
    float padding; // extra area surrounding the target
    float output_sigma_factor; // bandwidth of gaussian target
    int template_size; // template size
    float scale_step; // scale step for multi-scale estimation
    float scale_weight;  // to downweight detection scores of other scales for added stability

protected:
    // Detect object in the current frame.

    // Detect object in the current frame.
    double detect(float* srcZ, float* SrcX, int rows, int cols, int channel,  float& peak_x, float& peak_y);
    // train tracker with a single image
    void train(float* srcImg, int rows, int cols, int channel, float train_interp_factor);

    // Evaluates a Gaussian kernel with bandwidth SIGMA for all relative shifts between input images X and Y, which must both be MxN. They must    also be periodic (ie., pre-processed with a cosine window).
    //cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);
    void gaussianCorrelation(float* src1, float* src2, int srcRows, int srcCols, int srcChannel, float* dst, int dstRows, int dstCols, int dstChannel);
    // Create Gaussian Peak. Function called only in the first frame.
    ///
    /// \brief KCFTracker::createGaussianPeak
    /// \param sizey
    /// \param sizex
    /// \param res
    /// \return
    ///宽为 sizex 高为 sizey
    void createGaussianPeak(int sizey, int sizex, float* resDst);

    int getTmplSize(int& tmplHeight, int& tmplWidth, int& subWinHeight, int& subWinWidth, int templateSize, bool inithann, float scale_adjust);
    // Obtain sub-window from image, with replication-padding and extract features
    int createFeatures(const unsigned char* image, int imH, int imW, int channel, float** templ, int& getTemplH, int& getTemplW, int templChannel, bool init, float scale_adjust=1.0f);
    // Initialize Hanning window. Function called only in the first frame.
    void createHanningMats();

    // Calculate sub-pixel peak for one dimension
    float subPixelPeak(float left, float center, float right);

    //cv::Mat _alphaf;
    float* _alphaf;//宽高为 size_patch[1]， size_patch[0], 2个通道;
    //cv::Mat _prob;
    float* _prob;

private:
    int size_patch[3];

    //cv::Mat hann;
    float* m_hann;
    int m_hannW;
    int m_hannH;
    float* m_tmpl;
    int m_templW;
    int m_templH;
    int m_tmpl_szW;
    int m_tmpl_szH;
    float _scale;
    int _gaussian_size;
    bool _hogfeatures;
    IK_Rect m_roi;
};

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的转置
////////
void Matrix_Trans(float *Mul1, int Mul1_m, int Mul1_n, float *Mul);

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_Mul(float *Mul1, int Mul1_m, int Mul1_n, float *Mul2, int Mul2_m, int Mul2_n, float *Mul);

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_Add(float *Mul1Dst, float *Mul2,  float* dst, int rows, int cols, int channel);

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵累加和 多通道分别求和
////////
void Matrix_Sum(float *Mul, double* Val, int rows, int cols, int channel);

//矩阵的乘法
void Matrix_StarMul(float *Mul1, int Mul1_m, float *Mul2, int Mul2_n, int nm, float *Mul);

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 分离复数矩阵  实部第一通道，虚部第二通道
////////
void Matrix_imag(float *Mul, float** real, float** imag, int rows, int cols, int channel);

///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的卷积
////////
int IK_conv(unsigned char *Mul1, int Mul1_cols, int Mul1_rows, int channel, float *Mul2, int Mul2_cols, int Mul2_rows, float* value);
//crop抠图+扩展
int dipImCrop(const unsigned char *srcIm, int srcImH, int srcImW, int srcChannel, int startR, int startC, unsigned char *objIm, int objImH, int objImW,int dstChannel);
//二维卷积滤波
int IK_filterConv(unsigned char* srcDstIm, int srcImH, int srcImW, int srcChannel, float* kernel, int kernelH, int kernelW, float* dstIm);
//RGB转xyz
void RGB2XYZ(float R, float G, float B, float *X, float *Y, float *Z);
//xyz转lab
void XYZ2Lab(float X, float Y, float Z, float *L, float *a, float *b);
//rgb转lab
void RGB2Lab(float R, float G, float B, float *L, float *a, float *b);
//图像进行色彩空间转换
void IK_RGBImage2Lab(unsigned char* srcDstIm, int srcImH, int srcImW, int srcChannel);
//resize function
int resize_bilinear(const unsigned char* srcData, int srcW, int srcH, int srcChannels, unsigned char* dstData, int dstW, int dstH, int dstChannels);
//转灰度
int RGB2GrayFloat(unsigned char* srcIm, float* dstIm, int ImH, int ImW, int srcChannel, float sub=0 );

//传入图像感兴趣区域，图像数据，宽，高，通道数
void IK_trackingInit(const IK_Rect &roi, unsigned char* image, int cols, int rows,int channel);
double  IK_trackingUpdate( unsigned char* image, int cols, int rows, IK_Rect& roi);
