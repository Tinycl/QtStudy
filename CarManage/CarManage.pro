#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T09:38:20
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarManage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domxml.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    domxml.h \
    histogram.h

FORMS    += mainwindow.ui
