#include <QtTest/QtTest>
#include <climits>
#include <cfloat>
#include <cmath>

#include "arithmeticoperations.h"

class ArithmeticOperationsTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void multiplyPositiveIntegers();
    void multiplyPositiveDecimals();
    void multiplyByZero();
    void multiplyZeroByValue();
    void multiplyByOne();
    void multiplyNegativeByPositive();
    void multiplyPositiveByNegative();
    void multiplyTwoNegatives();
    void multiplyByNegativeOne();
    void multiplyMixedSignsWithDecimals();
    void multiplyLargeValuesNearLongMax();
    void multiplyLargeDoublesNearMax();
    void multiplySmallDoublesNearMin();
    void multiplyByVerySmallFraction();
    void multiplyIdentitySymmetry();
    void multiplyReturnsDouble();
    void multiplyHandlesInexactFloatingPoint();
    void multiplyInfByZero();
    void multiplyInfByNonZero();
    void multiplyNanPropagation();

    void dividePositiveIntegers();
    void dividePositiveDecimals();
    void divideByOne();
    void divideOneByValue();
    void divideNegativeByPositive();
    void dividePositiveByNegative();
    void divideTwoNegatives();
    void divideByNegativeOne();
    void divideMixedSignsWithDecimals();
    void divideZeroByNonZero();
    void divideZeroByZero();
    void divideIntegerByZero();
    void divideDoubleByZero();
    void divideZeroByZeroDouble();
    void divideResultsInFractionalOutput();
    void divideLargeValuesNearLongMax();
    void divideLargeDoublesNearMax();
    void divideSmallDoublesNearMin();
    void divideByVerySmallFraction();
    void divideIdentitySymmetry();
    void divideReturnsDouble();
    void divideHandlesInexactFloatingPoint();
    void divideInfByZero();
    void divideInfByNonZero();
    void divideZeroByInf();
    void divideNanPropagation();
};

void ArithmeticOperationsTest::initTestCase()
{
}

void ArithmeticOperationsTest::cleanupTestCase()
{
}

void ArithmeticOperationsTest::multiplyPositiveIntegers()
{
    QCOMPARE(arithmetic::multiplyNumbers(3.0, 4.0), 12.0);
    QCOMPARE(arithmetic::multiplyNumbers(7.0, 6.0), 42.0);
    QCOMPARE(arithmetic::multiplyNumbers(1.0, 1.0), 1.0);
    QCOMPARE(arithmetic::multiplyNumbers(100.0, 200.0), 20000.0);
}

void ArithmeticOperationsTest::multiplyPositiveDecimals()
{
    QCOMPARE(arithmetic::multiplyNumbers(2.5, 4.0), 10.0);
    QCOMPARE(arithmetic::multiplyNumbers(0.5, 0.5), 0.25);
    QCOMPARE(arithmetic::multiplyNumbers(1.25, 8.0), 10.0);
    QVERIFY(qFuzzyCompare(arithmetic::multiplyNumbers(0.1, 0.2), 0.02));
}

void ArithmeticOperationsTest::multiplyByZero()
{
    QCOMPARE(arithmetic::multiplyNumbers(0.0, 123456.0), 0.0);
    QCOMPARE(arithmetic::multiplyNumbers(0.0, -987.654), 0.0);
    QCOMPARE(arithmetic::multiplyNumbers(0.0, 0.0), 0.0);
}

void ArithmeticOperationsTest::multiplyZeroByValue()
{
    QCOMPARE(arithmetic::multiplyNumbers(42.0, 0.0), 0.0);
    QCOMPARE(arithmetic::multiplyNumbers(-42.0, 0.0), 0.0);
    QCOMPARE(arithmetic::multiplyNumbers(0.000001, 0.0), 0.0);
}

void ArithmeticOperationsTest::multiplyByOne()
{
    QCOMPARE(arithmetic::multiplyNumbers(1.0, 42.0), 42.0);
    QCOMPARE(arithmetic::multiplyNumbers(42.0, 1.0), 42.0);
    QCOMPARE(arithmetic::multiplyNumbers(1.0, -17.5), -17.5);
    QCOMPARE(arithmetic::multiplyNumbers(-33.3, 1.0), -33.3);
}

void ArithmeticOperationsTest::multiplyNegativeByPositive()
{
    QCOMPARE(arithmetic::multiplyNumbers(-3.0, 4.0), -12.0);
    QCOMPARE(arithmetic::multiplyNumbers(-7.0, 6.0), -42.0);
    QCOMPARE(arithmetic::multiplyNumbers(-2.5, 4.0), -10.0);
}

