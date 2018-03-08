/*************************************************
Copyright: 中科虹霸
作者: lhc, gw, tz, hyq
创建日期: 2018-03-06
描述:  读取配置文件的类
**************************************************/
#include "settingfile.h"
settingFile* settingFile::_instance = 0;

settingFile *settingFile::instance()
{
    if (settingFile::_instance == 0)
    {
        settingFile::_instance = new settingFile();
    }
    return settingFile::_instance;
}

void settingFile::Release()
{
    _instance->close();
    delete _instance;
    _instance = 0;
}

void settingFile::setPresseds(const bool flag)
{
    this->settings->setValue("pressed", flag);
    this->settings->sync();
}

bool settingFile::pressed()
{
    bool pres = this->settings->value("pressed", false).toBool();
    return pres;
}

void settingFile::setVoice(const bool flag)
{
    this->settings->setValue("voice", flag);
    this->settings->sync();
}

bool settingFile::voice()
{
    bool voice = this->settings->value("voice", false).toBool();
    return voice;
}

void settingFile::setVolume(const int vol)
{
    this->settings->setValue("volume", vol);
    this->settings->sync();
}

int settingFile::volume()
{
    bool volume = this->settings->value("volume", 3).toInt();
    return volume;
}

void settingFile::setWiegand(const int wg)
{
    this->settings->setValue("wiegand", wg);
    this->settings->sync();
}

int settingFile::wiegand()
{
    bool wiegand = this->settings->value("wiegand", 0).toInt();
    return wiegand;
}

void settingFile::setIo(const bool io)
{
    this->settings->setValue("io", io);
    this->settings->sync();
}

bool settingFile::io()
{
    bool io = this->settings->value("io", false).toBool();
    return io;
}

void settingFile::setUserVeri(const int uv)
{
    this->settings->setValue("UserVeri", uv);
    this->settings->sync();
}

int settingFile::userVeri()
{
    bool userVeri = this->settings->value("UserVeri", 2).toInt();
    return userVeri;
}

void settingFile::setAdminV(const int admin)
{
    this->settings->setValue("adminV", admin);
    this->settings->sync();
}

int settingFile::adminV()
{
    bool adminV = this->settings->value("adminV", 2).toInt();
    return adminV;
}

void settingFile::setFace(const bool fc)
{
    this->settings->setValue("face", fc);
    this->settings->sync();
}

bool settingFile::face()
{
    bool face = this->settings->value("face", false).toBool();
    return face;
}

void settingFile::setCopyright(QString cp)
{
    this->settings->setValue("copyright", cp);
    this->settings->sync();
}

QString settingFile::copyright()
{
    QString cp = this->settings->value("copyright", "北京中科虹霸科技有限公司").toString();
    return cp;
}

void settingFile::setAddress(QString ad)
{
    this->settings->setValue("address", ad);
    this->settings->sync();
}

QString settingFile::address()
{
    QString ad = this->settings->value("address", "北京市海淀区银谷大厦702").toString();
    return ad;
}

void settingFile::setTel(QString tel)
{
    this->settings->setValue("tel", tel);
    this->settings->sync();
}

QString settingFile::tel()
{
    QString tel = this->settings->value("tel", "010-5120343-8899").toString();
    return tel;
}

settingFile::settingFile()
{
    settings = nullptr;
    _instance->open();
}

void settingFile::open()
{
    if(settings == nullptr)
    {
        settings = new QSettings("/home/root/AI1000Set.ini", QSettings::IniFormat);
    }
}

void settingFile::close()
{
    settings->sync();
    settings->deleteLater();
}
