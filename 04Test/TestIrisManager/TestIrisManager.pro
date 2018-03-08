#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T14:58:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../03Code/IKAI1000QML/Common/Exectime.cpp \
    ../../03Code/Common/Logger.cpp \
    ../../03Code/IKAI1000QML/irismanager/irisData.cpp \
   ../../03Code/IKAI1000QML/irismanager/irisManager.cpp \
    ../../03Code/IKAI1000QML/irismanager/msqldatabase.cpp

HEADERS  += mainwindow.h \
    ../../03Code/IKAI1000QML/Common/Exectime.h \
    ../../03Code/Common/Logger.h \
    ../../03Code/IKAI1000QML/irismanager/featureCommon.h \
    ../../03Code/IKAI1000QML/irismanager/irisData.h \
    ../../03Code/IKAI1000QML/irismanager/irisManager.h \
    ../../03Code/IKAI1000QML/irismanager/msqldatabase.h


FORMS    += mainwindow.ui

LIBS += -luuid

INCLUDEPATH +=  ../Common
INCLUDEPATH += ../../03Code/IKAI1000QML/irismanager

#debug 和release 分别配置
CONFIG(debug,debug|release){
TARGET = TestIrisManager-Md   #linux下目录和程序同名有问题
}

CONFIG(release,debug|release){
TARGET = TestIrisManager-M    #linux下目录和程序同名有问题
}

target.path = /home/root
INSTALLS += target
