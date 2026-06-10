#ifndef TEST_CALCULATOR_CONTROLLER_UNIT_H
#define TEST_CALCULATOR_CONTROLLER_UNIT_H

#include <QObject>

class TestCalculatorControllerUnit : public QObject
{
    Q_OBJECT

private slots:
    void validOperandsDisplaySum();
    void invalidFirstOperandShowsError();
    void invalidSecondOperandShowsError();
    void emptyFirstOperandShowsError();
};

#endif
