#-------------------------------------------------
#
# Project created by QtCreator 2014-03-07T00:45:57
#
#-------------------------------------------------

QT       += core gui network xml webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dict
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mtfetcher.cpp

HEADERS  += mainwindow.h \
    mtfetcher.h

FORMS    += mainwindow.ui
