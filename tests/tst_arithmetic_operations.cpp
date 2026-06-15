#include "tst_arithmetic_operations.h"
#include "arithmeticoperations.h"

#include <QElapsedTimer>
#include <cmath>

namespace {
constexpr int kIterationCount = 1000000;
}

void TestArithmeticPerformance::initTestCase()
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
}

void TestArithmeticPerformance::addCompletesUnder100ms()
{
    QElapsedTimer timer;
    timer.start();
    double accumulator = 0.0;
    for (int i = 0; i < kIterationCount; ++i) {
        accumulator += arithmetic::addNumbers(static_cast<double>(i), 1.5);
    }
    const qint64 elapsedMs = timer.elapsed();
    QVERIFY2(elapsedMs < 100,
        qPrintable(QString("addNumbers: %1ms exceeds 100ms budget").arg(elapsedMs)));
    Q_UNUSED(accumulator);
}

void TestArithmeticPerformance::subtractCompletesUnder100ms()
{
    QElapsedTimer timer;
    timer.start();
    double accumulator = 0.0;
    for (int i = 0; i < kIterationCount; ++i) {
        accumulator += arithmetic::subtractNumbers(static_cast<double>(i), 0.5);
    }
    const qint64 elapsedMs = timer.elapsed();
    QVERIFY2(elapsedMs < 100,
        qPrintable(QString("subtractNumbers: %1ms exceeds 100ms budget").arg(elapsedMs)));
    Q_UNUSED(accumulator);
}

void TestArithmeticPerformance::multiplyCompletesUnder100ms()
{
    QElapsedTimer timer;
    timer.start();
    double accumulator = 0.0;
    for (int i = 1; i <= kIterationCount; ++i) {
        accumulator += arithmetic::multiplyNumbers(static_cast<double>(i), 2.0);
    }
    const qint64 elapsedMs = timer.elapsed();
    QVERIFY2(elapsedMs < 100,
        qPrintable(QString("multiplyNumbers: %1ms exceeds 100ms budget").arg(elapsedMs)));
    Q_UNUSED(accumulator);
}

void TestArithmeticPerformance::divideCompletesUnder100ms()
{
    QElapsedTimer timer;
    timer.start();
    double accumulator = 0.0;
    for (int i = 1; i <= kIterationCount; ++i) {
        accumulator += arithmetic::divideNumbers(static_cast<double>(i) * 2.0, 2.0);
    }
    const qint64 elapsedMs = timer.elapsed();
    QVERIFY2(elapsedMs < 100,
        qPrintable(QString("divideNumbers: %1ms exceeds 100ms budget").arg(elapsedMs)));
    Q_UNUSED(accumulator);
}

void TestArithmeticPerformance::addProducesCorrectResult()
{
    QCOMPARE(arithmetic::addNumbers(2.0, 3.0), 5.0);
    QCOMPARE(arithmetic::addNumbers(-1.5, 1.5), 0.0);
}

void TestArithmeticPerformance::subtractProducesCorrectResult()
{
    QCOMPARE(arithmetic::subtractNumbers(10.0, 4.0), 6.0);
    QCOMPARE(arithmetic::subtractNumbers(0.0, 0.0), 0.0);
}

void TestArithmeticPerformance::multiplyProducesCorrectResult()
{
    QCOMPARE(arithmetic::multiplyNumbers(3.0, 4.0), 12.0);
    QCOMPARE(arithmetic::multiplyNumbers(0.0, 999.0), 0.0);
}

void TestArithmeticPerformance::divideProducesCorrectResult()
{
    QCOMPARE(arithmetic::divideNumbers(10.0, 2.0), 5.0);
    QVERIFY(std::isnan(arithmetic::divideNumbers(1.0, 0.0)));
}
