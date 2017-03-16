#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T19:35:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_Feature_Detection_and_Matching
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    detection_matching.cpp \
    matching.cpp

HEADERS  += mainwindow.h \
    detection_matching.h \
    matching.h

FORMS    += mainwindow.ui \
    matching.ui

CONFIG +=link_pkgconfig
PKGCONFIG +=opencv

RESOURCES += \
    icon.qrc


