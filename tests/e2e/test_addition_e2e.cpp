#include "test_addition_e2e.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtTest>

void TestAdditionE2E::userAddsTwoPositiveIntegersEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("125"));
    window.secondOperandInput()->setText(QStringLiteral("275"));
    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("400"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestAdditionE2E::userAddsNegativeNumbersEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("-15"));
    window.secondOperandInput()->setText(QStringLiteral("-25"));
    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("-40"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestAdditionE2E::userAddsMixedSignsEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("10.5"));
    window.secondOperandInput()->setText(QStringLiteral("-4.25"));
    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("6.25"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestAdditionE2E::userAddsZeroEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("0"));
    window.secondOperandInput()->setText(QStringLiteral("99"));
    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("99"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestAdditionE2E::userEntersInvalidTextAndReceivesError()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("abc"));
    window.secondOperandInput()->setText(QStringLiteral("5"));
    window.buttonAdd()->click();

    QVERIFY(!window.statusLabel()->text().isEmpty());
    QCOMPARE(window.displayEdit()->text(), QString());
}

void TestAdditionE2E::userRecoversFromInvalidEntryAndComputesAgain()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("foo"));
    window.secondOperandInput()->setText(QStringLiteral("1"));
    window.buttonAdd()->click();
    QVERIFY(!window.statusLabel()->text().isEmpty());

    window.firstOperandInput()->setText(QStringLiteral("7"));
    window.secondOperandInput()->setText(QStringLiteral("8"));
    window.buttonAdd()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("15"));
    QCOMPARE(window.statusLabel()->text(), QString());
}
