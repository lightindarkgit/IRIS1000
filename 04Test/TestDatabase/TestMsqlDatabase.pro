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
        ../../03Code/IKAI1000QML/irismanager/msqldatabase.cpp \
    sqlmanage.cpp

HEADERS  += mainwindow.h \
        ../../03Code/IKAI1000QML/irismanager/msqldatabase.h \
    sqlmanage.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/../../03Code/IKAI1000QML/irismanager
LIBS += -luuid


#debug 和release 分别配置
CONFIG(debug,debug|release){
TARGET = TestMsqlDatabase-Md   #linux下目录和程序同名有问题
}

CONFIG(release,debug|release){
TARGET = TestMsqlDatabase-M    #linux下目录和程序同名有问题
}

#target.path = /home/root
#INSTALLS += target
