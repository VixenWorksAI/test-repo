#ifndef TEST_SUBTRACTION_UNIT_H
#define TEST_SUBTRACTION_UNIT_H

#include <QObject>

class TestSubtractionUnit : public QObject
{
    Q_OBJECT

private slots:
    void subtractsPositiveOperands();
    void subtractsNegativeOperands();
    void producesNegativeResult();
    void subtractingZeroReturnsFirstOperand();
    void subtractingFromZeroReturnsNegation();
    void subtractingEqualOperandsYieldsZero();
    void subtractsFractionalOperands();
    void handlesMixedSignOperands();
    void subtractsVeryLargeOperands();
    void subtractsVerySmallOperands();
    void subtractsAcrossSignBoundary();
};

#endif
