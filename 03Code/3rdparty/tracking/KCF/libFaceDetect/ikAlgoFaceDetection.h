/*
The MIT License (MIT)

Copyright (c) 2015-2016 Shiqi Yu
shiqi.yu@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef FACEDETECT_DLL_H
#define FACEDETECT_DLL_H

#define IKALG_PLATFORM_ANDROID_NO//
#define __linux__

#ifdef IKALG_PLATFORM_ANDROID
#define FACEDETECTDLL_API extern "C"
#else
#ifdef FACEDETECTDLL_EXPORTS
#define FACEDETECTDLL_API __declspec(dllexport) 
#else
#ifdef __linux__
#define FACEDETECTDLL_API   extern "C"
#else
#define FACEDETECTDLL_API __declspec(dllimport)
#endif
#endif
#endif
//Error Code
#define IKALGO_FACE_DETECT				-7202
#define IKALGO_FACE_IM_OVERSIZE			-7203
#define IKALGO_DIP_CropSubImErr			-7172
#define IR_FUN_SUCCESS					0

#define FR_FACE_DETECT_NONE				-1
#define FR_FACE_DETECT_VALID			0

#define FACE_IMAGE_HEIGHT				1520//1920
#define FACE_IMAGE_WIDTH				2592//1080
#define FACE_DETECT_DNRATE				1//4
#define FACE_DETECT_ROI_H				(FACE_IMAGE_HEIGHT/FACE_DETECT_DNRATE)
#define FACE_DETECT_ROI_W				(FACE_IMAGE_WIDTH/FACE_DETECT_DNRATE)
#define FACE_DETECT_ROI_SIZE			FACE_DETECT_ROI_H*FACE_DETECT_ROI_W

//#define FACE_CROP_IM_H					200
//#define FACE_CROP_IM_W					200

#define FR_DETECT_INFO_LEN				50	//Inf vector len of video stream information
typedef struct FaceDetectionInfoStruct
{
	int faceBgR;	//row index of up-left point of left eye
	int faceBgC;	//col index of up-left point of left eye
	int faceROIH;	//height index of left eye
	int faceROIW;	//width index of left eye
	int faceFlag;	//
	int streamInf[FR_DETECT_INFO_LEN];//used for video stream information (not used currently)
}FaceDetectionInfo, *pFaceDetectionInfo;

/*
函数名：IKFR_FaceDetection
输入：srcIm：输入图像
	  width：图像的宽
	  height：图像的高
	  cropFaceIm：输出的剪切图像；
	  cropImW：输出剪切图像的宽
	  cropImH：输出剪切图像的高
	  min_faceSize：检测人脸的最小值；
	  max_faceSize：检测人脸的最大值；
	  deviceType：输入的设备类型，暂时只支持设备类型0
输出：
	  detectResult：检测结果
	  函数返回值：0代表检测成，其他值代表检测失败	  
*/
FACEDETECTDLL_API int IKFR_FaceDetection(unsigned char *srcIm, int width, int height, unsigned char *cropFaceIm, int cropImW, int cropImH,
	int min_faceSize, int max_faceSize, pFaceDetectionInfo detectResults, int deviceType);
/*
函数名：IKFR_FaceDetection
输入：srcIm：输入图像
	  width：图像的宽
	  height：图像的高
	  min_faceSize：检测人脸的最小值；
	  max_faceSize：检测人脸的最大值；
	  deviceType：输入的设备类型，暂时只支持设备类型0
输出：
	  detectResult：检测结果
	  函数返回值：0代表检测成，其他值代表检测失败	  
*/
//FACEDETECTDLL_API int IKFR_FaceDetection(unsigned char *srcIm, int width, int height, int min_faceSize, int max_faceSize,
//	pFaceDetectionInfo detectResults, int deviceType);


FACEDETECTDLL_API int * facedetect_frontal(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0xC004 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_frontal_surveillance(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0xC004 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_multiview(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0xC004 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.

FACEDETECTDLL_API int * facedetect_multiview_reinforce(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0xC004 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
							   int max_object_width=0); //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.


#endif
