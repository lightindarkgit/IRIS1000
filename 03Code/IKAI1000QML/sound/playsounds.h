/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-03-05
描述: 播放声音的类
**************************************************/
#ifndef PLAYSOUNDS_H
#define PLAYSOUNDS_H

#include <QObject>

typedef enum SoundID
{
    //靠近，靠远
    CLOSER =0 ,
    FARTHER ,

    ENROLLSUCC,
    IDNAME,
    IDENSUCC,

    RETRY,
    ENROLLSTOP,

    SLOW,
    KEEP,
    UP,
    DOWN,
    LEFT,
    RIGHT,

    CAMERA,

    THANKS,
    WELCOME,
    BLINK,
    OPENNESS
} AudioID;
class QSound;
class playSounds : public QObject
{
    Q_OBJECT
public:
    //构造函数
    explicit playSounds(QObject *parent = 0);
    //析构
    ~playSounds();
    //播放声音，单次，不循环
    void Play(SoundID soundType);

signals:

public slots:
private:
    QSound *m_pSound;   //qsound播放声音

};

#endif // PLAYSOUNDS_H
