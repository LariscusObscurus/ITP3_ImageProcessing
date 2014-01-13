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
    filters/TestFilter.cpp \
    filters/MedianBlur.cpp \
    filters/GaussianBlur.cpp \
    filters/Erosion.cpp \
    filters/Dilation.cpp \
    filters/Blur.cpp \
    filters/BilateralFilter.cpp \
    filters/Outline.cpp \
    filters/Grayscale.cpp \
    colordisplaywidget.cpp \
    sizedialogue.cpp \
    filters/Sobel.cpp \
    filters/Canny.cpp

HEADERS  += mainwindow.h \
    ueberdialog.h \
    IOperation.h \
    Conversion.h \
    imagewidget.h \
    ringbuffer.h \
    Exception.h \
    filters/TestFilter.h \
    filters/MedianBlur.h \
    filters/GaussianBlur.h \
    filters/Erosion.h \
    filters/Dilation.h \
    filters/Blur.h \
    filters/BilateralFilter.h \
    filters/Outline.h \
    filters/Grayscale.h \
    colordisplaywidget.h \
    sizedialogue.h \
    filters/Sobel.h \
    filters/Canny.h

FORMS    += mainwindow.ui \
    ueberdialog.ui \
    sizedialogue.ui

RESOURCES += \
    Icons.qrc

unix:!macx: LIBS += -lopencv_core

unix:!macx: LIBS += -lopencv_imgproc

uinx: QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11

win32-msvc2012:!contains(QMAKE_HOST.arch, x86_64): {
	CONFIG(release, debug|release): LIBS += -L$$PWD/dep/lib/x86/ -lopencv_core248
	else:CONFIG(debug, debug|release): LIBS += -L$$PWD/dep/lib/x86/ -lopencv_core248d
	CONFIG(release, debug|release): LIBS += -L$$PWD/dep/lib/x86/ -lopencv_imgproc248
	else:CONFIG(debug, debug|release): LIBS += -L$$PWD/dep/lib/x86/ -lopencv_imgproc248d
	INCLUDEPATH += $$PWD/dep/lib/x86
	DEPENDPATH += $$PWD/dep/lib/x86
}

win32-msvc2012:contains(QMAKE_HOST.arch, x86_64): {
	CONFIG(release, debug|release): LIBS += -L$$PWD/dep/lib/x64/ -lopencv_core248
	else:CONFIG(debug, debug|release): LIBS += -L$$PWD/dep/lib/x64/ -lopencv_core248d
	CONFIG(release, debug|release): LIBS += -L$$PWD/dep/lib/x64/ -lopencv_imgproc248
	else:CONFIG(debug, debug|release): LIBS += -L$$PWD/dep/lib/x64/ -lopencv_imgproc248d
	INCLUDEPATH += $$PWD/dep/lib/x64
	DEPENDPATH += $$PWD/dep/lib/x64
}

win32: INCLUDEPATH += $$PWD/dep/inc
