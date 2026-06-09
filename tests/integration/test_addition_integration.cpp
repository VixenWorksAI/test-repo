#include <QApplication>
#include <QLineEdit>
#include <QtTest>

#include "test_addition_integration.h"
#include "mainwindow.h"
#include "arithmeticoperations.h"

using arithmetic::addNumbers;
using arithmetic::kMaxDouble;

namespace {
QString formatDisplay(double value)
{
    if (value == kMaxDouble) {
        return QString::number(kMaxDouble, 'g', 17);
    }
    return QString::number(value, 'g', 17);
}
}

void TestAdditionIntegration::additionResultIsDisplayedInMainWindow()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *display = window.displayEdit();
    QVERIFY(display != nullptr);

    const double result = addNumbers(7.0, 5.0);
    display->setText(formatDisplay(result));

    QCOMPARE(display->text(), formatDisplay(12.0));
}

void TestAdditionIntegration::additionWithNegativeOperandsIsDisplayedInMainWindow()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *display = window.displayEdit();
    QVERIFY(display != nullptr);

    const double result = addNumbers(-4.0, -6.0);
    display->setText(formatDisplay(result));

    QCOMPARE(display->text(), formatDisplay(-10.0));
}

void TestAdditionIntegration::additionOverflowClampIsDisplayedInMainWindow()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *display = window.displayEdit();
    QVERIFY(display != nullptr);

    const double result = addNumbers(kMaxDouble, 1.0e308);
    display->setText(formatDisplay(result));

    QCOMPARE(display->text(), formatDisplay(kMaxDouble));
}
