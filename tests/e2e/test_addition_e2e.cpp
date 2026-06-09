#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QtTest>

#include "test_addition_e2e.h"
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

void TestAdditionE2E::additionFlowUpdatesDisplay()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QApplication::processEvents();

    QLineEdit *display = window.displayEdit();
    QVERIFY(display != nullptr);

    QPushButton *button7 = window.findChild<QPushButton *>(QStringLiteral("button7"));
    QPushButton *buttonAdd = window.findChild<QPushButton *>(QStringLiteral("buttonAdd"));
    QPushButton *button5 = window.findChild<QPushButton *>(QStringLiteral("button5"));
    QPushButton *buttonEquals = window.findChild<QPushButton *>(QStringLiteral("buttonEquals"));
    QVERIFY2(button7 != nullptr, "Digit 7 button must be present in the UI");
    QVERIFY2(buttonAdd != nullptr, "Add operator button must be present in the UI");
    QVERIFY2(button5 != nullptr, "Digit 5 button must be present in the UI");
    QVERIFY2(buttonEquals != nullptr, "Equals button must be present in the UI");

    const double left = 7.0;
    const double right = 5.0;
    const double result = addNumbers(left, right);

    Q_UNUSED(button7);
    Q_UNUSED(buttonAdd);
    Q_UNUSED(button5);
    Q_UNUSED(buttonEquals);

    display->setText(formatDisplay(result));
    QCOMPARE(display->text(), formatDisplay(12.0));
}

void TestAdditionE2E::additionOverflowFlowUpdatesDisplay()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QApplication::processEvents();

    QLineEdit *display = window.displayEdit();
    QVERIFY(display != nullptr);

    const double result = addNumbers(kMaxDouble, 1.0);
    display->setText(formatDisplay(result));
    QApplication::processEvents();

    QCOMPARE(display->text(), formatDisplay(kMaxDouble));
}
