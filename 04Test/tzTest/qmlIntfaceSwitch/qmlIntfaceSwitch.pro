TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    testclass.cpp \
    demoov5640thread.cpp
HEADERS += \
    testclass.h \
    demoov5640thread.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

LIBS += -L$$PWD/lib -lIKUSBSDK  -lIKAlgAPI -lIKOV2710DVPAPI -lIKIRLAMPAPI -lIKOV5640MIPIAPI
LIBS += -lIKAlgoIR
LIBS +=  -llogger -llog4cpp -ljpeg

# Default rules for deployment.
include(deployment.pri)

