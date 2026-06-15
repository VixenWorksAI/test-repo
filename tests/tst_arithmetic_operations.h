#ifndef TST_ARITHMETIC_OPERATIONS_H
#define TST_ARITHMETIC_OPERATIONS_H

#include <QtTest>

class TestArithmeticPerformance : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void addCompletesUnder100ms();
    void subtractCompletesUnder100ms();
    void multiplyCompletesUnder100ms();
    void divideCompletesUnder100ms();
    void addProducesCorrectResult();
    void subtractProducesCorrectResult();
    void multiplyProducesCorrectResult();
    void divideProducesCorrectResult();
};

#endif
