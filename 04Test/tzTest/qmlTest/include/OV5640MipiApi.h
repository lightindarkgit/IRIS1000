#ifndef IKOV5640MIPIAPI_H_
#define  IKOV5640MIPIAPI_H_
#ifdef __cplusplus
extern "C" {
#endif

/**
* camera works well */
#define IK_CAMERA_API_OK                        	(0)
#define IK_CAMERA_API_ERROR_BASE                	(-1000)
#define IK_CAMERA_API_VIDIOC_QUERYBUF_ERR       	(-100 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_QBUF_ERR       		(-101 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_STREAMON_ERR       	(-102 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_STREAMOFF_ERR      	(-103 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_DEVICE_OPEN_ERR    		(-104 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_DBG_G_CHIP_IDENT_ERR       (-105 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_S_PARM_ERR       		(-106 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_S_INPUT_ERR       		(-106 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_G_CROP_ERR       		(-107 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_S_FMT_ERR       		(-108 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_VIDIOC_REQBUFS_ERR       		(-109 + IK_CAMERA_API_ERROR_BASE)

#define IK_CAMERA_API_GET_IMAGE_TIMEROUT_ERR       	(-110 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_IMAGE_NO_READY_ERR       		(-111 + IK_CAMERA_API_ERROR_BASE)

#define IK_CAMERA_API_COND_INIT_ERR		       	(-112 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_MUTEX_INIT_ERR		       	(-113 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_START_CAPTURE_ERR		       	(-114 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_STOP_CAPTURE_ERR		       	(-115 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_THREAD_CREATE_ERR		       	(-116 + IK_CAMERA_API_ERROR_BASE)

#define IK_CAMERA_API_GET_VERSION_ERR		       	(-117 + IK_CAMERA_API_ERROR_BASE)

#define IK_CAMERA_API_IPU_HANDLE_INIT_ERR		(-118 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_IPU_OPEN_ERR		       	(-119 + IK_CAMERA_API_ERROR_BASE)
#define IK_CAMERA_API_MMAP_FAIL_ERR		       	(-120 + IK_CAMERA_API_ERROR_BASE)





#define OV5640_IMAGE_FORMAT_Y			0x01
#define OV5640_IMAGE_FORMAT_UY			0x02
#define OV5640_IMAGE_FORMAT_RGB			0x03

#define MAX_PATH                260

char G_OV5640_Version[MAX_PATH] = "IKOV5640MIPICAMERAAPI.V1.0.0.20170928";

// 打开摄像头
int IKOV5640YUV_OpenMIPICamera(char* dev,int width,int height);

//获取图像数据,data空间长度至少为ImgSize
int IKOV5640YUV_GetMIPIImage(unsigned char *data);

//关闭摄像头
int IKOV5640YUV_CloseMIPICamera();

/**************************************************************/
/*
15fps 
	0      640,  480,
	1      320,  240,
	2      720,  480,
	3      720,  576,
	4      1280, 720,
	5      1920, 1080,
	6      2592, 1944,
	7      176,  144,
	8      1024, 768,

30fps
	0      640,  480,
	1      320,  240,
	2      720, 480,
	3      720, 576,
	4      1280, 720,
	5      1920, 1080,
	6      NULL, 0,
	7      176, 144,
	8      1024, 768,
*/
/**************************************************************************/
int IKOV5640YUV_SetParmMIPICamera(int framerate,int mode,int input,int rotate,int imge_format);

int IKOV5640YUV_GetVersion(char *version);

int IKOV5640YUV_SetBrightness(int val);

int IKOV5640YUV_SetGamma(int val);

int IKOV5640YUV_SetContrast(int val);

int IKOV5640YUV_SetSharpness(int val);

int IKOV5640YUV_ImgProcess_num(int val);

int IKOV5640YUV_GetIMGParameters(int *gamma, int *brightness, int *contrast, int *sharpness);
#ifdef __cplusplus
}
#endif

#endif





