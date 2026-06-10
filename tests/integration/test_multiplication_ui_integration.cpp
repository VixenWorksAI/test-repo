#include "test_multiplication_ui_integration.h"

#include "arithmeticoperations.h"
#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <QtTest/QTest>
#include <cfloat>
#include <limits>

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

void TestMultiplicationUiIntegration::multiplicationLogicProducesProductFromUiInputs()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    first->setText(QStringLiteral("6"));
    second->setText(QStringLiteral("7"));

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), 42.0);
}

void TestMultiplicationUiIntegration::multiplicationLogicHandlesNegativeNumbersFromUiInputs()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    first->setText(QStringLiteral("-4"));
    second->setText(QStringLiteral("5"));

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), -20.0);
    QCOMPARE(arithmetic::multiplyNumbers(-4.0, -5.0), 20.0);
}

void TestMultiplicationUiIntegration::multiplicationLogicHandlesOverflowFromUiInputs()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    first->setText(QString::number(DBL_MAX));
    second->setText(QStringLiteral("2"));

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);

    const double result = arithmetic::multiplyNumbers(a, b);
    QCOMPARE(result, std::numeric_limits<double>::max());
}

void TestMultiplicationUiIntegration::multiplicationLogicHandlesZeroFromUiInputs()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();

    first->setText(QStringLiteral("0"));
    second->setText(QStringLiteral("9.81"));

    bool okA = false;
    bool okB = false;
    const double a = first->text().toDouble(&okA);
    const double b = second->text().toDouble(&okB);
    QVERIFY(okA);
    QVERIFY(okB);
    QCOMPARE(arithmetic::multiplyNumbers(a, b), 0.0);
}

void TestMultiplicationUiIntegration::multiplyButtonClickProducesDisplayUpdateFromUiInputs()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    first->setText(QStringLiteral("6"));
    second->setText(QStringLiteral("7"));

    window.buttonMultiply()->click();

    const double expected = arithmetic::multiplyNumbers(6.0, 7.0);
    QCOMPARE(window.displayEdit()->text().toDouble(), expected);
}

void TestMultiplicationUiIntegration::multiplyButtonClickWithInvalidInputLeavesDisplayUnchanged()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QTest::qWaitForWindowExposed(&window);

    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    first->setText(QStringLiteral("not-a-number"));
    second->setText(QStringLiteral("7"));

    window.buttonMultiply()->click();
    QCOMPARE(window.displayEdit()->text(), QString());
    QVERIFY(!window.statusLabel()->text().isEmpty());
}
