/*************************************************
Copyright: 中科虹霸
作者: lhc
创建日期: 2018-03-05
描述: 播放声音的类，请将声音文件放到执行程序目录下的sounds目录下
**************************************************/
#include "playsounds.h"
#include <QSound>
#include <QCoreApplication>
/*****************************************************************************
 *                         构造函数
 *  函 数 名：playSounds
 *  功    能：构造函数
 *  说    明：
 *  参    数：QObject *parent
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-03-05
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
playSounds::playSounds(QObject *parent) : QObject(parent)
{
    m_pSound = new QSound("");
}
/*****************************************************************************
 *                         析构函数
 *  函 数 名：~playSounds
 *  功    能：析构函数
 *  说    明：
 *  参    数：无
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-03-05
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
playSounds::~playSounds()
{
    m_pSound->deleteLater();
}
/*****************************************************************************
 *                         声音播放函数
 *  函 数 名：Play
 *  功    能：声音播放函数
 *  说    明： 请将声音文件放到执行程序目录下的sounds目录下
 *  参    数：SoundID soundType
 *  返 回 值：无
 *  创 建 人：李翰臣
 *  创建时间：2018-03-05
 *  修 改 人：
 *  修改时间：
 *****************************************************************************/
void playSounds::Play(SoundID soundType)
{
    QString fileName = QCoreApplication::applicationDirPath();

    switch (soundType)
    {
    case CLOSER:
        fileName += "/sounds/010closer.wav";
        break;
    case FARTHER:
        fileName += "/sounds/018farther.wav";
        break;
    case ENROLLSUCC:
        fileName += "/sounds/003enrollsucc.wav";
        break;
    case ENROLLSTOP:
        fileName += "/sounds/006enrollstop.wav";
        break;
    case IDENSUCC:
        fileName += "/sounds/002idensucc.wav";
        break;
    case RETRY:
        fileName += "/sounds/005retry.wav";
        break;
    case SLOW:
        fileName += "/sounds/107slow.wav";
        break;
    case CAMERA:
        fileName += "/sounds/015-camera.wav";
        break;
    case KEEP:
        fileName += "/sounds/100keep.wav";
        break;
    case UP:
        fileName += "/sounds/103up.wav";
        break;
    case DOWN:
        fileName += "/sounds/102down.wav";
        break;
    case LEFT:
        fileName += "/sounds/105left.wav";
        break;
    case RIGHT:
        fileName += "/sounds/104down.wav";
        break;
    case THANKS:
        fileName += "/sounds/004thanks.wav";
        break;
    case WELCOME:
        fileName += "/sounds/016welcome.wav";
        break;
    }
    if(!m_pSound->isFinished())
    {
        m_pSound->stop();
    }
    m_pSound->play(fileName);
}
