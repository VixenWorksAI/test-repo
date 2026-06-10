#include "test_multiplication_ui_e2e.h"

#include "mainwindow.h"

#include <QApplication>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <QtTest/QTest>

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
