#pragma once
#ifndef FEATURE_DESCRIPTOR_H_
#define FEATURE_DESCRIPTOR_H_

#include "modelcfg.h"
#include "helper.h"
#include <hog.h>
extern "C" {
    #include "hog.h" // From the VLFeat C library
}

float hogArray[KP_HOG_LENGTH];
//float hogDescriptors[KP_HOG_FEATUTE_LENGTH] = { 0.f };

//hog特征
float HOGFeature[KP_HOG_FEATUTE_LENGTH];

float update_step[LandmarkPointsNum*2];
struct HoGParam
{
    VlHogVariant vlhog_variant;
    int num_cells;
    int cell_size;
    int num_bins;
    float relative_patch_size; // the patch size we'd like in percent of the IED of the current image
    // note: alternatively, we could dynamically vary cell_size. Guess it works if the hog features are somehow normalised.
};


void CalculateHogDescriptor(unsigned char* srcData, int height, int width, std::vector<int> LandmarkIndexs, std::vector<int> eyes_index, HoGParam mHoGParam, float* hogDescriptors, int hogWidth){

    assert(hogDescriptors!=0);
    memset(hogDescriptors, 0x00, sizeof(float)*hogWidth);
    float *hogDesTemp = new float[hogWidth];
    memset(hogDesTemp, 0x00, sizeof(float)*hogWidth);
    // This is in pixels in the original image:
    int numLandmarks = LandmarkPointsNum;
    float lx = ( currentShape[eyes_index.at(0)] + currentShape[eyes_index.at(1)] )*0.5f;
    float ly = ( currentShape[eyes_index.at(0) + numLandmarks] + currentShape[eyes_index.at(1)+numLandmarks])*0.5f;
    float rx = ( currentShape[eyes_index.at(2)] + currentShape[eyes_index.at(3)] )*0.5f;
    float ry = ( currentShape[eyes_index.at(2)+numLandmarks] + currentShape[eyes_index.at(3)+numLandmarks] )*0.5f;
    float distance = sqrt( (rx-lx)*(rx-lx)+(ry-ly)*(ry-ly) );
    int patch_width_half = (int)round(mHoGParam.relative_patch_size * distance);
    //cv::Mat hogDescriptors; // We'll get the dimensions later from vl_hog_get_*
    for (unsigned int i = 0; i < LandmarkIndexs.size(); i++) {
        int x = (int)round(currentShape[LandmarkIndexs.at(i)]);
        int y = (int)round(currentShape[LandmarkIndexs.at(i)+numLandmarks]);
        //////
        /// \brief roi
        //截取图像块
        unsigned char* roiData = new unsigned char[patch_width_half * 2*patch_width_half * 2];
        memset(roiData, 0x00, sizeof(unsigned char)*patch_width_half * 2*patch_width_half * 2);
        dipImCropHog(srcData, height,width,   y-patch_width_half, x-patch_width_half,roiData, patch_width_half * 2, patch_width_half * 2);
        int fixed_roi_size = mHoGParam.num_cells * mHoGParam.cell_size;

        //压缩图像
        float* f_roiImage = new float[fixed_roi_size*fixed_roi_size];
        memset(f_roiImage, 0, sizeof(float)*fixed_roi_size*fixed_roi_size);
        resize_bilinearFloat(roiData, patch_width_half * 2, patch_width_half * 2, 1, f_roiImage, fixed_roi_size, fixed_roi_size, 1);
        delete roiData;
        //hog特征抽取
        VlHog* hog = vl_hog_new(VlHogVariantUoctti, mHoGParam.num_bins, false); // transposed (=col-major) = false
        vl_hog_put_image(hog, (float*)f_roiImage, fixed_roi_size, fixed_roi_size, 1, mHoGParam.cell_size); // (the '1' is numChannels)
        int ww = static_cast<int>(vl_hog_get_width(hog)); // assert ww == hh == numCells
        int hh = static_cast<int>(vl_hog_get_height(hog));
        int dd = static_cast<int>(vl_hog_get_dimension(hog)); // assert ww=hogDim1, hh=hogDim2, dd=hogDim3
        //cv::Mat hogArray1(1, ww*hh*dd, CV_32FC1); // safer & same result. Don't use C-style memory management.
        vl_hog_extract(hog, hogArray);
        vl_hog_delete(hog);

        //特征转换
        delete f_roiImage;
        float *ptr = hogDesTemp + i*ww*hh*dd ;//+ j*ww*hh;
        for (int j = 0; j < dd; ++j)
        {
            float*src = hogArray + j*ww*hh;
            for (int m = 0; m < ww; m++)
            {
                for (int n = 0; n < hh; n++)
                {
                    // unused xx
                    // int xx = m + n*ww;
                    *ptr = src[m + n*ww];
                    ptr++;
                }
            }

        }

    }
    hogDesTemp[hogWidth - 1] = 1.f;
    memcpy(hogDescriptors, hogDesTemp, sizeof(float)*hogWidth);

    delete hogDesTemp;
    return;
}


#endif
