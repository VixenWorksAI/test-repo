#ifndef TEST_ADDITION_INTEGRATION_H
#define TEST_ADDITION_INTEGRATION_H

#include <QObject>

class TestAdditionIntegration : public QObject
{
    Q_OBJECT

private slots:
    void resultDisplayShowsSumForPositiveIntegers();
    void resultDisplayShowsSumForNegativeIntegers();
    void resultDisplayShowsSumForMixedSigns();
    void resultDisplayShowsSumWithZero();
    void invalidInputSetsErrorAndClearsResult();
    void statusLabelClearsAfterSuccessfulAdd();
};

#endif
