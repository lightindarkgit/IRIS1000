#pragma once
#ifndef __HELPER_H_
#define __HELPER_H_

#include <iostream>
#include <iostream>
#include <fstream>

#include "modelcfg.h"
#include <algorithm>
#include <assert.h>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//平均形状
float currentShape[LandmarkPointsNum*2];

struct IK_Point{
    IK_Point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    int m_x;
    int m_y;
};

static void get_enclosing_bbox(IK_Rect& rect, float* currentShape, int shapNum)
{
    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    int pointNum = shapNum/2;
    for(int i=0; i<pointNum; i++)
    {
        int x = (int)*(currentShape + i);
        int y = (int)*(currentShape + i + pointNum);
        if(0 == i)//初始化
        {
            minX = x;
            maxX = x;
            minY = y;
            maxY = y;
        }
        //更新最大最小值
        minX = x < minX ? x : minX;
        minY = y < minY ? y : minY;
        maxX = x > maxX ? x : maxX;
        maxY = y > maxY ? y : maxY;
    }
    rect = IK_Rect(minX, minY, maxX - minX, maxY - minY);
}

/**
 * Performs an initial alignment of the model, by putting the mean model into
 * the center of the face box.
 *
 * An optional scaling and translation parameters can be given to generate
 * perturbations of the initialisation.
 *
 * Note 02/04/15: I think with the new perturbation code, we can delete the optional
 * parameters here - make it as simple as possible, don't include what's not needed.
 * Align and perturb should really be separate - separate things.
 *
 * @param[in] mean Mean model points.
 * @param[in] facebox A facebox to align the model to.
 * @param[in] scaling_x Optional scaling in x of the model.
 * @param[in] scaling_y Optional scaling in y of the model.
 * @param[in] translation_x Optional translation in x of the model.
 * @param[in] translation_y Optional translation in y of the model.
 * @return A cv::Mat of the aligned points.
 */
void align_mean(float* mean, int meanNum, float* alignedMean, int alignedMeanNum, IK_Rect facebox, float scaling_x=1.0f, float scaling_y=1.0f, float translation_x=0.0f, float translation_y=0.0f)
{
    assert(meanNum==alignedMeanNum);
    assert(mean!=0 && alignedMean!=0);
    // Initial estimate x_0: Center the mean face at the [-0.5, 0.5] x [-0.5, 0.5] square (assuming the face-box is that square)
    // More precise: Take the mean as it is (assume it is in a space [-0.5, 0.5] x [-0.5, 0.5]), and just place it in the face-box as
    // if the box is [-0.5, 0.5] x [-0.5, 0.5]. (i.e. the mean coordinates get upscaled)

    //deal x
    for(int a=0 ;a<meanNum/2; a++)
    {
        *(alignedMean+a) = (*(mean + a)*scaling_x + 0.5f + translation_x) * facebox.m_width + facebox.m_x;
    }
    //deal y
    for(int a=meanNum/2 ;a<meanNum; a++)
    {
        *(alignedMean+a) = (*(mean + a)*scaling_y + 0.3f + translation_y) * facebox.m_height + facebox.m_y;
    }
}
///////
/// \brief Mul
/// \param matrixA
/// \param matrixB
/// \param matrixC
/// 矩阵的乘法
////////
void Matrix_Mul(float *Mul1, int Mul1_m, float *Mul2, int Mul2_n, int nm, float *Mul)
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


///
/// \brief dipImCropHog  corp the image
/// \param srcIm
/// \param srcImH
/// \param srcImW
/// \param startR
/// \param startC
/// \param objIm
/// \param objImH
/// \param objImW
/// \return
///
int dipImCropHog(const unsigned char *srcIm, int srcImH, int srcImW, int startR, int startC, unsigned char *objIm, int objImH, int objImW)
{
    if ((startR >= srcImH) || (startR + objImH < 0) || (startC >= srcImW) || (startC + objImW < 0))
    {
        return  -1;
    }
    //求两个矩形交集
    int AdjustLeft = std::max(0, startC);
    int AdjustRight = std::min(srcImW, startC + objImW);
    int AdjustTop = std::max(0, startR);
    int AdjustBottom = std::min(srcImH, startR + objImH);
    int AdjustWidth = AdjustRight<AdjustLeft?0:(AdjustRight - AdjustLeft);
    int AdjustHeight = AdjustBottom<AdjustTop?0:(AdjustBottom - AdjustTop);

    int offsetObjR = startR<0?(-startR):0;
    int offsetObjC = startC<0?(-startC):0;

    //计算crop的起始位置
    objIm = objIm+ offsetObjR*objImW ;
    unsigned char* data = (unsigned char*)(srcIm + srcImW*AdjustTop);
    //行遍历
    for(int i=0; i< AdjustHeight; i++, data+=srcImW)
    {
        memcpy(objIm+i*objImW+ offsetObjC, data+AdjustLeft, AdjustWidth);
    }
    return 0;
}


int resize_bilinearFloat(const unsigned char* srcData, int srcW, int srcH, int srcChannels, float* dstData, int dstW, int dstH, int dstChannels)
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
        float *pdst = dstData + (dx)*dstW*dstChannels;
        float rx = tabrx[dx], irx = 1.0f - rx;
        for (int dy = 0; dy < dstW; ++dy)
        {
            float *pcdst = pdst + dy*ch;
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
#endif