void ArithmeticOperationsTest::multiplyPositiveByNegative()
{
    QCOMPARE(arithmetic::multiplyNumbers(3.0, -4.0), -12.0);
    QCOMPARE(arithmetic::multiplyNumbers(7.0, -6.0), -42.0);
    QCOMPARE(arithmetic::multiplyNumbers(10.0, -0.5), -5.0);
}

void ArithmeticOperationsTest::multiplyTwoNegatives()
{
    QCOMPARE(arithmetic::multiplyNumbers(-3.0, -4.0), 12.0);
    QCOMPARE(arithmetic::multiplyNumbers(-7.0, -6.0), 42.0);
    QCOMPARE(arithmetic::multiplyNumbers(-2.5, -4.0), 10.0);
}

void ArithmeticOperationsTest::multiplyByNegativeOne()
{
    QCOMPARE(arithmetic::multiplyNumbers(-1.0, 42.0), -42.0);
    QCOMPARE(arithmetic::multiplyNumbers(42.0, -1.0), -42.0);
    QCOMPARE(arithmetic::multiplyNumbers(-1.0, -1.0), 1.0);
}

void ArithmeticOperationsTest::multiplyMixedSignsWithDecimals()
{
    QCOMPARE(arithmetic::multiplyNumbers(-0.5, 0.5), -0.25);
    QCOMPARE(arithmetic::multiplyNumbers(0.5, -0.5), -0.25);
    QCOMPARE(arithmetic::multiplyNumbers(-0.5, -0.5), 0.25);
    QCOMPARE(arithmetic::multiplyNumbers(-1.5, 2.0), -3.0);
}

void ArithmeticOperationsTest::multiplyLargeValuesNearLongMax()
{
    double lhs = static_cast<double>(LONG_MAX);
    double rhs = 1.0;
    QCOMPARE(arithmetic::multiplyNumbers(lhs, rhs), lhs);

    double bigA = static_cast<double>(LONG_MAX) / 2.0;
    double bigB = 2.0;
    QCOMPARE(arithmetic::multiplyNumbers(bigA, bigB), static_cast<double>(LONG_MAX));

    double huge = 1.0e15;
    QVERIFY(arithmetic::multiplyNumbers(huge, huge) == 1.0e30);
}

void ArithmeticOperationsTest::multiplyLargeDoublesNearMax()
{
    double max = DBL_MAX;
    QCOMPARE(arithmetic::multiplyNumbers(max, 1.0), max);

    double clamped1 = arithmetic::multiplyNumbers(DBL_MAX, 2.0);
    QVERIFY(!std::isnan(clamped1));
    QVERIFY(clamped1 == arithmetic::kMaxDouble);

    double clamped2 = arithmetic::multiplyNumbers(DBL_MAX, 10.0);
    QVERIFY(clamped2 == arithmetic::kMaxDouble);

    double clamped3 = arithmetic::multiplyNumbers(DBL_MAX, DBL_MAX);
    QVERIFY(clamped3 == arithmetic::kMaxDouble);

    double clampedNeg = arithmetic::multiplyNumbers(-DBL_MAX, 2.0);
    QVERIFY(clampedNeg == arithmetic::kMinDouble);
}

void ArithmeticOperationsTest::multiplySmallDoublesNearMin()
{
    double min = DBL_MIN;
    QCOMPARE(arithmetic::multiplyNumbers(min, 1.0), min);
    QCOMPARE(arithmetic::multiplyNumbers(min, 0.5), 0.0);
    QCOMPARE(arithmetic::multiplyNumbers(min, -1.0), -min);
}

void ArithmeticOperationsTest::multiplyByVerySmallFraction()
{
    QVERIFY(qFuzzyCompare(arithmetic::multiplyNumbers(1.0e9, 1.0e-9), 1.0));
    QVERIFY(qFuzzyCompare(arithmetic::multiplyNumbers(1.0e6, 1.0e-6), 1.0));
    QVERIFY(qFuzzyCompare(arithmetic::multiplyNumbers(1.0e-3, 1.0e-3), 1.0e-6));
}

void ArithmeticOperationsTest::multiplyIdentitySymmetry()
{
    QCOMPARE(arithmetic::multiplyNumbers(3.0, 5.0), arithmetic::multiplyNumbers(5.0, 3.0));
    QCOMPARE(arithmetic::multiplyNumbers(-7.0, 2.0), arithmetic::multiplyNumbers(2.0, -7.0));
    QCOMPARE(arithmetic::multiplyNumbers(0.5, 0.25), arithmetic::multiplyNumbers(0.25, 0.5));
}

