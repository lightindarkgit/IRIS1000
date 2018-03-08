#TARGET = SDM
TEMPLATE = lib#app#
#CONFIG += staticlib#  c++11
DEFINES += SDM_ALIGN_LIBRARY
#QMAKE_CXXFLAGS += -Wno-unused-parameter

HEADERS += \
    feature_descriptor.h \
    helper.h \
    hog.h \
    ldmarkmodel.h \
    modelcfg.h
    # modelsdm.h

SOURCES += \
    ldmarkmodel.cpp \
    hog.c \
    main.cpp
####配置opencv
#INCLUDEPATH += $$PWD/../../../3rdparty/opencv/include\
#               $$PWD/../../../3rdparty/opencv/include/opencv\
#               $$PWD/../../../3rdparty/opencv/include/opencv2

INCLUDEPATH += $$PWD/include

win32{
DEFINES +=Q_OS_WIN
}

unix{
DEFINES +=Q_OS_UNIX
}

#DESTDIR = $$PWD/../../../bin

#debug 和release 分别配置
CONFIG(debug,debug|release){

TARGET = SDMd

#LIBS += $$PWD/../../../3rdparty/opencv/opencv_core320d.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_imgproc320d.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_imgcodecs320d.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_highgui320d.lib
}
CONFIG(release,debug|release){

TARGET = SDM
#LIBS += $$PWD/../../../3rdparty/opencv/opencv_core320.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_imgproc320.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_imgcodecs320.lib\
#        $$PWD/../../../3rdparty/opencv/opencv_highgui320.lib
}

DISTFILES +=

RESOURCES +=
