#include "test_calculator_controller_integration.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtTest>

void TestCalculatorControllerIntegration::mainWindowWiresAddButtonToController()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QVERIFY(window.buttonAdd() != nullptr);
    QVERIFY(window.firstOperandInput() != nullptr);
    QVERIFY(window.secondOperandInput() != nullptr);
    QVERIFY(window.displayEdit() != nullptr);
    QVERIFY(window.statusLabel() != nullptr);
}

void TestCalculatorControllerIntegration::mainWindowAdditionFlowProducesExpectedOutput()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("10"));
    window.secondOperandInput()->setText(QStringLiteral("15"));

    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("25"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestCalculatorControllerIntegration::mainWindowInvalidInputShowsError()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("not-a-number"));
    window.secondOperandInput()->setText(QStringLiteral("4"));

    window.buttonAdd()->click();

    QVERIFY(!window.statusLabel()->text().isEmpty());
}
