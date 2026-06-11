QT       += core gui widgets
QT       -= multimedia network sql testlib concurrent serialport

CONFIG   += c++17
CONFIG   += release
CONFIG   += optimize_size
TARGET   = Calculator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += DEFER_NON_ESSENTIAL_RESOURCES

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/mainwindow.cpp \
    $$PWD/src/arithmeticoperations.cpp \
    $$PWD/src/calculatorcontroller.cpp

HEADERS += \
    $$PWD/include/mainwindow.h \
    $$PWD/include/arithmeticoperations.h \
    $$PWD/include/calculatorcontroller.h

FORMS += \
    $$PWD/forms/mainwindow.ui

RESOURCES += \
    $$PWD/resources/resources.qrc

QMAKE_CXXFLAGS += -Os -fdata-sections -ffunction-sections
QMAKE_LFLAGS   += -Wl,--gc-sections -Wl,-s

OBJECTS_DIR     = build/obj
MOC_DIR         = build/moc
RCC_DIR         = build/rcc
UI_DIR          = build/ui
DESTDIR         = bin
