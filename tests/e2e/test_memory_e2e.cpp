#include "test_memory_e2e.h"

#include "memory.h"

#include <QString>
#include <QtTest/QtTest>

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

void TestMemoryE2E::longRunningStabilityHoldsBelowLimit()
{
    MemoryAudit::instance().resetTracking();

    constexpr int iterationCount = 4096;

    for (int i = 0; i < iterationCount; ++i) {
        std::vector<std::unique_ptr<ScopedBuffer>> batch;
        batch.reserve(4);
        const std::size_t size = static_cast<std::size_t>((i % 8 + 1) * 4096);
        for (int b = 0; b < 4; ++b) {
            batch.push_back(std::make_unique<ScopedBuffer>(size));
        }
    }

    QVERIFY2(MemoryAudit::instance().peakUsageBytes() <= MemoryAudit::MemoryLimitBytes,
             qPrintable(QStringLiteral("peak=%1 limit=%2")
                            .arg(MemoryAudit::instance().formatBytes(MemoryAudit::instance().peakUsageBytes()))
                            .arg(MemoryAudit::instance().formatBytes(MemoryAudit::MemoryLimitBytes))));
    QVERIFY(MemoryAudit::instance().validateMemoryLimit());
}

void TestMemoryE2E::longRunningStabilityHasNoNetLeakGrowth()
{
    MemoryAudit::instance().resetTracking();
    constexpr int iterationCount = 4096;

    auto runWave = [](int offset) {
        std::vector<std::unique_ptr<ScopedBuffer>> wave;
        wave.reserve(6);
        for (int j = 0; j < 6; ++j) {
            wave.push_back(std::make_unique<ScopedBuffer>(static_cast<std::size_t>((offset + j) % 5 + 1) * 1024));
        }
    };

    for (int i = 0; i < iterationCount; ++i) {
        runWave(i);
    }

    QVERIFY(MemoryAudit::instance().validateNoLeaks());
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    QCOMPARE(MemoryAudit::instance().outstandingAllocations(), static_cast<std::ptrdiff_t>(0));
}
