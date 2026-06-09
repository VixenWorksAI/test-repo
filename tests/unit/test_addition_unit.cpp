#include "test_addition_unit.h"
#include "arithmeticoperations.h"

#include <QtTest/QtTest>
#include <cmath>
#include <limits>

using arithmetic::addNumbers;
using arithmetic::kMaxDouble;
using arithmetic::kMinDouble;

void TestAdditionUnit::additionOfTwoPositiveNumbers()
{
    QCOMPARE(addNumbers(2.0, 3.0), 5.0);
    QCOMPARE(addNumbers(0.5, 0.25), 0.75);
    QCOMPARE(addNumbers(1.0e6, 2.0e6), 3.0e6);
}

void TestAdditionUnit::additionOfTwoNegativeNumbers()
{
    QCOMPARE(addNumbers(-2.0, -3.0), -5.0);
    QCOMPARE(addNumbers(-0.5, -0.25), -0.75);
    QCOMPARE(addNumbers(-1.0e6, -2.0e6), -3.0e6);
}

void TestAdditionUnit::additionOfLargeAndSmallPreservesPrecision()
{
    const double large = 1.0e15;
    const double small = 1.0;
    const double sum = addNumbers(large, small);
    QVERIFY(sum >= large);
    QVERIFY(sum <= large + 10.0);
}

void TestAdditionUnit::additionOverflowClampsToMaxDouble()
{
    const double result = addNumbers(kMaxDouble, 1.0);
    QCOMPARE(result, kMaxDouble);
    QVERIFY(!std::isinf(result));
}

void TestAdditionUnit::additionUnderflowClampsToMinDouble()
{
    const double result = addNumbers(kMinDouble, -1.0);
    QCOMPARE(result, kMinDouble);
    QVERIFY(!std::isinf(result));
}
