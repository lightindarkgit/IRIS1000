#ifndef IKOV2710DVPAPI_H_
#define  IKOV2710DVPAPI_H_
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

#define MAX_PATH                260

char G_OV2710_Version[MAX_PATH] = "IKOV2710DVPCAMERAAPI.V1.0.0.20171126";

// 打开摄像头
int IKOV2710Raw_OpenDVPCamera(char* dev,int width,int height);

//获取图像数据,data空间长度至少为ImgSize
int IKOV2710Raw_GetDVPImage(unsigned char *data);

//关闭摄像头
int IKOV2710Raw_CloseDVPCamera();

int IKOV2710Raw_GetVersion(char *version);

int IKOV2710Raw_SetBrightness(int val);

int IKOV2710Raw_SetGamma(int val);

int IKOV2710Raw_SetContrast(int val);

int IKOV2710Raw_SetSharpness(int val);

int IKOV2710Raw_ImgProcess_num(int val);

int IKOV2710Raw_GetIMGParameters(int *gamma, int *brightness, int *contrast, int *sharpness);
#ifdef __cplusplus
}
#endif

#endif





