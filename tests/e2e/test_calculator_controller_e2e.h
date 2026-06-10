#ifndef TEST_CALCULATOR_CONTROLLER_E2E_H
#define TEST_CALCULATOR_CONTROLLER_E2E_H

#include <QObject>

class TestCalculatorControllerE2E : public QObject
{
    Q_OBJECT

private slots:
    void userInitiatedAdditionShowsCorrectResult();
    void userInitiatedAdditionWithInvalidInputReportsError();
};

#endif
