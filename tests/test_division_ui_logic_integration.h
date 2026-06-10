#ifndef TEST_DIVISION_UI_LOGIC_INTEGRATION_H
#define TEST_DIVISION_UI_LOGIC_INTEGRATION_H

#include <QObject>
#include <QtTest/QtTest>

class DivisionUiLogicIntegrationTest : public QObject
{
    Q_OBJECT

private slots:
    void validDivisionFlowsThroughController();
    void validDivisionHandlesDecimalResult();
    void divisionByZeroShowsErrorInResultDisplay();
    void invalidFirstOperandShowsError();
    void signalSlotChainCompletesEndToEnd();
};

#endif
