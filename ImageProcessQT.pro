#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T18:12:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessQT
TRANSLATIONS = $${TARGET}_el_GR.ts $${TARGET}_de.ts $${TARGET}_pl.ts
CODECFORSRC = UTF-8

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocessing.cpp \
    myqlabel.cpp \
    myqimage.cpp

HEADERS  += mainwindow.h \
    imageprocessing.h \
    myqlabel.h \
    myqimage.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc \
    translations.qrc

DISTFILES +=

win32 {
    copyfiles.commands = @call copy ..\\$${TARGET}\\*.qm $${DESTDIR}\\
}
