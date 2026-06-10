#include "test_subtraction_e2e.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtTest>

void TestSubtractionE2E::userSubtractsTwoPositiveIntegersEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("125"));
    window.secondOperandInput()->setText(QStringLiteral("25"));
    window.buttonSubtract()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("100"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestSubtractionE2E::userSubtractsResultingInNegativeEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("3"));
    window.secondOperandInput()->setText(QStringLiteral("10"));
    window.buttonSubtract()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("-7"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestSubtractionE2E::userSubtractsWithZeroEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("42"));
    window.secondOperandInput()->setText(QStringLiteral("0"));
    window.buttonSubtract()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("42"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestSubtractionE2E::userSubtractsFractionalValuesEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("5.5"));
    window.secondOperandInput()->setText(QStringLiteral("2.25"));
    window.buttonSubtract()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("3.25"));
    QCOMPARE(window.statusLabel()->text(), QString());
}

void TestSubtractionE2E::userEntersInvalidSubtractionTextAndReceivesError()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("abc"));
    window.secondOperandInput()->setText(QStringLiteral("5"));
    window.buttonSubtract()->click();

    QVERIFY(!window.statusLabel()->text().isEmpty());
    QCOMPARE(window.displayEdit()->text(), QString());
}

void TestSubtractionE2E::userRecoversFromInvalidSubtractionEntryAndComputesAgain()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("foo"));
    window.secondOperandInput()->setText(QStringLiteral("1"));
    window.buttonSubtract()->click();
    QVERIFY(!window.statusLabel()->text().isEmpty());

    window.firstOperandInput()->setText(QStringLiteral("9"));
    window.secondOperandInput()->setText(QStringLiteral("4"));
    window.buttonSubtract()->click();

    QCOMPARE(window.displayEdit()->text(), QStringLiteral("5"));
    QCOMPARE(window.statusLabel()->text(), QString());
}