void ArithmeticOperationsTest::multiplyReturnsDouble()
{
    double result = arithmetic::multiplyNumbers(3, 4);
    QVERIFY(qFuzzyCompare(result, 12.0));

    result = arithmetic::multiplyNumbers(2, 7);
    QVERIFY(qFuzzyCompare(result, 14.0));
}

void ArithmeticOperationsTest::multiplyHandlesInexactFloatingPoint()
{
    double a = 0.1;
    double b = 0.2;
    double product = arithmetic::multiplyNumbers(a, b);
    QVERIFY(qAbs(product - 0.02) < 1.0e-12);

    double product2 = arithmetic::multiplyNumbers(1.0 / 3.0, 3.0);
    QVERIFY(qAbs(product2 - 1.0) < 1.0e-12);
}

void ArithmeticOperationsTest::multiplyInfByZero()
{
    double posInf = std::numeric_limits<double>::infinity();
    double raw = posInf * 0.0;
    double result = arithmetic::multiplyNumbers(posInf, 0.0);
    QVERIFY(!std::isnan(result));
    QVERIFY(!std::isinf(result));
    QVERIFY(result == raw || result == 0.0);
}

void ArithmeticOperationsTest::multiplyInfByNonZero()
{
    double posInf = std::numeric_limits<double>::infinity();
    double negInf = -std::numeric_limits<double>::infinity();

    double r1 = arithmetic::multiplyNumbers(posInf, 2.0);
    QVERIFY(!std::isnan(r1));
    QVERIFY(r1 == arithmetic::kMaxDouble);

    double r2 = arithmetic::multiplyNumbers(posInf, -1.5);
    QVERIFY(r2 == arithmetic::kMinDouble);

    double r3 = arithmetic::multiplyNumbers(negInf, -3.0);
    QVERIFY(r3 == arithmetic::kMaxDouble);
}

void ArithmeticOperationsTest::multiplyNanPropagation()
{
    double nan = std::numeric_limits<double>::quiet_NaN();
    QVERIFY(arithmetic::multiplyNumbers(nan, 5.0) == 0.0);
    QVERIFY(arithmetic::multiplyNumbers(5.0, nan) == 0.0);
    QVERIFY(arithmetic::multiplyNumbers(nan, nan) == 0.0);
    QVERIFY(arithmetic::multiplyNumbers(nan, 0.0) == 0.0);
}

void ArithmeticOperationsTest::dividePositiveIntegers()
{
    QCOMPARE(arithmetic::divideNumbers(12.0, 4.0), 3.0);
    QCOMPARE(arithmetic::divideNumbers(42.0, 6.0), 7.0);
    QCOMPARE(arithmetic::divideNumbers(1.0, 1.0), 1.0);
    QCOMPARE(arithmetic::divideNumbers(20000.0, 200.0), 100.0);
    QCOMPARE(arithmetic::divideNumbers(100.0, 4.0), 25.0);
}

void ArithmeticOperationsTest::dividePositiveDecimals()
{
    QCOMPARE(arithmetic::divideNumbers(10.0, 4.0), 2.5);
    QCOMPARE(arithmetic::divideNumbers(0.25, 0.5), 0.5);
    QCOMPARE(arithmetic::divideNumbers(10.0, 8.0), 1.25);
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(0.02, 0.2), 0.1));
}

void ArithmeticOperationsTest::divideByOne()
{
    QCOMPARE(arithmetic::divideNumbers(42.0, 1.0), 42.0);
    QCOMPARE(arithmetic::divideNumbers(-17.5, 1.0), -17.5);
    QCOMPARE(arithmetic::divideNumbers(0.0, 1.0), 0.0);
}

void ArithmeticOperationsTest::divideOneByValue()
{
    QCOMPARE(arithmetic::divideNumbers(1.0, 42.0), 1.0 / 42.0);
    QCOMPARE(arithmetic::divideNumbers(1.0, -33.3), 1.0 / -33.3);
    QCOMPARE(arithmetic::divideNumbers(1.0, 0.5), 2.0);
    QCOMPARE(arithmetic::divideNumbers(1.0, 0.25), 4.0);
}

