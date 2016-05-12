#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T13:05:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Blob_Searching
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocessing.cpp

HEADERS  += mainwindow.h \
    imageprocessing.h

FORMS    += mainwindow.ui

unix:!macx|win32: LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d
