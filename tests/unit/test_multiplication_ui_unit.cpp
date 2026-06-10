#include "test_multiplication_ui_unit.h"

#include "arithmeticoperations.h"
#include "mainwindow.h"

#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <cfloat>
#include <cmath>
#include <limits>

using arithmetic::multiplyNumbers;

TestMultiplicationUiUnit::TestMultiplicationUiUnit(QObject *parent)
    : QObject(parent)
{
}

void TestMultiplicationUiUnit::multiplyButtonExists()
{
    MainWindow window;
    QVERIFY(window.buttonMultiply() != nullptr);
}

void TestMultiplicationUiUnit::multiplyButtonDisplaysStarSymbol()
{
    MainWindow window;
    QCOMPARE(window.buttonMultiply()->text(), QStringLiteral("*"));
}

void TestMultiplicationUiUnit::multiplyButtonIsCheckable()
{
    MainWindow window;
    QVERIFY(window.buttonMultiply()->isCheckable());
}

void TestMultiplicationUiUnit::multiplyButtonStartsInactive()
{
    MainWindow window;
    QVERIFY(!window.buttonMultiply()->isChecked());
}

void TestMultiplicationUiUnit::firstOperandInputExists()
{
    MainWindow window;
    QVERIFY(window.firstOperandInput() != nullptr);
}

void TestMultiplicationUiUnit::secondOperandInputExists()
{
    MainWindow window;
    QVERIFY(window.secondOperandInput() != nullptr);
}

void TestMultiplicationUiUnit::firstOperandInputHasNumericValidator()
{
    MainWindow window;
    QVERIFY(qobject_cast<const QDoubleValidator *>(window.firstOperandInput()->validator()) != nullptr);
}

void TestMultiplicationUiUnit::secondOperandInputHasNumericValidator()
{
    MainWindow window;
    QVERIFY(qobject_cast<const QDoubleValidator *>(window.secondOperandInput()->validator()) != nullptr);
}

void TestMultiplicationUiUnit::firstOperandInputRejectsAlpha()
{
    MainWindow window;
    QLineEdit *input = window.firstOperandInput();
    QVERIFY(input->validator() != nullptr);
    QString rejected = QStringLiteral("abc");
    int pos = 0;
    const QValidator::State state = input->validator()->validate(rejected, pos);
    QVERIFY(state == QValidator::Invalid);
}

void TestMultiplicationUiUnit::secondOperandInputRejectsAlpha()
{
    MainWindow window;
    QLineEdit *input = window.secondOperandInput();
    QVERIFY(input->validator() != nullptr);
    QString rejected = QStringLiteral("xyz");
    int pos = 0;
    const QValidator::State state = input->validator()->validate(rejected, pos);
    QVERIFY(state == QValidator::Invalid);
}

void TestMultiplicationUiUnit::multiplyPositiveByPositive()
{
    QCOMPARE(multiplyNumbers(3.0, 4.0), 12.0);
    QCOMPARE(multiplyNumbers(2.5, 4.0), 10.0);
    QCOMPARE(multiplyNumbers(0.1, 0.2), 0.02);
}

void TestMultiplicationUiUnit::multiplyPositiveByNegative()
{
    QCOMPARE(multiplyNumbers(5.0, -2.0), -10.0);
    QCOMPARE(multiplyNumbers(-5.0, 2.0), -10.0);
    QCOMPARE(multiplyNumbers(7.5, -3.0), -22.5);
}

void TestMultiplicationUiUnit::multiplyNegativeByNegative()
{
    QCOMPARE(multiplyNumbers(-3.0, -4.0), 12.0);
    QCOMPARE(multiplyNumbers(-2.5, -4.0), 10.0);
    QCOMPARE(multiplyNumbers(-1.5, -2.0), 3.0);
}

void TestMultiplicationUiUnit::multiplyByZeroReturnsZero()
{
    QCOMPARE(multiplyNumbers(5.0, 0.0), 0.0);
    QCOMPARE(multiplyNumbers(-5.0, 0.0), 0.0);
    QCOMPARE(multiplyNumbers(0.0, 0.0), 0.0);
}

void TestMultiplicationUiUnit::multiplyZeroByNumberReturnsZero()
{
    QCOMPARE(multiplyNumbers(0.0, 5.0), 0.0);
    QCOMPARE(multiplyNumbers(0.0, -5.0), 0.0);
    QCOMPARE(multiplyNumbers(0.0, 123456789.0), 0.0);
}

void TestMultiplicationUiUnit::multiplyLargeNumbersSaturatesToMax()
{
    const double result = multiplyNumbers(DBL_MAX, 2.0);
    QCOMPARE(result, std::numeric_limits<double>::max());
    QVERIFY(!std::isinf(result));
}

void TestMultiplicationUiUnit::multiplyLargePositiveByLargeNegativeSaturatesToMin()
{
    const double result = multiplyNumbers(DBL_MAX, -2.0);
    QCOMPARE(result, std::numeric_limits<double>::lowest());
    QVERIFY(!std::isinf(result));
}

void TestMultiplicationUiUnit::multiplyFractionalNumbersMaintainsPrecision()
{
    QCOMPARE(multiplyNumbers(0.5, 0.5), 0.25);
    QCOMPARE(multiplyNumbers(1.25, 8.0), 10.0);
    QVERIFY(qFuzzyCompare(multiplyNumbers(1.0 / 3.0, 3.0), 1.0));
}
