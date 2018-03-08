QT += core
QT -= gui

CONFIG += c++11

TARGET = Testpwm
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../03Code/IKAI1000QML/hid/pwm.cpp

HEADERS += \
    ../../03Code/IKAI1000QML/hid/pwm.h \
    ../../03Code/IKAI1000QML/hid/pwmdata.h

INCLUDEPATH += ../../03Code/IKAI1000QML/hid/
