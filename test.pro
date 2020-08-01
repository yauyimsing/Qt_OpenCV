greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core
QT -= gui

CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qtform.cpp \
    opencvclass.cpp \
    mainwindow.cpp \
    opencvfunction.cpp \
    colordetectcontroller.cpp \
    colordetector.cpp \
    showdialog.cpp \
    histogram1d.cpp \
    viewform.cpp \
    colorhistogram.cpp \
    cmdaction.cpp \
    imagelabel.cpp \
    contentfinder.cpp \
    eventlineedit.cpp \
    testform.cpp \
    singleimageform.cpp \
    command.cpp

INCLUDEPATH += E:\OpenCV\opencv_3_4_1_build_x64\install\include \
                    $$PWD\include

LIBS += -LE:\OpenCV\opencv_3_4_1_build_x64\install\x64\vc12\lib \
    -lopencv_core341d \
    -lopencv_imgproc341d \
    -lopencv_highgui341d \
    -lopencv_ml341d \
    -lopencv_video341d \
    -lopencv_features2d341d \
    -lopencv_calib3d341d \
    -lopencv_objdetect341d \
    -lopencv_dnn341d \
    -lopencv_flann341d \
    -lopencv_imgcodecs341d \
    -lopencv_photo341d \
    -lopencv_shape341d \
    -lopencv_stitching341d \
    -lopencv_superres341d \
    -lopencv_videoio341d \
    -lopencv_videostab341d


RC_ICONS = opencv.ico

FORMS += \
    qtform.ui \
    mainwindow.ui \
    showdialog.ui \
    viewform.ui \
    testform.ui \
    singleimageform.ui

HEADERS += \
    qtform.h \
    ui_qtform.h \
    opencvclass.h \
    ui_mainwindow.h \
    mainwindow.h \
    opencvfunction.h \
    colordetectcontroller.h \
    colordetector.h \
    showdialog.h \
    ui_showdialog.h \
    histogram1d.h \
    viewform.h \
    colorhistogram.h \
    cmdaction.h \
    imagelabel.h \
    ui_viewform.h \
    contentfinder.h \
    eventlineedit.h \
    testform.h \
    ui_testform.h \
    singleimageform.h \
    command.h

RESOURCES += \
    imageResource.qrc
