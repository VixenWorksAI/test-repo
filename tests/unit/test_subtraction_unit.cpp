#include "test_subtraction_unit.h"

#include "arithmeticoperations.h"

#include <QtTest>
#include <cmath>
#include <limits>

void TestSubtractionUnit::subtractsPositiveOperands()
{
    QCOMPARE(arithmetic::subtractNumbers(7.0, 3.0), 4.0);
    QCOMPARE(arithmetic::subtractNumbers(100.0, 25.0), 75.0);
    QCOMPARE(arithmetic::subtractNumbers(1.5, 0.25), 1.25);
}

void TestSubtractionUnit::subtractsNegativeOperands()
{
    QCOMPARE(arithmetic::subtractNumbers(-5.0, -3.0), -2.0);
    QCOMPARE(arithmetic::subtractNumbers(-10.0, -4.0), -6.0);
    QCOMPARE(arithmetic::subtractNumbers(-1.5, -1.5), 0.0);
}

void TestSubtractionUnit::producesNegativeResult()
{
    QCOMPARE(arithmetic::subtractNumbers(3.0, 7.0), -4.0);
    QCOMPARE(arithmetic::subtractNumbers(0.0, 5.0), -5.0);
}

void TestSubtractionUnit::subtractingZeroReturnsFirstOperand()
{
    QCOMPARE(arithmetic::subtractNumbers(42.0, 0.0), 42.0);
    QCOMPARE(arithmetic::subtractNumbers(-7.5, 0.0), -7.5);
    QCOMPARE(arithmetic::subtractNumbers(0.0, 0.0), 0.0);
}

void TestSubtractionUnit::subtractingFromZeroReturnsNegation()
{
    QCOMPARE(arithmetic::subtractNumbers(0.0, 9.0), -9.0);
    QCOMPARE(arithmetic::subtractNumbers(0.0, -3.5), 3.5);
}

void TestSubtractionUnit::subtractingEqualOperandsYieldsZero()
{
    QCOMPARE(arithmetic::subtractNumbers(5.0, 5.0), 0.0);
    QCOMPARE(arithmetic::subtractNumbers(-4.0, -4.0), 0.0);
    QCOMPARE(arithmetic::subtractNumbers(0.0, 0.0), 0.0);
}

void TestSubtractionUnit::subtractsFractionalOperands()
{
    QVERIFY(qFuzzyCompare(arithmetic::subtractNumbers(1.25, 0.5), 0.75));
    QVERIFY(qFuzzyCompare(arithmetic::subtractNumbers(3.14159, 2.71828), 0.42331));
    QVERIFY(qFuzzyCompare(arithmetic::subtractNumbers(-1.5, 0.25), -1.75));
}

void TestSubtractionUnit::handlesMixedSignOperands()
{
    QCOMPARE(arithmetic::subtractNumbers(10.0, -4.0), 14.0);
    QCOMPARE(arithmetic::subtractNumbers(-10.0, 4.0), -14.0);
    QCOMPARE(arithmetic::subtractNumbers(6.0, -6.0), 12.0);
}

void TestSubtractionUnit::subtractsVeryLargeOperands()
{
    constexpr double kLargeA = 1.0e308;
    constexpr double kLargeB = 1.0e307;
    const double largeResult = arithmetic::subtractNumbers(kLargeA, kLargeB);
    QVERIFY(std::isfinite(largeResult));
    QVERIFY(largeResult > 0.0);
    QVERIFY(qFuzzyCompare(largeResult, 9.0e307));

    const double minDouble = std::numeric_limits<double>::min();
    const double maxDouble = std::numeric_limits<double>::max();
    const double maxMinusEpsilon = arithmetic::subtractNumbers(maxDouble, minDouble);
    QVERIFY(maxMinusEpsilon > 0.0);
    QVERIFY(maxMinusEpsilon <= maxDouble);
}

void TestSubtractionUnit::subtractsVerySmallOperands()
{
    const double result = arithmetic::subtractNumbers(1.0e-308, 1.0e-308);
    QCOMPARE(result, 0.0);

    const double smallDiff = arithmetic::subtractNumbers(0.5e-307, 0.5e-307);
    QCOMPARE(smallDiff, 0.0);
}

void TestSubtractionUnit::subtractsAcrossSignBoundary()
{
    const double result = arithmetic::subtractNumbers(0.0001, 0.0002);
    QVERIFY(result < 0.0);
    QVERIFY(qFuzzyCompare(result, -0.0001));

    const double negativeToPositive = arithmetic::subtractNumbers(-5.5, 5.5);
    QCOMPARE(negativeToPositive, -11.0);
}
