#include "test_calculator_controller_unit.h"
#include "calculatorcontroller.h"

#include <QLabel>
#include <QLineEdit>
#include <QtTest>

void TestCalculatorControllerUnit::validOperandsDisplaySum()
{
    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("3.5"));
    second.setText(QStringLiteral("2.25"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onAddButtonClicked();

    QCOMPARE(result.text(), QStringLiteral("5.75"));
    QCOMPARE(status.text(), QString());
}

void TestCalculatorControllerUnit::invalidFirstOperandShowsError()
{
    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("abc"));
    second.setText(QStringLiteral("2"));
    result.setText(QStringLiteral("legacy"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onAddButtonClicked();

    QCOMPARE(result.text(), QString());
    QVERIFY(!status.text().isEmpty());
}

void TestCalculatorControllerUnit::invalidSecondOperandShowsError()
{
    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("2"));
    second.setText(QStringLiteral("xyz"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onAddButtonClicked();

    QCOMPARE(result.text(), QString());
    QVERIFY(!status.text().isEmpty());
}

void TestCalculatorControllerUnit::emptyFirstOperandShowsError()
{
    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    second.setText(QStringLiteral("1"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onAddButtonClicked();

    QCOMPARE(result.text(), QString());
    QVERIFY(!status.text().isEmpty());
}
