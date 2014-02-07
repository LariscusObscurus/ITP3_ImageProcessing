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
    Utility.cpp \
    color/Grayscale.cpp \
    filter/BilateralFilter.cpp \
    filter/Blur.cpp \
    filter/Canny.cpp \
    filter/Dilation.cpp \
    filter/Erosion.cpp \
    filter/GaussianBlur.cpp \
    filter/MedianBlur.cpp \
    filter/Outline.cpp \
    filter/Sobel.cpp \
    filter/TestFilter.cpp \
    tool/Brush.cpp \
    tool/Flood.cpp \
    tool/Pencil.cpp \
    tool/BasicTool.cpp \
    SavePopupDialog.cpp \
    LiveFilterDialog.cpp \
    tool/AirBrush.cpp

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
    Utility.hpp \
    filter/BilateralFilter.hpp \
    filter/Blur.hpp \
    filter/Canny.hpp \
    filter/Dilation.hpp \
    filter/Erosion.hpp \
    filter/GaussianBlur.hpp \
    filter/MedianBlur.hpp \
    filter/Outline.hpp \
    filter/Sobel.hpp \
    filter/TestFilter.hpp \
    tool/Brush.hpp \
    tool/Flood.hpp \
    tool/Pencil.hpp \
    tool/BasicTool.hpp \
    OperationType.hpp \
    SavePopupDialog.hpp \
    LiveFilterDialog.hpp \
    color/Grayscale.hpp \
    tool/AirBrush.hpp

FORMS    += mainwindow.ui \
    ueberdialog.ui \
    sizedialogue.ui \
    SavePopupDialog.ui \
    LiveFilterDialog.ui

RESOURCES += \
    Icons.qrc

unix: QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11

unix:!macx: LIBS += -lopencv_core
unix:!macx: LIBS += -lopencv_imgproc

unix: QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11

# Debug Code
unix:CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -g
win32-g++:CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -g
win32-msvc2012:CONFIG(debug, debug|release): QMAKE_CXXFLAGS += /Zi

# Optimiere Code
unix:CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
win32-g++:CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
win32-msvc2012:CONFIG(release, debug|release): QMAKE_CXXFLAGS += /O2 /GA

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
