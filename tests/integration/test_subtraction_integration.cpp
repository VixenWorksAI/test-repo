#include "test_subtraction_integration.h"
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

void TestSubtractionIntegration::resultDisplayShowsDifferenceForPositiveIntegers()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("15"));
    widgets.second.setText(QStringLiteral("7"));
    subtractButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("8"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestSubtractionIntegration::resultDisplayShowsDifferenceForNegativeIntegers()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("-4"));
    widgets.second.setText(QStringLiteral("-6"));
    subtractButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("2"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestSubtractionIntegration::resultDisplayShowsDifferenceForMixedSigns()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("3.5"));
    widgets.second.setText(QStringLiteral("-1.25"));
    subtractButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("4.75"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestSubtractionIntegration::resultDisplayShowsDifferenceWithZero()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("0"));
    widgets.second.setText(QStringLiteral("42"));
    subtractButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("-42"));
    QVERIFY(widgets.status.text().isEmpty());
}

void TestSubtractionIntegration::invalidInputSetsErrorAndClearsResult()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("10"));
    widgets.second.setText(QStringLiteral("3"));
    subtractButton.click();
    QCOMPARE(widgets.result.text(), QStringLiteral("7"));

    widgets.first.setText(QStringLiteral("abc"));
    widgets.second.setText(QStringLiteral("2"));
    subtractButton.click();

    QVERIFY(!widgets.status.text().isEmpty());
    QCOMPARE(widgets.result.text(), QString());
}

void TestSubtractionIntegration::statusLabelClearsAfterSuccessfulSubtract()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    Widgets widgets;
    CalculatorController controller(&widgets.first,
                                    &widgets.second,
                                    &widgets.result,
                                    &widgets.status);
    QPushButton subtractButton;
    controller.bindSubtract(&subtractButton);

    widgets.first.setText(QStringLiteral("xyz"));
    widgets.second.setText(QStringLiteral("1"));
    subtractButton.click();
    QVERIFY(!widgets.status.text().isEmpty());

    widgets.first.setText(QStringLiteral("9"));
    widgets.second.setText(QStringLiteral("4"));
    subtractButton.click();

    QCOMPARE(widgets.result.text(), QStringLiteral("5"));
    QVERIFY(widgets.status.text().isEmpty());
}
