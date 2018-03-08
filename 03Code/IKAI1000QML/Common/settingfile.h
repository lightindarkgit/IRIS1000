/*************************************************
Copyright: 中科虹霸
作者: lhc, gw, tz, hyq
创建日期: 2018-03-06
描述:  读取配置文件的类

pressed   true,false  是否有按键音     如果配置文件不写，默认false
voice        true,false  是否有语音提示   如果配置文件不写，默认false
volume    0,1,2,3,4,5 声音大小     如果配置文件不写，默认3
Wiegand  0--禁用, 1--24, 2--26    如果配置文件不写，默认0
IO             false--禁用, true--开启           如果配置文件不写，默认false
UserVeri   0--虹膜或卡, 1--虹膜和卡, 2--虹膜, 3--卡   如果配置文件不写，默认2
AdminV    0--虹膜或卡, 1--虹膜和卡, 2--虹膜, 3--卡    如果配置文件不写，默认2
face          false--禁用, true--开启  人脸验证暂时禁用

ServerIP      字符串     服务器IP，暂时不可修改
ServerPort   字符串    服务器端口，暂时不可修改

下面三个在代码中有默认值，如果配置文件不写，就是中科虹霸的信息
copyright   版权所有      北京中科虹霸科技有限公司
address     公司地址       北京市海淀区银谷大厦702
tel               公司电话      010-5120343-8899
**************************************************/
#ifndef SETTINGFILE_H
#define SETTINGFILE_H
#include <QSettings>

class settingFile
{
public:
    static settingFile* instance();
    static void Release();   //释放
    Q_PROPERTY(bool pressed READ pressed WRITE setPresseds)  //按键音
    Q_PROPERTY(bool voice READ voice WRITE setVoice)                 //语音提示
    Q_PROPERTY(int volume READ volume WRITE setVolume)         //声音大小
    Q_PROPERTY(int wiegand READ wiegand WRITE setWiegand)    //韦根参数
    Q_PROPERTY(bool io READ io WRITE setIo)                                   //io参数
    Q_PROPERTY(int userVeri READ userVeri WRITE setUserVeri)      //用户验证方式
    Q_PROPERTY(int adminV READ adminV WRITE setAdminV)        //管理员验证方式
    Q_PROPERTY(bool face READ face WRITE setFace)                          //人脸验证开启
    Q_PROPERTY(QString copyright READ copyright WRITE setCopyright)      //版权信息
    Q_PROPERTY(QString address READ address WRITE setAddress)      //地址信息
    Q_PROPERTY(QString tel READ tel WRITE setTel)      //地址信息

    void setPresseds(const bool flag);
    bool pressed();
    void setVoice(const bool flag);
    bool voice();
    void setVolume(const int vol);
    int  volume();
    void setWiegand(const int wg);
    int wiegand();
    void setIo(const bool io);
    bool io();
    void setUserVeri(const int uv);
    int userVeri();
    void setAdminV(const int admin);
    int adminV();
    void setFace(const bool fc);
    bool face();

    void setCopyright(QString cp);
    QString copyright();
    void setAddress(QString ad);
    QString address();
    void setTel(QString tel);
    QString tel();

private:
    settingFile();  //私有构造函数
    void open();    //打开
    void close();   //关闭
private:
    static settingFile* _instance;
    QSettings *settings;
};

#endif // SETTINGFILE_H
