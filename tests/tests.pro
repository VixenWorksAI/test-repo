QT       += core gui widgets testlib
CONFIG   += console c++17
CONFIG   -= app_bundle
TEMPLATE = app
TARGET   = test_placeholder_responsiveness
INCLUDEPATH += $$PWD/../include \
               $$PWD/unit \
               $$PWD/integration \
               $$PWD/e2e

SOURCES += \
    $$PWD/test_main.cpp \
    $$PWD/../src/mainwindow.cpp \
    $$PWD/unit/test_placeholder_responsiveness_unit.cpp \
    $$PWD/integration/test_placeholder_responsiveness_integration.cpp \
    $$PWD/e2e/test_placeholder_responsiveness_e2e.cpp

HEADERS += \
    $$PWD/../include/mainwindow.h \
    $$PWD/unit/test_placeholder_responsiveness_unit.h \
    $$PWD/integration/test_placeholder_responsiveness_integration.h \
    $$PWD/e2e/test_placeholder_responsiveness_e2e.h

FORMS += \
    $$PWD/../forms/mainwindow.ui

UI_HEADERS_DIR = $$PWD/.ui
UI_SOURCES_DIR = $$PWD/.ui
