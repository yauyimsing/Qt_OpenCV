QT += core
QT -= gui

CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += D:\temp\opencv_mingw\install\include \
                    D:\work\qt\LibraryStatic0

LIBS += D:\work\qt\LibraryStatic0\debug\libLibra*.a \
        D:\temp\opencv_mingw\install\x86\mingw\bin\libopencv_*.dll \
