#-------------------------------------------------
#
# Project created by QtCreator 2017-06-30T16:37:49
#
#-------------------------------------------------

QT       -= gui
CONFIG   += plugin

TARGET   = KCFTracking
TEMPLATE = lib #app#
DESTDIR  = $$PWD/../../../lib

DEFINES  += KCF_ALIGN_LIBRARY

#CONFIG += staticlib
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += $$PWD/libFaceDetect
INCLUDEPATH += $$PWD/fbc_cv/include
INCLUDEPATH += $$PWD/SDM


#unix {  #lhc去掉
#    target.path = /usr/lib
#    INSTALLS += target
#}

win32{
DEFINES +=Q_OS_WIN
LIBS += $$PWD/libFaceDetect/IKAlgoFaceDetect.lib
message('win32');
}

unix {
   DEFINES +=Q_OS_UNIX
message('unix');
}
CONFIG(debug,debug|release){
TARGET = KCFTrackingd
DEFINES += _DEBUG
unix{
    LIBS += $$PWD/SDM/libKD_d.so
}
}

CONFIG(release,debug|release){
TARGET = KCFTracking
unix{
#    LIBS  += $$PWD/libFaceDetect/LINUX32/libIKAlgoFaceDetect.so
##    LIBS += $$PWD/SDM/libKD.so
#    LIBS += $$PWD/SDM/libIKAlgoFaceKd.so
LIBS += -L../../../lib
LIBS  +=-lIKAlgoFaceDetect
LIBS  +=-lIKAlgoFaceKd
}
}

HEADERS += \
    fhog.hpp \
    kcftracker.hpp \
    tracker.h \
    ffttools.h \
    fbc_cv/include/dft.hpp \
    fbc_cv/include/core/mat.hpp \
    publicdata.h \
    thread.hpp

SOURCES += \
    fhog.cpp \
    kcftracker.cpp \
    runtracker.cpp \
    tools.cpp \
    detecttracking.cpp \
    publicdata.cpp
