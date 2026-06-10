#include "test_division_unit.h"

#include "arithmeticoperations.h"

#include <cmath>
#include <limits>

#include <QtTest/QtTest>

void TestDivisionUnit::quotientOfPositiveOperands()
{
    const double result = arithmetic::divideNumbers(10.0, 2.0);
    QVERIFY(qFuzzyCompare(result, 5.0));
}

void TestDivisionUnit::quotientOfNegativeAndPositiveOperands()
{
    const double result = arithmetic::divideNumbers(-9.0, 3.0);
    QVERIFY(qFuzzyCompare(result, -3.0));
}

void TestDivisionUnit::quotientOfTwoNegativeOperands()
{
    const double result = arithmetic::divideNumbers(-12.0, -4.0);
    QVERIFY(qFuzzyCompare(result, 3.0));
}

void TestDivisionUnit::quotientWithFractionalResult()
{
    const double result = arithmetic::divideNumbers(1.0, 4.0);
    QVERIFY(qFuzzyCompare(result, 0.25));
}

void TestDivisionUnit::divisionByZeroReturnsQuietNaN()
{
    const double result = arithmetic::divideNumbers(7.0, 0.0);
    QVERIFY(std::isnan(result));
}

void TestDivisionUnit::divisionByNegativeZeroReturnsQuietNaN()
{
    const double result = arithmetic::divideNumbers(7.0, -0.0);
    QVERIFY(std::isnan(result));
}

void TestDivisionUnit::divisionOfZeroNumerator()
{
    const double result = arithmetic::divideNumbers(0.0, 5.0);
    QVERIFY(qFuzzyCompare(result, 0.0));
}

void TestDivisionUnit::quotientWithVeryLargeOperands()
{
    const double result = arithmetic::divideNumbers(1.0e308, 1.0e100);
    QVERIFY(qFuzzyCompare(result, 1.0e208));
}

void TestDivisionUnit::quotientWithVerySmallOperands()
{
    const double result = arithmetic::divideNumbers(1.0, 1.0e-308);
    const double expected = 1.0e308;
    QVERIFY(qFuzzyCompare(result, expected));
}
