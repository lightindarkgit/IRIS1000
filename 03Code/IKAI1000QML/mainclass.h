/*************************************************
Copyright: 中科虹霸
作者: lhc, gw, tz, hyq
创建日期: 2018-02-09
描述: QML和C++中间处理的主代码
**************************************************/
#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include <QQuickImageProvider>
#include <QQuickWindow>
#include <QImage>
#include "include/IKUSBSDK.h"
#include "demoov5640thread.h"
#include "msqldatabase.h"
#include "include/wiegandrw.h"

const QString questionerFaceDir = "/home/root/QuestionerFaces/";

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
        Q_UNUSED(id);
        Q_UNUSED(size);
        Q_UNUSED(requestedSize);
        return this->img;
    }
    void setimage(QImage image)
    {
        img = image;
    }
    QImage img;
};
class ThreadSwipeCard : public QThread
{
    Q_OBJECT

public:
    explicit ThreadSwipeCard(QObject *parent = 0);
signals:
    void sigSendCarNum(int hid,int pid);
protected:
    void run();   //线程
public:
    bool startSwipeCardFlg;
    wiegandrw* wiegand;
    bool stopped;
};

class ThreadEnroll;
class idenWorker;
class playSounds;
class mainClass : public QObject
{
    Q_OBJECT
public:
    explicit mainClass(QObject *parent = 0);
    Q_PROPERTY(QString msgText READ getmsgText WRITE setmsgText NOTIFY msgTextChanged)

    Q_PROPERTY(int leftNum READ getleftNum WRITE setleftNum NOTIFY leftNumChanged)
    Q_PROPERTY(int rightNum READ getrightNum WRITE setrightNum NOTIFY rightNumChanged)

    Q_PROPERTY(bool ableCapImage READ ableCapImage WRITE setAbleCapImage)  //qml->c++ qml显示完成，请求下一张图

    Q_PROPERTY(bool ableCapIris READ ableCapIris WRITE setAbleCapIris)  //qml->c++ qml显示完成，请求下一张图2710显示用

    Q_PROPERTY(bool identFlag READ identFlag WRITE setIdentFlag)        //qml->c++ 识别状态标志位

    Q_PROPERTY(bool qmlStartEnroll READ qmlStartEnroll WRITE setQmlStartEnroll)

    Q_PROPERTY(int irisEnrMode READ irisEnrMode WRITE setIrisEnrMode)

    Q_PROPERTY(bool  startSwipeCard READ getStartSwipeCard WRITE setStartSwipeCard)

    QString getmsgText() const;
    void setmsgText(const QString &tmp);
//设置5640采图线程是否可以发送图像函数
    void setAbleCapImage(const bool flag);
    bool ableCapImage();   //避免警告，无用
//设置虹膜回调函数是否可以采集图像并发送图像函数
    void setAbleCapIris(const bool flag);
    bool ableCapIris();  //避免警告，无用

//设置注册线程状态函数
    void setQmlStartEnroll(const bool flag);
    bool qmlStartEnroll();   //避免警告，无用


    Q_INVOKABLE void getUserIrisImg(const QString &uid);

//    Q_INVOKABLE void saveAddUserFromQML(QVariantMap map);
//设置识别线程状态函数
    void setIdentFlag(const bool flag);
    bool identFlag();   //避免警告，无用

    void setleftNum(const int tmp);
    int getleftNum();
    void setrightNum(const int tmp);
    int getrightNum();

    int irisEnrMode() const;
    void setIrisEnrMode(const int &mode);

    bool getStartSwipeCard();
    void setStartSwipeCard(bool tmp);

    ScreenImageProvider *imgProviderRGB;
    ScreenImageProvider *imgProviderIris;
    ScreenImageProvider *imgProIrisImgL;
    ScreenImageProvider *imgProIrisImgR;
private:
//加载虹膜特征
    void loadIrisCodeList();
    QImage GetImg(const unsigned char *buffer, int bufferSize);

    void initSteering();        // added at 20180302 by yqhe, 初始化舵机

    //存疑人员存图处理
    void saveQuestionerFaceHandle();

private:
    DemoOv5640Thread *m_pOv5640framesThread;    //5640采集RGB线程
    int qtnum_ov5640;    //计算帧率
    struct timeval qtbegintv_ov5640;  //开始时间
    struct timeval qtendtv_ov5640;    //结束时间    

    QThread m_enrollThread;   //注册线程变量
    ThreadEnroll *m_pEnrollWork;   //注册工作线程
    QString m_msgText;
    int m_leftNum; //左眼注册进度
    int m_rightNum;//右眼注册进度
    int m_irisEnrMode; //注册模式
    //存疑人员相关
    bool m_isSuspect;
    QString oldMonthStr;

    idenWorker  *m_pIdenWork;  //识别工作线程
    QThread m_idenThread;         //识别线程变量

    ThreadSwipeCard *m_pSwipeCard; // 刷卡线程

//普通人员数据虹膜数据
    unsigned char *m_pCodeListL;  //左眼虹膜数据地址指针
    unsigned char *m_pCodeListR; //右眼虹膜数据地址指针
    int m_codeNumL;     //左眼数量
    int m_codeNumR;     //右眼数量
//管理员虹膜数据
    unsigned char *m_pAdminCodeListL;  //左眼虹膜数据地址指针
    int       m_adminCodeNumL;               //左眼数量
    unsigned char *m_pAdminCodeListR;  //右眼虹膜数据地址指针
    int       m_adminCodeNumR;               //右眼数量

    QList<PIRISUserInfo> m_infoLis;      //注册成功要保存到数据库里的参数
    QList<PIRISEnrPara> m_enrollInfoList;   //注册成功要保存到数据库里的参数

    playSounds   *m_pPlaySound;    //播放声音的

signals:       
    void sigPersonTableUpdated();
    void sigUpdateImageRGB();
    void sigUpdateImageIris();
    void sigUpdateAddIrisImg(int left, int right);
    void sigUpdateEditIrisImg(int left, int right);
    void msgTextChanged();
    void leftNumChanged();
    void rightNumChanged();

    void cppIdentResult(int index, QString strName, QString strID);  //index :0成功，1失败，2终止 ; strName，用作传递姓名或者消息;strID 识别成功时传递用户id，其他时候填写空字符串即可
    void cppEnrollResult(int result, QString str);  //result :   0:"注册成功"; 1:"注册失败";2:"注册终止";3"注册结束"(不是成功);

    void sigQmlCarNum(int hid,int pid);

public slots:
    void slotOnBtnOpenIrisDevClicked();   //初始化 sdk 槽函数
    void slotUpdateImageov2710();

    void slotOnBtnOpenRGBDevClicked();
    void ov5640imageUpdated(QImage img);  //获取到图像后 刷新界面进行显示

    void slotOnBtnSaveImgIrisDevClicked();
    void slotOnBtnSaveImgRGBDevClicked();

//  保存人员成功后继续保存虹膜数据，将注册人员信息及虹膜信息保存到数据库
    void savePersonIrisData(DBPersonInfo personInfo);

    void slotReciveCarNum(int hid,int pid);



private slots:
//接收注册成功发过来的虹膜信息，并保存
    void saveEnrollIrisData(IKSDKIrisInfo* enrIrisL, int numEnrL, IKSDKIrisInfo* enrIrisR, int numEnrR, IKResultFlag IKflag);
//接收注册状态，并显示到界面
    void showEnrollState(int state);
//接收识别状态，并显示到界面
    void showIdenState(long index, int flag);

public:
};

#endif // MAINCLASS_H
