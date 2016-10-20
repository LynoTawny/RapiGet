#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T23:48:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RapiGet
TEMPLATE = app

SOURCES += main.cpp \
    gui/mainwindow.cpp \
    core/dltask.cpp \
    core/TorrentParser.cpp

HEADERS  += gui/mainwindow.h \
    core/dltask.h \
    core/interface.h \
    head.h \
    core/TorrentParser.h

FORMS    += gui/mainwindow.ui \
