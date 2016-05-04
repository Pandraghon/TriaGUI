#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T13:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TriaGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pointstablemodel.cpp \
    triangulation.cpp \
    point.cpp \
    data.cpp \
    segment.cpp \
    segmentstablemodel.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    pointstablemodel.h \
    triangulation.h \
    point.h \
    data.h \
    segment.h \
    segmentstablemodel.h \
    renderarea.h

FORMS    += mainwindow.ui \
    pointstablemodel.ui
