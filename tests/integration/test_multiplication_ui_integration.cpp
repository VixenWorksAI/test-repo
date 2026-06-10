#include "test_multiplication_ui_integration.h"

#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <QtTest/QTest>

TestMultiplicationUiIntegration::TestMultiplicationUiIntegration(QObject *parent)
    : QObject(parent)
{
}

void TestMultiplicationUiIntegration::multiplyButtonClicksToggleActiveState()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonMultiply();
    QVERIFY(button != nullptr);

    QSignalSpy spy(button, &QPushButton::toggled);
    button->click();
    QVERIFY(button->isChecked());
    QCOMPARE(spy.count(), 1);

    button->click();
    QVERIFY(!button->isChecked());
    QCOMPARE(spy.count(), 2);
}

void TestMultiplicationUiIntegration::multiplyButtonClickChangesButtonToChecked()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonMultiply();
    QVERIFY(!button->isChecked());

    button->click();
    QCOMPARE(button->isChecked(), true);

    button->click();
    QCOMPARE(button->isChecked(), false);
}

void TestMultiplicationUiIntegration::multiplyButtonIsClickableWithKeyboard()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QPushButton *button = window.buttonMultiply();
    QVERIFY(button != nullptr);
    QVERIFY(button->isCheckable());

    QVERIFY(button->isEnabled());
    QVERIFY(button->isVisibleTo(&window));

    button->click();
    QVERIFY(button->isChecked());
}

void TestMultiplicationUiIntegration::multiplyButtonReceivesFocusAndClick()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonMultiply();
    QVERIFY(button != nullptr);

    button->setDefault(true);
    QVERIFY(button->isDefault());

    button->click();
    QVERIFY(button->isChecked());
}

void TestMultiplicationUiIntegration::firstAndSecondInputsAreIndependent()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QVERIFY(first != nullptr);
    QVERIFY(second != nullptr);
    QVERIFY(first != second);

    first->setText(QStringLiteral("7"));
    second->setText(QStringLiteral("11"));
    QCOMPARE(first->text(), QStringLiteral("7"));
    QCOMPARE(second->text(), QStringLiteral("11"));
}

void TestMultiplicationUiIntegration::multiplyButtonLabelIsMultiplicationGlyph()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonMultiply();
    QCOMPARE(button->text(), QStringLiteral("*"));
    QCOMPARE(button->text().size(), 1);
    QCOMPARE(button->text().at(0), QChar('*'));
}

void TestMultiplicationUiIntegration::multiplyButtonRespondsToMousePressAndRelease()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QPushButton *button = window.buttonMultiply();
    QVERIFY(!button->isChecked());

    const QPoint center = button->rect().center();
    QTest::mouseClick(button, Qt::LeftButton, Qt::NoModifier, center);
    QVERIFY(button->isChecked());
}
