#-------------------------------------------------
#
# Project created by QtCreator 2015-01-03T09:08:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyJson
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    jsonparser.cpp \
    dialog.cpp

RESOURCES += \
    myres.qrc

HEADERS += \
    jsonparser.h \
    dialog.h

FORMS += \
    dialog.ui