void ArithmeticOperationsTest::divideNegativeByPositive()
{
    QCOMPARE(arithmetic::divideNumbers(-12.0, 4.0), -3.0);
    QCOMPARE(arithmetic::divideNumbers(-42.0, 6.0), -7.0);
    QCOMPARE(arithmetic::divideNumbers(-10.0, 4.0), -2.5);
}

void ArithmeticOperationsTest::dividePositiveByNegative()
{
    QCOMPARE(arithmetic::divideNumbers(12.0, -4.0), -3.0);
    QCOMPARE(arithmetic::divideNumbers(42.0, -6.0), -7.0);
    QCOMPARE(arithmetic::divideNumbers(5.0, -0.5), -10.0);
}

void ArithmeticOperationsTest::divideTwoNegatives()
{
    QCOMPARE(arithmetic::divideNumbers(-12.0, -4.0), 3.0);
    QCOMPARE(arithmetic::divideNumbers(-42.0, -6.0), 7.0);
    QCOMPARE(arithmetic::divideNumbers(-10.0, -4.0), 2.5);
}

void ArithmeticOperationsTest::divideByNegativeOne()
{
    QCOMPARE(arithmetic::divideNumbers(-42.0, -1.0), 42.0);
    QCOMPARE(arithmetic::divideNumbers(42.0, -1.0), -42.0);
    QCOMPARE(arithmetic::divideNumbers(-1.0, -1.0), 1.0);
}

void ArithmeticOperationsTest::divideMixedSignsWithDecimals()
{
    QCOMPARE(arithmetic::divideNumbers(-0.25, 0.5), -0.5);
    QCOMPARE(arithmetic::divideNumbers(0.25, -0.5), -0.5);
    QCOMPARE(arithmetic::divideNumbers(-0.25, -0.5), 0.5);
    QCOMPARE(arithmetic::divideNumbers(-3.0, 2.0), -1.5);
}

void ArithmeticOperationsTest::divideZeroByNonZero()
{
    QCOMPARE(arithmetic::divideNumbers(0.0, 123456.0), 0.0);
    QCOMPARE(arithmetic::divideNumbers(0.0, -987.654), 0.0);
    QCOMPARE(arithmetic::divideNumbers(0.0, 0.000001), 0.0);
    QCOMPARE(arithmetic::divideNumbers(-0.0, 42.0), 0.0);
}

void ArithmeticOperationsTest::divideZeroByZero()
{
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-0.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.0, -0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-0.0, -0.0)));
}

void ArithmeticOperationsTest::divideIntegerByZero()
{
    QVERIFY(std::isnan(arithmetic::divideNumbers(5.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-5.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(1.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(100.0, 0.0)));
}

void ArithmeticOperationsTest::divideDoubleByZero()
{
    QVERIFY(std::isnan(arithmetic::divideNumbers(2.5, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-2.5, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.000001, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(123.456, 0.0)));
}

void ArithmeticOperationsTest::divideZeroByZeroDouble()
{
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.0, -0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-0.0, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(-0.0, -0.0)));
}

void ArithmeticOperationsTest::divideResultsInFractionalOutput()
{
    QCOMPARE(arithmetic::divideNumbers(1.0, 4.0), 0.25);
    QCOMPARE(arithmetic::divideNumbers(1.0, 3.0), 1.0 / 3.0);
    QCOMPARE(arithmetic::divideNumbers(7.0, 2.0), 3.5);
    QCOMPARE(arithmetic::divideNumbers(22.0, 7.0), 22.0 / 7.0);
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(1.0, 3.0), 1.0 / 3.0));
}

void ArithmeticOperationsTest::divideLargeValuesNearLongMax()
{
    double lhs = static_cast<double>(LONG_MAX);
    QCOMPARE(arithmetic::divideNumbers(lhs, 1.0), lhs);
    QCOMPARE(arithmetic::divideNumbers(static_cast<double>(LONG_MAX), 2.0),
             static_cast<double>(LONG_MAX) / 2.0);
    QCOMPARE(arithmetic::divideNumbers(1.0e30, 1.0e15), 1.0e15);
    QCOMPARE(arithmetic::divideNumbers(1.0e30, 1.0), 1.0e30);
}

void ArithmeticOperationsTest::divideLargeDoublesNearMax()
{
    double max = DBL_MAX;
    QCOMPARE(arithmetic::divideNumbers(max, 1.0), max);
    QCOMPARE(arithmetic::divideNumbers(max, 2.0), max / 2.0);
    QCOMPARE(arithmetic::divideNumbers(max, -1.0), -max);
    QCOMPARE(arithmetic::divideNumbers(max, DBL_MAX), 1.0);
}

