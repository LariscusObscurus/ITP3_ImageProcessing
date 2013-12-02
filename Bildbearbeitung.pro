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
    ueberdialog.cpp \
    Conversion.cpp \
    imagewidget.cpp \
    TestFilter.cpp

HEADERS  += mainwindow.h \
    ueberdialog.h \
    IOperation.h \
    Conversion.h \
    imagewidget.h \
    ringbuffer.h \
    TestFilter.h

FORMS    += mainwindow.ui \
    ueberdialog.ui

RESOURCES += \
    Icons.qrc

unix:!macx: LIBS += -lopencv_core

unix:!macx: LIBS += -lopencv_imgproc
