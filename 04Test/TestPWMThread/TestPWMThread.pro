#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T14:58:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \ 
    ../../03Code/IKAI1000QML/hid/ptzbase.cpp \
    ../../03Code/IKAI1000QML/hid/pwm.cpp

HEADERS  += mainwindow.h \ 
    ../../03Code/IKAI1000QML/hid/ptzbase.h \
    ../../03Code/IKAI1000QML/hid/pwm.h \
    ../../03Code/IKAI1000QML/hid/pwmdata.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../../03Code/IKAI1000QML/hid

#debug 和release 分别配置
CONFIG(debug,debug|release){
TARGET = TestPWMThreadd
}

CONFIG(release,debug|release){
TARGET = TestPWMThread
}

#target.path = /home/root
#INSTALLS += target
