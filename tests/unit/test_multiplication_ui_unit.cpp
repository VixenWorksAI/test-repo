#include "test_multiplication_ui_unit.h"

#include "mainwindow.h"

#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>

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
