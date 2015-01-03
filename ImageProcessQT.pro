#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T18:12:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestProject001
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocessing.cpp \
    myqlabel.cpp

HEADERS  += mainwindow.h \
    imageprocessing.h \
    myqlabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
