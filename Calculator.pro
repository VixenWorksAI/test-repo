QT       += core gui widgets

CONFIG   += c++17
TARGET   = Calculator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/mainwindow.cpp

HEADERS += \
    $$PWD/include/mainwindow.h

FORMS += \
    $$PWD/forms/mainwindow.ui

RESOURCES += \
    $$PWD/resources/resources.qrc
