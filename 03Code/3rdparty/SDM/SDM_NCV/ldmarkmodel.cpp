#include "ldmarkmodel.h"
#include <iostream>

#include "helper.h"
#include "feature_descriptor.h"
#include <stdlib.h>
#include "modelsdm.h"

//回归器类
class LinearRegressor{

public:
    LinearRegressor(int rows, int cols);

    void  predict(float* value, int Num,float* shape, int index);
public:

    //float** m_weight;
    int m_rows;
    int m_cols;
};

std::vector<HoGParam> HoGParams;

std::vector<LinearRegressor> LinearRegressors;
std::vector<std::vector<int> > LandmarkIndexs;
using namespace std;
LinearRegressor::LinearRegressor(int rows, int cols)//[LandmarkPointsNum*2])
{
    m_cols = cols;
    m_rows = rows;

    //m_weight = weight;
}

void  LinearRegressor::predict(float* value, int Num, float* shape, int index)
{
    assert(value!=0);
    if(index == 1)
    {
       Matrix_Mul(&value[0], 1, (float*)&weights1[0][0], 2*LandmarkPointsNum, this->m_rows, &shape[0]);
    }
    else if(index == 2)
    {
       Matrix_Mul(&value[0], 1, (float*)&weights2[0][0], 2*LandmarkPointsNum, this->m_rows, &shape[0]);
    }
    else if(index == 3)
    {
       Matrix_Mul(&value[0], 1, (float*)&weights3[0][0], 2*LandmarkPointsNum, this->m_rows, &shape[0]);
    }
    else if(index == 4)
    {
       Matrix_Mul(&value[0], 1, (float*)&weights4[0][0], 2*LandmarkPointsNum, this->m_rows, &shape[0]);
    }
    else if(index == 5)
    {
       Matrix_Mul(&value[0], 1, (float*)&weights5[0][0],2*LandmarkPointsNum, this->m_rows,&shape[0]);
    }
    //return  values*this->weights;
}

ldmarkmodel::ldmarkmodel():isNormal(true){
    //{36,39,42,45,30,48,54};   {7,16,17,8,9,10,11};
    //static int HeadPosePointIndexs[] = {36,39,42,45,30,48,54};
    //estimateHeadPosePointIndexs = HeadPosePointIndexs;

    vector<int> LandmarkIndex1(IteraLandmarkIndex1, IteraLandmarkIndex1+LandmarkLength1);
    LandmarkIndexs.push_back(LandmarkIndex1);
    vector<int> LandmarkIndex2(IteraLandmarkIndex2, IteraLandmarkIndex2+LandmarkLength2);
    LandmarkIndexs.push_back(LandmarkIndex2);
    vector<int> LandmarkIndex3(IteraLandmarkIndex3, IteraLandmarkIndex3+LandmarkLength3);
    LandmarkIndexs.push_back(LandmarkIndex3);
    vector<int> LandmarkIndex4(IteraLandmarkIndex4, IteraLandmarkIndex4+LandmarkLength4);
    LandmarkIndexs.push_back(LandmarkIndex4);
    vector<int> LandmarkIndex5(IteraLandmarkIndex5, IteraLandmarkIndex5+LandmarkLength5);
    LandmarkIndexs.push_back(LandmarkIndex5);

    meanShape = mean_norm_shape;
    HoGParam hog1 = { VlHogVariantUoctti, 4, 11, 4, 0.9f };
    HoGParams.push_back(hog1);
    HoGParam hog2 = { VlHogVariantUoctti, 4, 10, 4, 0.7f };
    HoGParams.push_back(hog2);
    HoGParam hog3 = { VlHogVariantUoctti, 4, 9, 4, 0.5f };
    HoGParams.push_back(hog3);
    HoGParam hog4 = { VlHogVariantUoctti, 4, 8, 4, 0.3f };
    HoGParams.push_back(hog4);
    HoGParam hog5 = { VlHogVariantUoctti, 4, 6, 4, 0.2f };
    HoGParams.push_back(hog5);

    //HoGParams = std::vector<HoGParam>{ ,{ VlHogVariantUoctti, 4, 10, 4, 0.7f },{VlHogVariantUoctti, 4, 9, 4, 0.5f },{ VlHogVariantUoctti, 4, 8, 4, 0.3f }, { VlHogVariantUoctti, 4, 6, 4, 0.2f } };
    LinearRegressor lr1(3073,LandmarkPointsNum*2);
    LinearRegressors.push_back(lr1);

    LinearRegressor lr2(3073,LandmarkPointsNum*2);
    LinearRegressors.push_back(lr2);

    LinearRegressor lr3(3073,LandmarkPointsNum*2);
    LinearRegressors.push_back(lr3);

    LinearRegressor lr4(5121,LandmarkPointsNum*2);
    LinearRegressors.push_back(lr4);

    LinearRegressor lr5(5121,LandmarkPointsNum*2);
    LinearRegressors.push_back(lr5);
}

ldmarkmodel::~ldmarkmodel()
{

}


