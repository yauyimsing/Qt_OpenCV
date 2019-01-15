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
    contentfinder.cpp

INCLUDEPATH += D:\temp\opencv_mingw\install\include \
                    D:\work\qt\LibraryStatic0 \
                    D:\work\qt\library0 \
                    $$PWD\include

LIBS += D:\work\qt\LibraryStatic0\debug\libLibra*.a \
        D:\temp\opencv_mingw\install\x86\mingw\bin\libopencv_*.dll \


RC_ICONS = opencv.ico

FORMS += \
    qtform.ui \
    mainwindow.ui \
    showdialog.ui \
    viewform.ui

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
    contentfinder.h

RESOURCES += \
    images.qrc
