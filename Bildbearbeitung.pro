#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T10:20:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    ueberdialog.cpp \
    Conversion.cpp \
    imagewidget.cpp \
    colordisplaywidget.cpp \
    sizedialogue.cpp \
    filters/BilateralFilter.cpp \
    filters/Blur.cpp \
    filters/Canny.cpp \
    filters/Dilation.cpp \
    filters/Erosion.cpp \
    filters/GaussianBlur.cpp \
    filters/Grayscale.cpp \
    filters/MedianBlur.cpp \
    filters/Outline.cpp \
    filters/Sobel.cpp \
    filters/TestFilter.cpp \
    Utility.cpp

HEADERS  += \
    colordisplaywidget.hpp \
    Conversion.hpp \
    Exception.hpp \
    imagewidget.hpp \
    IOperation.hpp \
    mainwindow.hpp \
    ringbuffer.hpp \
    sizedialogue.hpp \
    ueberdialog.hpp \
    filters/BilateralFilter.hpp \
    filters/Blur.hpp \
    filters/Canny.hpp \
    filters/Dilation.hpp \
    filters/Erosion.hpp \
    filters/GaussianBlur.hpp \
    filters/Grayscale.hpp \
    filters/MedianBlur.hpp \
    filters/Outline.hpp \
    filters/Sobel.hpp \
    filters/TestFilter.hpp \
    Utility.hpp

FORMS    += mainwindow.ui \
    ueberdialog.ui \
    sizedialogue.ui

RESOURCES += \
    Icons.qrc

unix: QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11

unix:!macx: LIBS += -lopencv_core
unix:!macx: LIBS += -lopencv_imgproc

unix: QMAKE_CXXFLAGS += -std=c++11
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
