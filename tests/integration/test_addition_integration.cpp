#include "test_addition_integration.h"
#include "calculatorcontroller.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

namespace
{
struct Widgets
{
    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
};
}

void TestAdditionIntegration::resultDisplayShowsSumForPositiveIntegers()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("7"));
    widgets.second.setText(QStringLiteral("8"));
    addButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("15"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestAdditionIntegration::resultDisplayShowsSumForNegativeIntegers()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("-4"));
    widgets.second.setText(QStringLiteral("-6"));
    addButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("-10"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestAdditionIntegration::resultDisplayShowsSumForMixedSigns()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("12.5"));
    widgets.second.setText(QStringLiteral("-3.25"));
    addButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("9.25"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestAdditionIntegration::resultDisplayShowsSumWithZero()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("0"));
    widgets.second.setText(QStringLiteral("42"));
    addButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("42"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestAdditionIntegration::invalidInputSetsErrorAndClearsResult()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("1"));
    widgets.second.setText(QStringLiteral("2"));
    addButton.click();
    QCOMPARE(widgets.result.text(), QStringLiteral("3"));

    widgets.first.setText(QStringLiteral("abc"));
    widgets.second.setText(QStringLiteral("2"));
    addButton.click();

    QVERIFY(!widgets.status.text().isEmpty());
    QCOMPARE(widgets.result.text(), QString());
}

void TestAdditionIntegration::statusLabelClearsAfterSuccessfulAdd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton addButton;
    controller.bind(&addButton);

    widgets.first.setText(QStringLiteral("xyz"));
    widgets.second.setText(QStringLiteral("1"));
    addButton.click();
    QVERIFY(!widgets.status.text().isEmpty());

    widgets.first.setText(QStringLiteral("2"));
    widgets.second.setText(QStringLiteral("3"));
    addButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("5"));
    QVERIFY(widgets.status.text().isEmpty());
}
