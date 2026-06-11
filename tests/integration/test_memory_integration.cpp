#include "test_memory_integration.h"

#include "memory.h"

#include <QString>
#include <QVector>
#include <QtTest/QtTest>

#include <memory>
#include <vector>

void TestMemoryIntegration::mixedOperationsStayUnder50MiB()
{
    MemoryAudit::instance().resetTracking();

    std::vector<std::unique_ptr<ScopedBuffer>> buffers;
    buffers.reserve(32);
    for (int i = 0; i < 32; ++i) {
        buffers.push_back(std::make_unique<ScopedBuffer>(static_cast<std::size_t>(i + 1) * 1024));
    }

    QVector<AllocationGuard *> guards;
    for (int i = 0; i < 16; ++i) {
        guards.append(new AllocationGuard(static_cast<std::size_t>(i + 1) * 512));
    }
    qDeleteAll(guards);
    guards.clear();

    QVERIFY2(MemoryAudit::instance().validateMemoryLimit(),
             qPrintable(QStringLiteral("peak=%1 limit=%2")
                            .arg(MemoryAudit::instance().formatBytes(MemoryAudit::instance().peakUsageBytes()))
                            .arg(MemoryAudit::instance().formatBytes(MemoryAudit::MemoryLimitBytes))));

    buffers.clear();
    QVERIFY(MemoryAudit::instance().validateNoLeaks());
}

void TestMemoryIntegration::bufferAllocationsAreNetZeroAfterWorkload()
{
    MemoryAudit::instance().resetTracking();
    const std::uint64_t baselineAllocs = MemoryAudit::instance().totalAllocations();
    const std::uint64_t baselineFrees = MemoryAudit::instance().totalDeallocations();

    for (int cycle = 0; cycle < 64; ++cycle) {
        ScopedBuffer transient(static_cast<std::size_t>(cycle) * 256 + 1024);
    }

    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    const auto allocDelta = static_cast<std::ptrdiff_t>(MemoryAudit::instance().totalAllocations() - baselineAllocs);
    const auto freeDelta = static_cast<std::ptrdiff_t>(MemoryAudit::instance().totalDeallocations() - baselineFrees);
    QCOMPARE(allocDelta, freeDelta);
}

void TestMemoryIntegration::concurrentScopedBuffersDoNotLeak()
{
    MemoryAudit::instance().resetTracking();
    QVector<ScopedBuffer *> live;
    live.reserve(128);
    for (int i = 0; i < 128; ++i) {
        live.append(new ScopedBuffer(static_cast<std::size_t>(1024 + i * 64)));
    }
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), MemoryAudit::instance().peakUsageBytes());

    for (int i = 0; i < live.size(); ++i) {
        delete live[i];
    }
    live.clear();
    QVERIFY(MemoryAudit::instance().validateNoLeaks());
}
