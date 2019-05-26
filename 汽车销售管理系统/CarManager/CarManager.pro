#-------------------------------------------------
#
# Project created by QtCreator 2015-11-29T09:16:55
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarManager
TEMPLATE = app


SOURCES += main.cpp\
        carmanager.cpp \
    histogram.cpp \
    pie.cpp

HEADERS  += carmanager.h \
    histogram.h \
    pie.h

FORMS    += carmanager.ui

CONFIG += c++11
