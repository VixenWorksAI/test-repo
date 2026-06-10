#ifndef TEST_SUBTRACTION_INTEGRATION_H
#define TEST_SUBTRACTION_INTEGRATION_H

#include <QObject>

class TestSubtractionIntegration : public QObject
{
    Q_OBJECT

private slots:
    void resultDisplayShowsDifferenceForPositiveIntegers();
    void resultDisplayShowsDifferenceForNegativeIntegers();
    void resultDisplayShowsDifferenceForMixedSigns();
    void resultDisplayShowsDifferenceWithZero();
    void invalidInputSetsErrorAndClearsResult();
    void statusLabelClearsAfterSuccessfulSubtract();
};

#endif
