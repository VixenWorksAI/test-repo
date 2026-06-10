#ifndef TEST_ADDITION_UNIT_H
#define TEST_ADDITION_UNIT_H

#include <QObject>

class TestAdditionUnit : public QObject
{
    Q_OBJECT

private slots:
    void addTwoPositiveIntegers();
    void addTwoNegativeIntegers();
    void addPositiveAndNegative();
    void addWithZero();
    void addTwoZeros();
    void addFractionalValues();
    void addVerySmallFractionalValues();
    void addMaxDoubleMagnitudes();
    void addOppositeNearMaxYieldsNearZero();
    void addReturnsExactIntegerSum();
    void addProducesNegativeResult();
};

#endif
