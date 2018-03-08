//#include "ldmarkmodel.h"
//#include <cv.h>
////#include <modelcfg.h>
//#include <highgui.hpp>
//#include <imgcodecs.hpp>
//#include <imgproc.hpp>
//int main()
//{
//    cv::Mat img = cv::imread("H:\\IRISPRO\\code\\IKAI1KBio_AF\\IKAI1KBio_AF\\3rdparty\\SDM\\sdm_NCV\\face.jpg",0);
//    ldmarkmodel g_model;
//    float current_shape[136];
//    IK_Rect ROI(24,29,144,186);

//    //关键点对齐
//    g_model.track(img.data,img.cols, img.rows, current_shape, 136, ROI);//关键点跟踪
//    float eav[3];                                //分别为pitch, yaw, roll
//    g_model.EstimateHeadPose(current_shape,136, eav,3);//姿态估计
//    //关键点解析，并计算出瞳距，眉心位置，browData(1x13)结构为
//    //[眉心x, 眉心y, 左瞳x, 左瞳y， 右瞳x, 右瞳y,cropX, cropY, cropWidth, cropHeight, pitch, yaw, roll]
//    IK_Rect rect = g_model.enclosing_bbox(current_shape,136);
//    int numLandmarks = 68;
//    for(int j=0; j<numLandmarks; j++){
//        int x = current_shape[j];
//        int y = current_shape[j + numLandmarks];
//        cv::circle(img, cv::Point(x,y), 5, cv::Scalar(255,0,0));
//    }
//    cv::imshow("x", img);
//    cv::waitKey(0);
//    return 0;
//}
