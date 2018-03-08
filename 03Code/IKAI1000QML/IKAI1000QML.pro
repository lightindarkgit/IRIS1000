TEMPLATE = app

QT += qml quick sql multimedia
CONFIG += c++11
QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp \
    demoov5640thread.cpp \
    userlistmodel.cpp \
    irismanager/irisData.cpp \
    irismanager/irisManager.cpp \
    irismanager/msqldatabase.cpp \
    Common/common.cpp \
    Common/Exectime.cpp \
    usermanage.cpp \
    ThreadEnroll.cpp \
    mainclass.cpp \
    idenworker.cpp \
    facetrack.cpp \
    hid/ptzbase.cpp \
    hid/pwm.cpp \
    sound/playsounds.cpp \
    Common/settingfile.cpp

HEADERS += \
    demoov5640thread.h \
    userlistmodel.h \
    include/IKUSBSDK.h \
    include/OV5640MipiApi.h \
    irismanager/featureCommon.h \
    irismanager/irisData.h \
    irismanager/irisManager.h \
    irismanager/msqldatabase.h \
    Common/common.h \
    Common/Exectime.h \
    usermanage.h \
    ThreadEnroll.h \
    mainclass.h \
    idenworker.h \
    facetrack.h \
    include/tracker.h \
    hid/ptzbase.h \
    hid/pwm.h \
    hid/pwmdata.h \
    include/wiegandrw.h \
    sound/playsounds.h \
    Common/settingfile.h

RESOURCES += qml.qrc \
    image.qrc
INCLUDEPATH +=. \
         ./Common \
         ./include \
         ./sound \
        ./irismanager \
        ./hid

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

LIBS += -L$$PWD/lib -lIKUSBSDK  -lIKAlgAPI -lIKOV2710DVPAPI -lIKIRLAMPAPI -lIKOV5640MIPIAPI
LIBS += -lIKAlgoIR
LIBS += -lIKAlgoFaceDetect -lIKAlgoFaceKd -lKCFTracking
LIBS +=  -llogger -llog4cpp -ljpeg -luuid -lWIEGANDRW
# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

DEFINES += QT_MESSAGELOGCONTEXT
