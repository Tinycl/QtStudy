#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T08:52:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 04_QEvent
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mylabel.cpp \
    mybutton.cpp

HEADERS  += mywidget.h \
    mylabel.h \
    mybutton.h

FORMS    += mywidget.ui

CONFIG += c++11
