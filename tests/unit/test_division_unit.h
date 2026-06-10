#ifndef TEST_DIVISION_UNIT_H
#define TEST_DIVISION_UNIT_H

#include <QObject>

class TestDivisionUnit : public QObject {
    Q_OBJECT

private slots:
    void quotientOfPositiveOperands();
    void quotientOfNegativeAndPositiveOperands();
    void quotientOfTwoNegativeOperands();
    void quotientWithFractionalResult();
    void divisionByZeroReturnsQuietNaN();
    void divisionByNegativeZeroReturnsQuietNaN();
    void divisionOfZeroNumerator();
    void quotientWithVeryLargeOperands();
    void quotientWithVerySmallOperands();
};

#endif