void ldmarkmodel::predict(unsigned char* grayImage, int width, int height, IK_Rect crop)
{
    if(0 == grayImage)
    {
        return;
    }
    std::vector<int> eyes_index(eyes_indexs, eyes_indexs+4);
    float current_shape[2*LandmarkPointsNum];
    align_mean(mean_norm_shape, 2*LandmarkPointsNum,current_shape, 2*LandmarkPointsNum, crop);        //perturb(maxRect), 模型和人脸进行
    int numLandmarks = LandmarkPointsNum;

    for(unsigned int i=0; i<LinearRegressors.size(); i++){
        float* hogDescriptors = new float[sizeof(float)*LinearRegressors[i].m_rows*LinearRegressors[i].m_cols];

        CalculateHogDescriptor(grayImage, height,width, LandmarkIndexs.at(i), eyes_index, HoGParams.at(i), hogDescriptors, LinearRegressors[i].m_rows*LinearRegressors[i].m_cols);
        LinearRegressors.at(i).predict(hogDescriptors,KP_HOG_FEATUTE_LENGTH,update_step, i);
        //cv::Mat update_step = LinearRegressors.at(i).predict(Descriptor);
        if(isNormal){
            float lx = (float)(( current_shape[eyes_index.at(0)] + current_shape[eyes_index.at(1)] )*0.5);
            float ly = (float)(( current_shape[eyes_index.at(0)+numLandmarks] + current_shape[eyes_index.at(1)+numLandmarks] )*0.5);
            float rx = (float)(( current_shape[eyes_index.at(2)] + current_shape[eyes_index.at(3)] )*0.5);
            float ry = (float)(( current_shape[eyes_index.at(2)+numLandmarks] + current_shape[eyes_index.at(3)+numLandmarks] )*0.5);
            float distance = (float)sqrt( (rx-lx)*(rx-lx)+(ry-ly)*(ry-ly) );
            for(int k =0; k<LandmarkPointsNum*2; k++)
            {
                update_step[k]*=distance;
            }
        }
        for(int k =0; k<LandmarkPointsNum*2; k++)
        {
            current_shape[k]+=update_step[k];
        }
        delete hogDescriptors;
    }
    return;
}


//只接收灰度图
int ldmarkmodel::track(unsigned char* srcData, int width, int height, float* current_shape, int current_shapeNum, IK_Rect face_Rect){
    if(0 == srcData)
    {
        return SDM_ERROR_IMAGE;
    }
    std::vector<int> eyes_index(eyes_indexs, eyes_indexs+4);
    //get_enclosing_bbox(current_shape,2*LandmarkPointsNum,faceBox);

    int error_code = SDM_NO_ERROR;
    faceBox = face_Rect;
    align_mean(mean_norm_shape, 2*LandmarkPointsNum, currentShape, 2*LandmarkPointsNum, face_Rect);
    int numLandmarks = LandmarkPointsNum;

    for(unsigned int i=0; i<LinearRegressors.size(); i++){
        float* hogDescriptors = new float[sizeof(float)*LinearRegressors[i].m_rows];
        CalculateHogDescriptor(srcData,height, width, LandmarkIndexs.at(i), eyes_index, HoGParams.at(i), hogDescriptors, LinearRegressors[i].m_rows);

        LinearRegressors.at(i).predict(hogDescriptors,KP_HOG_FEATUTE_LENGTH,update_step, i+1);
        if(isNormal){
            float lx = (float)(( currentShape[eyes_index.at(0)] + currentShape[eyes_index.at(1)] )*0.5);
            float ly = (float)(( currentShape[eyes_index.at(0)+numLandmarks] + currentShape[eyes_index.at(1)+numLandmarks] )*0.5);
            float rx = (float)(( currentShape[eyes_index.at(2)] + currentShape[eyes_index.at(3)] )*0.5);
            float ry = (float)(( currentShape[eyes_index.at(2)+numLandmarks] + currentShape[eyes_index.at(3)+numLandmarks] )*0.5);
            float distance = (float)sqrt( (rx-lx)*(rx-lx)+(ry-ly)*(ry-ly) );
            for(int k =0; k<LandmarkPointsNum*2; k++)
            {
                update_step[k]*=distance;
            }
        }
        for(int k =0; k<LandmarkPointsNum*2; k++)
        {
            currentShape[k]+=update_step[k];
        }
        delete hogDescriptors;
    }
    memcpy(current_shape,currentShape, sizeof(float)*current_shapeNum);
    return error_code;
}

//进行姿态的估计
void ldmarkmodel::EstimateHeadPose(float* current_shape, int current_shapeNum, float* eav, int eavNum){
    assert(current_shape!=0);
    static const int samplePdim = 7;
    float miny = 10000000000.0f;
    float maxy = 0.0f;
    float sumx = 0.0f;
    float sumy = 0.0f;
    int landmarkPointsNum = current_shapeNum/2;
    for(int i=0; i<samplePdim; i++){
        sumx += current_shape[HeadPosePointIndexs[i]];
        float y = current_shape[HeadPosePointIndexs[i]+landmarkPointsNum];
        sumy += y;
        if(miny > y)
            miny = y;
        if(maxy < y)
            maxy = y;
    }
    float dist = maxy - miny;
    sumx = sumx/samplePdim;
    sumy = sumy/samplePdim;
    float* temp = new float[2*samplePdim+1];
    memset(temp,0x00, 2*samplePdim+1);
    //static cv::Mat tmp(1, 2*samplePdim+1, CV_32FC1);
    for(int i=0; i<samplePdim; i++){
        temp[i] = (current_shape[HeadPosePointIndexs[i]]-sumx)/dist;
        temp[i+samplePdim] = (current_shape[HeadPosePointIndexs[i]+landmarkPointsNum]-sumy)/dist;
    }
    temp[2*samplePdim] = 1.0f;

    float tempEAV[3];
    memset(tempEAV,0x00,sizeof(float)*eavNum);

    Matrix_Mul(&temp[0],1,&estimateHeadPose2dArray2[0],eavNum,15, tempEAV);
    memcpy(eav,tempEAV,sizeof(float)*eavNum);
    delete temp;
    return;
}

IK_Rect ldmarkmodel::enclosing_bbox(float* current_shape, int current_shapeNum)
{
    IK_Rect rect;
    get_enclosing_bbox(rect, current_shape, current_shapeNum);
    return rect;
}

