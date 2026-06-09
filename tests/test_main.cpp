#include <QApplication>
#include <QtTest>
#include <QTest>
#include <cstdlib>

#include "mainwindow.h"

#include "test_placeholder_responsiveness_unit.h"
#include "test_placeholder_responsiveness_integration.h"
#include "test_placeholder_responsiveness_e2e.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;
    {
        TestPlaceholderResponsivenessUnit unit;
        status |= QTest::qExec(&unit, argc, argv);
    }
    {
        TestPlaceholderResponsivenessIntegration integration;
        status |= QTest::qExec(&integration, argc, argv);
    }
    {
        TestPlaceholderResponsivenessE2E e2e;
        status |= QTest::qExec(&e2e, argc, argv);
    }
    return status;
}
