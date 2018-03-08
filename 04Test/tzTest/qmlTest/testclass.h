#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QQuickImageProvider>
#include <QQuickWindow>
#include <QImage>
#include "include/IKUSBSDK.h"
#include "demoov5640thread.h"

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
public:
    explicit testclass(QObject *parent = 0);

    ScreenImageProvider *imgProviderRGB;
    ScreenImageProvider *imgProviderIris;
private:
    DemoOv5640Thread *ov5640framesThread;    //5640采集RGB线程
    int qtnum_ov5640;    //计算帧率
    struct timeval qtbegintv_ov5640;  //开始时间
    struct timeval qtendtv_ov5640;    //结束时间

signals:       
    void sigUpdateImageRGB();
    void sigUpdateImageIris();

public slots:
    void slotOnBtnOpenIrisDevClicked();
    void slotUpdateImageov2710();

    void slotOnBtnOpenRGBDevClicked();
    void ov5640imageUpdated(QImage img);  //获取到图像后 刷新界面进行显示

    void slotOnBtnSaveImgIrisDevClicked();
    void slotOnBtnSaveImgRGBDevClicked();
public:
};

#endif // TESTCLASS_H
