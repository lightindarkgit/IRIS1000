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
    demoov5640thread.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    testclass.h \
    demoov5640thread.h

LIBS += -L$$PWD/lib -lIKUSBSDK  -lIKAlgAPI -lIKOV2710DVPAPI -lIKIRLAMPAPI -lIKOV5640MIPIAPI
LIBS += -lIKAlgoIR
LIBS +=  -llogger -llog4cpp -ljpeg
