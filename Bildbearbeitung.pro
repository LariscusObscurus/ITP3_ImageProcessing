#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T10:20:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bildbearbeitung
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    ueberdialog.cpp

HEADERS  += mainwindow.h \
    ueberdialog.h

FORMS    += mainwindow.ui \
    ueberdialog.ui

RESOURCES += \
    Icons.qrc
