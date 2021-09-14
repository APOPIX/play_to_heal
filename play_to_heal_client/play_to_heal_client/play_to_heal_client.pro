#-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T19:14:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = play_to_heal_client
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    mainwindow.cpp \
    gmfmdialog.cpp \
    commandlinethread.cpp \
    scenecognitiondialog.cpp \
    emotionalabilitydialog.cpp

HEADERS  += loginwindow.h \
    settings.h \
    mainwindow.h \
    gmfmdialog.h \
    commandlinethread.h \
    scenecognitiondialog.h \
    emotionalabilitydialog.h

FORMS    += loginwindow.ui \
    mainwindow.ui \
    gmfmdialog.ui \
    scenecognitiondialog.ui \
    emotionalabilitydialog.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_video.so \
        /usr/local/lib/libopencv_videoio.so \
        /usr/local/lib/libopencv_videostab.so \
        /usr/lib/arm-linux-gnueabihf/libv4l/v4l1compat.so\
        -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_video \
        -lopencv_videoio \
        -lopencv_videostab \
