#include "test_addition_unit.h"
#include "arithmeticoperations.h"

#include <QtTest/QtTest>
#include <limits>

void TestAdditionUnit::addTwoPositiveIntegers()
{
    QCOMPARE(arithmetic::addNumbers(2.0, 3.0), 5.0);
}

void TestAdditionUnit::addTwoNegativeIntegers()
{
    QCOMPARE(arithmetic::addNumbers(-4.0, -7.0), -11.0);
}

void TestAdditionUnit::addPositiveAndNegative()
{
    QCOMPARE(arithmetic::addNumbers(10.0, -3.0), 7.0);
    QCOMPARE(arithmetic::addNumbers(-10.0, 3.0), -7.0);
}

void TestAdditionUnit::addWithZero()
{
    QCOMPARE(arithmetic::addNumbers(0.0, 42.0), 42.0);
    QCOMPARE(arithmetic::addNumbers(42.0, 0.0), 42.0);
    QCOMPARE(arithmetic::addNumbers(0.0, -42.0), -42.0);
}

void TestAdditionUnit::addTwoZeros()
{
    QCOMPARE(arithmetic::addNumbers(0.0, 0.0), 0.0);
}

void TestAdditionUnit::addFractionalValues()
{
    const double result = arithmetic::addNumbers(0.1, 0.2);
    QVERIFY(qFuzzyCompare(result, 0.3));
}

void TestAdditionUnit::addVerySmallFractionalValues()
{
    const double tiny = 1e-15;
    const double result = arithmetic::addNumbers(tiny, tiny);
    QCOMPARE(result, 2e-15);
}

void TestAdditionUnit::addMaxDoubleMagnitudes()
{
    const double max = std::numeric_limits<double>::max();
    const double result = arithmetic::addNumbers(max, 0.0);
    QCOMPARE(result, max);
}

void TestAdditionUnit::addOppositeNearMaxYieldsNearZero()
{
    const double max = std::numeric_limits<double>::max();
    const double result = arithmetic::addNumbers(max, -max);
    QCOMPARE(result, 0.0);
}

void TestAdditionUnit::addReturnsExactIntegerSum()
{
    const double result = arithmetic::addNumbers(123456789.0, 987654321.0);
    QCOMPARE(result, 1111111110.0);
}

void TestAdditionUnit::addProducesNegativeResult()
{
    QVERIFY(arithmetic::addNumbers(-2.5, -3.5) < 0.0);
    QCOMPARE(arithmetic::addNumbers(-2.5, -3.5), -6.0);
}
