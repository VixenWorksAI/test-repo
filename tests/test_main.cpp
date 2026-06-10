#include <QApplication>
#include <QtTest>
#include <QTest>
#include <cstdlib>

#include "mainwindow.h"

#include "test_placeholder_responsiveness_unit.h"
#include "test_placeholder_responsiveness_integration.h"
#include "test_placeholder_responsiveness_e2e.h"
#include "test_addition_unit.h"
#include "test_addition_integration.h"
#include "test_addition_e2e.h"
#include "test_calculator_controller_unit.h"
#include "test_calculator_controller_integration.h"
#include "test_calculator_controller_e2e.h"
#include "test_subtraction_ui_unit.h"
#include "test_subtraction_ui_integration.h"
#include "test_subtraction_ui_e2e.h"
#include "test_subtraction_integration.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;
    {
        TestPlaceholderResponsivenessUnit unit;
        status |= QTest::qExec(&unit, argc, argv);
    }
    {
        TestAdditionUnit unit;
        status |= QTest::qExec(&unit, argc, argv);
    }
    {
        TestSubtractionUiUnit unit;
        status |= QTest::qExec(&unit, argc, argv);
    }
    {
        TestCalculatorControllerUnit unit;
        status |= QTest::qExec(&unit, argc, argv);
    }
    {
        TestPlaceholderResponsivenessIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestAdditionIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestSubtractionUiIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestSubtractionIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestCalculatorControllerIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestPlaceholderResponsivenessE2E e2e;
        status |= QTest::qExec(&e2e, argc, argv);
    }
    {
        TestAdditionE2E e2e;
        status |= QTest::qExec(&e2e, argc, argv);
    }
    {
        TestSubtractionUiE2e e2e;
        status |= QTest::qExec(&e2e, argc, argv);
    }
    {
        TestCalculatorControllerE2E e2e;
        status |= QTest::qExec(&e2e, argc, argv);
    }
    return status;
}
