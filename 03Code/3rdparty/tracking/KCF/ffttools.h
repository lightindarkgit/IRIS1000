/* 
Author: Christian Bailer
Contact address: Christian.Bailer@dfki.de 
Department Augmented Vision DFKI 

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

#ifndef _OPENCV_FFTTOOLS_HPP_
#define _OPENCV_FFTTOOLS_HPP_
#endif
//#include <api/fftw3.h>
#include <complex>
#include <assert.h>
#include <string.h>
#define eps 1e-6
#define PI 3.14159265354
//NOTE: FFTW support is still shaky, disabled for now.
/*#ifdef USE_FFTW
#include <fftw3.h>
#endif*/
//typedef std::complex<double> complex_t;

namespace FFTTools
{
// Previous declarations, to avoid warnings
void fftd(float* srcImg, int srcH, int srcW, int srcChnnel, float* dstImg, bool backwards=false);


//计算互功率谱的分子部分，即公式3中的分子，其中P为输出结果，true表示的是对FF2取共轭，所以得到的结果为：P=FFT1×FFT2*，mulSpectrums函数为通用函数
///
/// \brief mulSpectrums
/// \param src1
/// \param src2
/// \param dst
/// \param rows
/// \param cols
/// \param channel
///            cv::Mat temp[2];
//temp[0] = (fftX1E[0].mul(fftX2E[0]) - fftX1E[1].mul(fftX2E[1]));  //复数矩阵的乘积
//temp[1] = (fftX1E[0].mul(fftX2E[1]) + fftX1E[0].mul(fftX2E[1]));  //复数矩阵的乘积
//cv::merge(temp,2,caux);
void mulSpectrums(float* src1, float* src2, float* dst, int rows, int cols, int channel);
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
void Matrix_Linner(float* srcDst, int rows, int cols, int channel, float plus, float mul=1);

///
/// \brief Matrix_Max
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
/// \param plus
/// \param mul
///求两个矩阵最大值
void Matrix_Max(float* src1, float* src2, float* dst, int rows, int cols, int channel);

///
/// \brief Matrix_EXP
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///对数据进行e 的指数次幂运算
void Matrix_EXP(float* srcDst, int rows, int cols, int channel);

///
/// \brief Matrix_complexDivision
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///复数的除法
void Matrix_complexDivision(float* src1,float* src2, float* dst, int rows, int cols, int channel);

///
/// \brief Matrix_complexDivision
/// \param srcDst
/// \param rows
/// \param cols
/// \param channel
///复数的乘法
void Matrix_complexMultiplication(float* src1,float* src2, float* dst, int rows, int cols, int channel);

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
void Matrix_MaxLoc(float* src, int rows, int cols, int channel, double& bestVal, int& bestX, int& bestY);
//分离图像为三个通道并且排列
template<typename T>
void splitImageChannel(T* srcImage, int srcH, int srcW, int srcChannel, T* arrayImage)
{
    assert(srcChannel!=0);
//    dstH = srcH*srcChannel;
//    dstW = srcW;
    for(int i=0; i<srcH; i++)
    {
        T* srcImageW = srcImage + i*srcW*srcChannel;
        for(int j=0; j<srcW; j++)
        {
            T* srcImageWC = srcImageW + j*srcChannel;
            for(int k=0; k<srcChannel; k++)
            {
                *(arrayImage + k*(srcH*srcW) + i*srcW + j ) = *(srcImageWC + k);
            }
        }
    }
}

//合并多个图像为多通道图
template<typename T>
void IK_mergeImageChannel(T* srcImage, int srcH, int srcW, int Num, T* dstImage)
{
    assert(Num!=0);
//    dstH = srcH*srcChannel;
//    dstW = srcW;
    for(int i=0; i<srcH/Num; i++)
    {
        T* dstImageW = dstImage + i*srcW*Num;
        for(int j=0; j<srcW; j++)
        {
            T* dstImageWC = dstImageW + j*Num;
            for(int k=0; k<Num; k++)
            {
                 *(dstImageWC + k) = *(srcImage + k*((srcH/Num)*srcW) + i*srcW + j );
            }
        }
    }
}



//翻转图像四个角
template<typename T>
void IK_rearrange(T* srcDstImg, int srcH, int srcW, int srcChannel)
{
    // img = img(cv::Rect(0, 0, img.cols & -2, img.rows & -2));
    int cx = srcW / 2;
    int cy = srcH / 2;
    int dstX, dstY=0;
    T* n_image = new T[srcH*srcW*srcChannel];
    for(int i=0; i<srcH; i++)
    {
        dstY = i<cy?(i+cy):(i-cy);
        for(int j=0; j<srcW; j++)
        {
            dstX = j<cx?(j+cx):(j-cx);
            for(int k=0; k< srcChannel; k++)
            {
                *(n_image + dstY*srcW*srcChannel + dstX*srcChannel +k) = *(srcDstImg + i*srcW*srcChannel + j*srcChannel + k);
            }
        }
    }
    memcpy(srcDstImg, n_image, sizeof(T)*srcH*srcW*srcChannel);
    delete n_image;
}


