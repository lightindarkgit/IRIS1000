TEMPLATE = app

QT += qml quick
CONFIG += link_pkgconfig
CONFIG += c++11
CONFIG+= lang-en_GB lang-zh_CN disable-desktop

static{
QTPLUGIN+=qtvirtualkeyboardplugin
QT+=svg
}

SOURCES += main.cpp \
    testclass.cpp \
    enroll.cpp \
    idenworker.cpp
#    demoov5640thread.cpp
HEADERS += \
    testclass.h \
    enroll.h \
    idenworker.h
#    demoov5640thread.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH +=  ./include

LIBS += -L$$PWD/lib -lIKUSBSDK  -lIKAlgAPI -lIKOV2710DVPAPI -lIKIRLAMPAPI -lIKOV5640MIPIAPI
LIBS += -lIKAlgoIR
LIBS +=  -llogger -llog4cpp -ljpeg
