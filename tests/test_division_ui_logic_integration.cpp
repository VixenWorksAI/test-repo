#include "test_division_ui_logic_integration.h"

#include "calculatorcontroller.h"
#include "arithmeticoperations.h"

#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>

void DivisionUiLogicIntegrationTest::validDivisionFlowsThroughController()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("20"));
    second.setText(QStringLiteral("4"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onDivideButtonClicked();

    QCOMPARE(result.text(), QStringLiteral("5"));
    QCOMPARE(status.text(), QString());
}

void DivisionUiLogicIntegrationTest::validDivisionHandlesDecimalResult()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("7"));
    second.setText(QStringLiteral("2"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onDivideButtonClicked();

    QCOMPARE(result.text(), QStringLiteral("3.5"));
    QCOMPARE(status.text(), QString());
}

void DivisionUiLogicIntegrationTest::divisionByZeroShowsErrorInResultDisplay()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("9"));
    second.setText(QStringLiteral("0"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onDivideButtonClicked();

    QVERIFY2(status.text().contains(QStringLiteral("Division by zero"),
                                    Qt::CaseInsensitive),
             "Status label must report division by zero");
}

void DivisionUiLogicIntegrationTest::invalidFirstOperandShowsError()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    first.setText(QStringLiteral("not-a-number"));
    second.setText(QStringLiteral("2"));

    CalculatorController controller(&first, &second, &result, &status);
    controller.onDivideButtonClicked();

    QVERIFY2(!status.text().isEmpty(),
             "Status label must report an error for invalid input");
}

void DivisionUiLogicIntegrationTest::signalSlotChainCompletesEndToEnd()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    QLineEdit first;
    QLineEdit second;
    QLineEdit result;
    QLabel status;
    QPushButton divideButton;

    CalculatorController controller(&first, &second, &result, &status);
    controller.bindDivide(&divideButton);

    first.setText(QStringLiteral("100"));
    second.setText(QStringLiteral("25"));
    divideButton.click();
    divideButton.click();
    divideButton.click();
    QCOMPARE(result.text(), QStringLiteral("4"));
    QCOMPARE(status.text(), QString());

    first.setText(QStringLiteral("10"));
    second.setText(QStringLiteral("0"));
    divideButton.click();
    QVERIFY2(status.text().contains(QStringLiteral("Division by zero"),
                                    Qt::CaseInsensitive),
             "End-to-end chain must surface divide-by-zero through the "
             "controller into the result-display status label");
}
