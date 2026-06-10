#include "test_calculator_controller_e2e.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtTest>

void TestCalculatorControllerE2E::userInitiatedAdditionShowsCorrectResult()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("42"));
    window.secondOperandInput()->setText(QStringLiteral("58"));

    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("100"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestCalculatorControllerE2E::userInitiatedAdditionWithInvalidInputReportsError()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral(""));
    window.secondOperandInput()->setText(QStringLiteral("5"));

    window.buttonAdd()->click();

    QVERIFY(!window.statusLabel()->text().isEmpty());
    QCOMPARE(window.displayEdit()->text(), QString());
}
