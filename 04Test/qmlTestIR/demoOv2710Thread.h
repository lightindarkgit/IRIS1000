/*
 * ov2710
*/
#ifndef DEMOOV2710THREAD_H
#define DEMOOV2710THREAD_H
#include <QObject>
#include <QThread>
#include <QImage>



class DemoOv2710Thread : public QThread
{
    Q_OBJECT

public:
    explicit DemoOv2710Thread(QObject *parent = 0);
    ~DemoOv2710Thread();
    void stopThread();
    void startThread();

signals:
    void newFrameGetted(QImage img);
//    void saveimg();
//    void saveimgok();

private slots:
//    void ov2710_saveimg();

protected:
    void run();

private:
    volatile bool stopped;
    QImage *dispImg;

public:
    char Save_Img_Flag_ov2710;
    char num_img_ov2710;
    unsigned char ov2710_data[50][1920*1080];

    QString file_str_ov2710;
    QString file_path_str_ov2710;
    char file_path_name_ov2710[256];

};
#endif
