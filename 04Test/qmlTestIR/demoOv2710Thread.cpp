/*******************************************************************************
 * ov2710
********************************************************************************/
#include "demoOv2710Thread.h"
#include "Ov2710DvpApi.h"

char ov2710_g_v4l_device[100] = "/dev/video0";
int ov2710_width = 1920;
int ov2710_height = 1080;
#define OV2710_DATA_LEN			1920*1080
unsigned char ov2710_testdata[OV2710_DATA_LEN];
int ov2710_g_rotate = 0;
int ov2710_g_width = 1920;
int ov2710_g_height = 1080;
int ov2710_g_exit_flag = 0;
int ov2710_g_fps = 30;
char Ov2710_Version[260];
DemoOv2710Thread::DemoOv2710Thread(QObject *parent)
    : QThread(parent)
{
    stopped = false;
    dispImg = NULL;
//    connect(this, SIGNAL(saveimg()), this, SLOT(ov2710_saveimg()));
    memset(ov2710_testdata, 0x0, 1920*1080);
    IKOV2710Raw_GetVersion(Ov2710_Version);
    printf("IKOV2710Raw_GetVersion = %s\r\n",Ov2710_Version);
    IKOV2710Raw_OpenDVPCamera(ov2710_g_v4l_device,ov2710_width,ov2710_height);

}
DemoOv2710Thread::~DemoOv2710Thread()
{
    IKOV2710Raw_CloseDVPCamera();
    stopThread();
    quit();
    wait();
}
//void DemoOv2710Thread::ov2710_saveimg()
//{
//    char p_name[256];
//    for(int i = 0; i < num_img_ov2710; i++)
//    {
//        sprintf(p_name,"%s-%d.bmp",file_path_name_ov2710,i);
//        itSaveBMP(p_name,ov2710_data[i], ov2710_g_height,ov2710_g_width);
//    }
//    emit saveimgok();
//}
void DemoOv2710Thread::stopThread()
{
    stopped = true;
//    this->terminate();
}

void DemoOv2710Thread::startThread()
{
    stopped = false;
    this->start();
}

void DemoOv2710Thread::run()
{
//    unsigned char num = 0;
    QImage *dispImg_ov2710 = new QImage(ov2710_testdata, ov2710_g_width,ov2710_g_height,QImage::Format_Indexed8);
    QVector<QRgb> my_table;
    for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
    dispImg_ov2710->setColorTable(my_table);
    while(!stopped)
    {
        //printf("DemoOv2710Thread----------------------------------\r\n");
        IKOV2710Raw_GetDVPImage(ov2710_testdata);
//        if(Save_Img_Flag_ov2710)
//        {
//            memcpy(ov2710_data[num], ov2710_testdata, ov2710_g_width*ov2710_g_height);
//            num++;
//            Save_Img_Flag_ov2710--;
//            if(Save_Img_Flag_ov2710 == 0)
//            {
//                emit saveimg();
//            }
//        }
//        else
//        {
//            num = 0;
//        }
        emit newFrameGetted(*dispImg_ov2710);
        usleep(30000);
    }
}
