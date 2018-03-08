#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QQuickImageProvider>
#include <QQuickWindow>
#include <QImage>
#include <QThread>
#include "include/IKUSBSDK.h"
//#include "demoov5640thread.h"
class DemoOv2710Thread;
class idenWorker;
class ImagePaintEvent : public QObject
{
    Q_OBJECT
public:
    void RaisePaintEvent();
signals:
    void sigPaint();
};

class ScreenImageProvider : public QQuickImageProvider
{
public:
    ScreenImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {

    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)//这个是自动调用的。路径"image://screen"，如需要使用id等参数，如"image://screen/id"等
    {
        return this->img;
    }
    void setimage(QImage image)
    {
        img = image;
    }
    QImage img;
};

class testclass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tipInfo READ tipInfo WRITE setTipInfo NOTIFY tipInfoChanged)
    Q_PROPERTY(QString tipInfo2 READ tipInfo2 WRITE setTipInfo2 NOTIFY tipInfo2Changed)
    void setTipInfo(const QString &a);
    QString tipInfo() const;
    void setTipInfo2(const QString &a);
    QString tipInfo2() const;
signals:
    void tipInfoChanged();
    void tipInfo2Changed();
public:
    explicit testclass(QObject *parent = 0);

    ScreenImageProvider *imgProviderRGB;
    ScreenImageProvider *imgProviderIris;
private:
//    DemoOv5640Thread *ov5640framesThread;    //5640采集RGB线程
//    int qtnum_ov5640;    //计算帧率
//    struct timeval qtbegintv_ov5640;  //开始时间
//    struct timeval qtendtv_ov5640;    //结束时间
   QString m_tipInfo;
   QString m_tipInfo2;
signals:       
    void sigUpdateImageRGB();
    void sigUpdateImageIris();
    void startEnroll();
private:
    void loadIrisCodeList();
public slots:
    void showEnrollState(int state);
    void showIdenState(long index, int flag);
    void slotStartEnroll();
    void slotStartIden();

    void slotOnBtnOpenIrisDevClicked();
    void slotUpdateImageov2710();

    void slotOnBtnOpenRGBDevClicked();
//    void ov5640imageUpdated(QImage img);  //获取到图像后 刷新界面进行显示

    void slotOnBtnSaveImgIrisDevClicked();
    void slotOnBtnSaveImgRGBDevClicked();
public:

private:
    DemoOv2710Thread *ov2710framesThread;
    int qtnum_ov2710;
    struct timeval qtbegintv_ov2710;
    struct timeval qtendtv_ov2710;

    unsigned char *codeListL;
    unsigned char *codeListR;
    int codeNumL;
    int codeNumR;
    volatile bool idenState;
//红外灯
    unsigned int low_ns_ov2710;
    unsigned int hight_ns_ov2710;
    unsigned short reg_ov2710;
    unsigned char val_ov2710;
    unsigned char ir_state_ov2710;

    QThread enrollThread;  //注册线程
    QThread idenThread;
    idenWorker *idenWork;
};

#endif // TESTCLASS_H
