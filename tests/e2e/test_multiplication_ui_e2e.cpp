#include "test_multiplication_ui_e2e.h"

#include "arithmeticoperations.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDoubleValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <QtTest/QTest>
#include <cfloat>
#include <limits>

TestMultiplicationUiE2E::TestMultiplicationUiE2E(QObject *parent)
    : QObject(parent)
{
}

void TestMultiplicationUiE2E::uiComponentsAreResponsiveToUserActions()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    QVERIFY(first != nullptr);
    QVERIFY(second != nullptr);
    QVERIFY(multiply != nullptr);

    first->setText(QStringLiteral("6"));
    second->setText(QStringLiteral("9"));
    QVERIFY(first->text() == QStringLiteral("6"));
    QVERIFY(second->text() == QStringLiteral("9"));

    QSignalSpy spy(multiply, &QPushButton::clicked);
    multiply->click();
    QCOMPARE(spy.count(), 1);
    QVERIFY(multiply->isChecked());
}

void TestMultiplicationUiE2E::multiplyButtonVisualStateChangesWhenActive()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QPushButton *button = window.buttonMultiply();
    QVERIFY(button != nullptr);

    QVERIFY(!button->isChecked());

    button->click();
    QVERIFY(button->isChecked());
    QCOMPARE(button->isCheckable(), true);

    button->click();
    QVERIFY(!button->isChecked());
}

void TestMultiplicationUiE2E::multiplyButtonRespondsToRepeatedClicks()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QPushButton *button = window.buttonMultiply();
    QSignalSpy spy(button, &QPushButton::toggled);

    for (int i = 0; i < 4; ++i) {
        button->click();
    }

    QCOMPARE(spy.count(), 4);
    QVERIFY(!button->isChecked());
}

void TestMultiplicationUiE2E::allOperatorButtonsAreResponsive()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QPushButton *subtract = window.buttonSubtract();
    QPushButton *multiply = window.buttonMultiply();

    QVERIFY(subtract != nullptr);
    QVERIFY(multiply != nullptr);

    multiply->click();
    QVERIFY(multiply->isChecked());
    QVERIFY(!subtract->isChecked());

    multiply->click();
    QVERIFY(!multiply->isChecked());

    subtract->click();
    QVERIFY(subtract->isChecked());
}

void TestMultiplicationUiE2E::inputFieldsAcceptValidNumbers()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    first->setText(QStringLiteral("42"));
    second->setText(QStringLiteral("3.14"));
    QCOMPARE(first->text(), QStringLiteral("42"));
    QCOMPARE(second->text(), QStringLiteral("3.14"));
}

void TestMultiplicationUiE2E::inputFieldsRejectInvalidCharacters()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    const QValidator *firstValidator = first->validator();
    const QValidator *secondValidator = second->validator();
    QVERIFY(firstValidator != nullptr);
    QVERIFY(secondValidator != nullptr);

    QString alphabetic = QStringLiteral("hello");
    int pos = 0;
    QCOMPARE(firstValidator->validate(alphabetic, pos), QValidator::Invalid);
    QCOMPARE(secondValidator->validate(alphabetic, pos), QValidator::Invalid);
}

void TestMultiplicationUiE2E::e2eMultiplicationProducesCorrectProduct()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QStringLiteral("8"));
    second->setText(QStringLiteral("5"));

    QSignalSpy clickedSpy(multiply, &QPushButton::clicked);
    multiply->click();
    QCOMPARE(clickedSpy.count(), 1);

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), 40.0);
}

void TestMultiplicationUiE2E::e2eMultiplicationWithNegativeNumbersProducesCorrectProduct()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QStringLiteral("-7"));
    second->setText(QStringLiteral("6"));

    multiply->click();

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), -42.0);
}

void TestMultiplicationUiE2E::e2eMultiplicationWithLargeNumbersSaturates()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QString::number(DBL_MAX));
    second->setText(QStringLiteral("2"));

    multiply->click();

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);

    const double result = arithmetic::multiplyNumbers(a, b);
    QCOMPARE(result, std::numeric_limits<double>::max());
    QVERIFY(!std::isinf(result));
}

void TestMultiplicationUiE2E::e2eMultiplicationWithZeroProducesZero()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QStringLiteral("0"));
    second->setText(QStringLiteral("1234.5678"));

    multiply->click();

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), 0.0);
}

void TestMultiplicationUiE2E::e2eTypingThenClickingMultiplyUpdatesDisplay()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QStringLiteral("9"));
    second->setText(QStringLiteral("4"));

    multiply->click();

    const double expected = arithmetic::multiplyNumbers(9.0, 4.0);
    QCOMPARE(window.displayEdit()->text().toDouble(), expected);
}

void TestMultiplicationUiE2E::e2eInvalidInputSurfacesErrorInStatusLabel()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QPushButton *multiply = window.buttonMultiply();

    first->setText(QStringLiteral("not-a-number"));
    second->setText(QStringLiteral("2"));

    multiply->click();

    QVERIFY(!window.statusLabel()->text().isEmpty());
}
