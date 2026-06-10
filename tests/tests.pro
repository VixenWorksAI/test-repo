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
    $$PWD/../src/arithmeticoperations.cpp \
    $$PWD/../src/calculatorcontroller.cpp \
    $$PWD/unit/test_placeholder_responsiveness_unit.cpp \
    $$PWD/unit/test_addition_unit.cpp \
    $$PWD/unit/test_calculator_controller_unit.cpp \
    $$PWD/unit/test_subtraction_ui_unit.cpp \
    $$PWD/integration/test_placeholder_responsiveness_integration.cpp \
    $$PWD/integration/test_addition_integration.cpp \
    $$PWD/integration/test_calculator_controller_integration.cpp \
    $$PWD/integration/test_subtraction_ui_integration.cpp \
    $$PWD/integration/test_subtraction_integration.cpp \
    $$PWD/e2e/test_placeholder_responsiveness_e2e.cpp \
    $$PWD/e2e/test_addition_e2e.cpp \
    $$PWD/e2e/test_calculator_controller_e2e.cpp \
    $$PWD/e2e/test_subtraction_ui_e2e.cpp

HEADERS += \
    $$PWD/../include/mainwindow.h \
    $$PWD/../include/arithmeticoperations.h \
    $$PWD/../include/calculatorcontroller.h \
    $$PWD/unit/test_placeholder_responsiveness_unit.h \
    $$PWD/unit/test_addition_unit.h \
    $$PWD/unit/test_calculator_controller_unit.h \
    $$PWD/unit/test_subtraction_ui_unit.h \
    $$PWD/integration/test_placeholder_responsiveness_integration.h \
    $$PWD/integration/test_addition_integration.h \
    $$PWD/integration/test_calculator_controller_integration.h \
    $$PWD/integration/test_subtraction_ui_integration.h \
    $$PWD/integration/test_subtraction_integration.h \
    $$PWD/e2e/test_placeholder_responsiveness_e2e.h \
    $$PWD/e2e/test_addition_e2e.h \
    $$PWD/e2e/test_calculator_controller_e2e.h \
    $$PWD/e2e/test_subtraction_ui_e2e.h

FORMS += \
    $$PWD/../forms/mainwindow.ui

UI_HEADERS_DIR = $$PWD/.ui
UI_SOURCES_DIR = $$PWD/.ui
