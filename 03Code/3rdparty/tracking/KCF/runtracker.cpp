
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//#include <iostream>
//#include <io.h>
//#include <direct.h>
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <fstream>
//#ifdef _DEBUG
////#include <vld.h>
//#endif
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include "kcftracker.hpp"
//#include <ffttools.h>
//#include <tracker.h>
//#include <Windows.h>
//#include <ikAlgoFaceDetection.h>
//#include <publicdata.h>
//using namespace std;
//using namespace cv;
//#define DETECT_BUFFER_SIZE 0x20000       //定义人脸检测需要分配的内存大小
////void renameFile(){
////    //重命名
////    string xxName =string(ImagePath + imageMark_filenames[nFrames]);
////    string fname = string(imageMark_filenames[nFrames]);
////    string fTopname = fname.substr(0,fname.size()-4);
////    int number = std::stoi(fTopname);
////    char buffer[80];
////    sprintf(buffer, "%05d", number);//转换123为"00123"
////    string newName(buffer);
////    string xxnewName = ImagePath + newName + ".bmp";
////    if(!_access(xxName.data(),0))//如果文件存在:
////    {
////        if(!rename(xxName.data(),xxnewName.data()))//删除成功
////        {
////            cout<<ImagePath + imageMark_filenames[nFrames]<<" 成功重命名为: "<<xxnewName<<endl;
////        }
////        else//无法重命名:文件打开或无权限执行重命名
////        {
////            //                cout<<"文件无法重命名(可能原因如下):"<<endl;
////            //                cout<<"\t"<<"1. "<<newname<<" 已存在"<<endl
////            //                   <<"\t"<<"2. "<<newname<<" 正在使用,未关闭."<<endl
////            //                  <<"\t"<<"3. "<<"你没有权限重命名此文件."<<endl;
////        }
////    }

////    frame = cv::imread(ImagePath + imageMark_filenames[nFrames+1]);
////    if(frame.empty())
////        break;
////    nFrames++;
////}
//bool get_filelist_from_dir(std::string path, std::vector<std::string>& files)
//{
//    long   hFile = 0;
//    struct _finddata_t fileinfo;
//    files.clear();
//    if ((hFile = _findfirst(path.c_str(), &fileinfo)) != -1)
//    {
//        do
//        {
//            if (!(fileinfo.attrib &  _A_SUBDIR))
//                files.push_back(fileinfo.name);
//            //cout <<fileinfo.name << endl;
//        } while (_findnext(hFile, &fileinfo) == 0);
//        _findclose(hFile);
//        return true;
//    }
//    else
//        return false;
//}

////翻转图像四个角
//void rearrange(cv::Mat& img)
//{
//    // img = img(cv::Rect(0, 0, img.cols & -2, img.rows & -2));
//    int cx = img.cols / 2;
//    int cy = img.rows / 2;
//    cv::Mat q0(img, cv::Rect(0, 0, cx, cy)); // Top-Left - Create a ROI per quadrant
//    cv::Mat q1(img, cv::Rect(cx, 0, cx, cy)); // Top-Right
//    cv::Mat q2(img, cv::Rect(0, cy, cx, cy)); // Bottom-Left
//    cv::Mat q3(img, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

//    cv::Mat tmp; // swap quadrants (Top-Left with Bottom-Right)
//    q0.copyTo(tmp);
//    q3.copyTo(q0);
//    tmp.copyTo(q3);
//    q1.copyTo(tmp); // swap quadrant (Top-Right with Bottom-Left)
//    q2.copyTo(q1);
//    tmp.copyTo(q2);
//}

//int main(int argc, char* argv[]){

//    // Frame readed
//    Mat frame;
//    string ImagePath = "G:\\FaceDetect\\FaceBase\\";
//    string command = "dir /b /a-d " + ImagePath + "*.bmp >" + ImagePath + "allfiles.txt";
//    //system(command.data());
//    // Tracker results
////    Rect result;

//    // Using min and max of X and Y for groundtruth rectangle
////    float xMin = 30;
////    float yMin = 5;
////    float width = 95;
////    float height = 65;
//    VideoCapture capture(0);// ("H://FFOutput//facetest1.avi");
//    //检测是否正常打开:成功打开时，isOpened返回ture
//    if (!capture.isOpened())
//        cout << "fail to open!" << endl;


//    char imgName[10];
//    string frameName;
//    int nFrames = 0;
//    bool initFace = false;
//    IK_Rect rect;
//    cv::Rect  tkFace;
//    std::vector<string> imageMark_filenames;
//    string search_path = ImagePath + "*.bmp";
//    string outPut = ImagePath + "example/";
//    if (!get_filelist_from_dir(search_path, imageMark_filenames)) printf("can not read file list\n");
//    int TrackCount = 0;
//    int DetectCount = 0;
//    //while(1)
//    while(capture.read(frame))
//    {
////        frame = cv::imread(ImagePath + imageMark_filenames[nFrames]);
////        if(frame.empty())
////            break;
//        nFrames++;

//        cv::transpose(frame, frame);                  //转置，长宽方向颠倒
//        cv::flip(frame, frame, 1);
//        //frame = cv::imread("E://face.jpg",1);
//        //cv::Mat test = frame.clone();
//        //cv::resize(frame, frame, cv::Size(320,240));

//        pointData data;
//        int val = detectTracking(frame.data, frame.rows, frame.cols, frame.channels(),rect, data);
//        if(val==0)
//        {
//            if(data.flag == true)
//            {
//                tkFace = cv::Rect(data.track_cropX, data.track_cropY, data.track_cropWidth, data.track_cropHeight);
//                if(data.track_cropWidth!=0 && data.detect_cropWidth==0)
//                {
//                    TrackCount++;
//                }
//                if(data.track_cropWidth!=0 && data.detect_cropWidth!=0)
//                {
//                    DetectCount++;
//                }
//                rectangle( frame, cv::Rect(data.detect_cropX, data.detect_cropY, data.detect_cropWidth, data.detect_cropHeight), Scalar( 0, 0, 255 ), 5, 8 );//红，检测
//                rectangle( frame, cv::Rect(data.cropX, data.cropY,data.cropW,data.cropH), Scalar( 0, 255, 0 ), 1, 8 );//绿，关键点
//                rectangle( frame, tkFace, Scalar( 255, 0, 0 ), 2, 8 );//蓝，跟踪
//                for(int i=0; i< LANDMARKNUM; i++)
//                {
//                    cv::circle(frame, cv::Point(data.landmarks[2*i], data.landmarks[2*i+1]), 8, cv::Scalar(100,10,100));
//                }
//            }
//        }

//        imshow("Image", frame);
//        cv::resize(frame, frame, cv::Size(320,240));
//        string fullname = imageMark_filenames[nFrames];
//        string nameX = fullname.substr(0, fullname.size() - 4);
//        cv::imwrite(outPut+nameX +".jpg", frame);
//        waitKey(1);
//    }
//    std::cout<<"TrackCount:"<<TrackCount<<" DetectCount:"<<DetectCount<<std::endl;
//}
