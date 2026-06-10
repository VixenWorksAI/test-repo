#ifndef TEST_CALCULATOR_CONTROLLER_INTEGRATION_H
#define TEST_CALCULATOR_CONTROLLER_INTEGRATION_H

#include <QObject>

class TestCalculatorControllerIntegration : public QObject
{
    Q_OBJECT

private slots:
    void mainWindowWiresAddButtonToController();
    void mainWindowAdditionFlowProducesExpectedOutput();
    void mainWindowInvalidInputShowsError();
};

#endif
