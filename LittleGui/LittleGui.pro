#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T11:37:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LittleGui
TEMPLATE = app


SOURCES += main.cpp\
        littlegui.cpp \
    circle.cpp \
    imageprocessing.cpp

HEADERS  += littlegui.h \
    circle.h \
    imageprocessing.h \
    imageprocessing_global.h

FORMS    += littlegui.ui

unix:!macx|win32: LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
