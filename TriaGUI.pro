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
    triangle.cpp \
    point.cpp \
    data.cpp \
    segment.cpp \
    segmentstablemodel.cpp \
    graphicsscene.cpp \
    pointitem.cpp \
    graphicsview.cpp \
    segmentitem.cpp \
    triangleitem.cpp

HEADERS  += mainwindow.h \
    pointstablemodel.h \
    triangulation.h \
    triangle.h \
    point.h \
    data.h \
    segment.h \
    segmentstablemodel.h \
    graphicsscene.h \
    pointitem.h \
    graphicsview.h \
    segmentitem.h \
    triangleitem.h \
    simple_svg_1.0.0.hpp

FORMS    += mainwindow.ui \
    pointstablemodel.ui

RESOURCES += \
    resource.qrc