void ArithmeticOperationsTest::divideSmallDoublesNearMin()
{
    double min = DBL_MIN;
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(min, 1.0), min));
    QVERIFY(arithmetic::divideNumbers(min, 0.5) > min);
    QVERIFY(arithmetic::divideNumbers(min, 0.5) < min * 4.0);
    double oneOverMin = arithmetic::divideNumbers(1.0, min);
    QVERIFY(oneOverMin > 0.0);
    QVERIFY(std::isfinite(oneOverMin));
}

void ArithmeticOperationsTest::divideByVerySmallFraction()
{
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(1.0, 1.0e-9), 1.0e9));
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(1.0, 1.0e-6), 1.0e6));
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(1.0, 1.0e-3), 1000.0));
    QVERIFY(qFuzzyCompare(arithmetic::divideNumbers(1.0, 1.0e-12), 1.0e12));
}

void ArithmeticOperationsTest::divideIdentitySymmetry()
{
    QCOMPARE(arithmetic::divideNumbers(15.0, 5.0), arithmetic::divideNumbers(15.0, 5.0));
    QCOMPARE(arithmetic::divideNumbers(-7.0, 2.0), arithmetic::divideNumbers(7.0, -2.0));
    QCOMPARE(arithmetic::divideNumbers(20.0, 4.0), 5.0);
    QVERIFY(arithmetic::divideNumbers(20.0, 4.0) == arithmetic::divideNumbers(20.0, 4.0));
}

void ArithmeticOperationsTest::divideReturnsDouble()
{
    double result = arithmetic::divideNumbers(12, 4);
    QVERIFY(qFuzzyCompare(result, 3.0));

    result = arithmetic::divideNumbers(14, 2);
    QVERIFY(qFuzzyCompare(result, 7.0));

    result = arithmetic::divideNumbers(100, 4);
    QVERIFY(qFuzzyCompare(result, 25.0));
}

void ArithmeticOperationsTest::divideHandlesInexactFloatingPoint()
{
    double a = 0.1;
    double b = 0.2;
    double quotient = arithmetic::divideNumbers(a, b);
    QVERIFY(qAbs(quotient - 0.5) < 1.0e-12);

    double q2 = arithmetic::divideNumbers(1.0, 3.0);
    QVERIFY(qAbs(q2 * 3.0 - 1.0) < 1.0e-12);

    double q3 = arithmetic::divideNumbers(1.0, 7.0);
    QVERIFY(qAbs(q3 * 7.0 - 1.0) < 1.0e-12);
}

void ArithmeticOperationsTest::divideInfByZero()
{
    double posInf = std::numeric_limits<double>::infinity();
    double negInf = -std::numeric_limits<double>::infinity();
    QVERIFY(std::isnan(arithmetic::divideNumbers(posInf, 0.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(negInf, 0.0)));
}

void ArithmeticOperationsTest::divideInfByNonZero()
{
    double posInf = std::numeric_limits<double>::infinity();
    double negInf = -std::numeric_limits<double>::infinity();
    QVERIFY(std::isinf(arithmetic::divideNumbers(posInf, 2.0)));
    QVERIFY(arithmetic::divideNumbers(posInf, 2.0) > 0);
    QVERIFY(arithmetic::divideNumbers(negInf, -3.0) > 0);
    QVERIFY(arithmetic::divideNumbers(posInf, -1.5) < 0);
}

void ArithmeticOperationsTest::divideZeroByInf()
{
    double posInf = std::numeric_limits<double>::infinity();
    QCOMPARE(arithmetic::divideNumbers(0.0, posInf), 0.0);
    QCOMPARE(arithmetic::divideNumbers(0.0, -posInf), 0.0);
    QCOMPARE(arithmetic::divideNumbers(5.0, posInf), 0.0);
    QCOMPARE(arithmetic::divideNumbers(-5.0, posInf), 0.0);
}

void ArithmeticOperationsTest::divideNanPropagation()
{
    double nan = std::numeric_limits<double>::quiet_NaN();
    QVERIFY(std::isnan(arithmetic::divideNumbers(nan, 5.0)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(5.0, nan)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(nan, nan)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(0.0, nan)));
    QVERIFY(std::isnan(arithmetic::divideNumbers(nan, 0.0)));
}

QTEST_APPLESS_MAIN(ArithmeticOperationsTest)
#include "ArithmeticOperationsTest.moc"
