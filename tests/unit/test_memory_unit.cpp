#include "test_memory_unit.h"

#include "memory.h"

#include <QString>
#include <QtTest/QtTest>

void TestMemoryUnit::allocationSymmetry()
{
    MemoryAudit::instance().resetTracking();
    MemoryAudit::instance().trackAllocation(1024);
    MemoryAudit::instance().trackAllocation(2048);
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(3072));
    QCOMPARE(MemoryAudit::instance().totalAllocations(), static_cast<std::uint64_t>(2));
    MemoryAudit::instance().trackDeallocation(1024);
    MemoryAudit::instance().trackDeallocation(2048);
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    QCOMPARE(MemoryAudit::instance().outstandingAllocations(), static_cast<std::ptrdiff_t>(0));
    QVERIFY(MemoryAudit::instance().validateNoLeaks());
}

void TestMemoryUnit::scopedBufferReleasesOnDestruction()
{
    MemoryAudit::instance().resetTracking();
    {
        ScopedBuffer buffer(4096);
        QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(4096));
        QCOMPARE(buffer.size(), static_cast<std::size_t>(4096));
        QVERIFY(buffer.data() != nullptr);
    }
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    QVERIFY(MemoryAudit::instance().validateNoLeaks());
}

void TestMemoryUnit::allocationGuardReleasesOnDestruction()
{
    MemoryAudit::instance().resetTracking();
    {
        AllocationGuard guard(8192);
        QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(8192));
    }
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    QVERIFY(MemoryAudit::instance().validateNoLeaks());
}

void TestMemoryUnit::resetTrackingClearsCounters()
{
    MemoryAudit::instance().trackAllocation(256);
    MemoryAudit::instance().trackDeallocation(256);
    MemoryAudit::instance().resetTracking();
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(0));
    QCOMPARE(MemoryAudit::instance().peakUsageBytes(), static_cast<std::size_t>(0));
    QCOMPARE(MemoryAudit::instance().totalAllocations(), static_cast<std::uint64_t>(0));
    QCOMPARE(MemoryAudit::instance().totalDeallocations(), static_cast<std::uint64_t>(0));
}

void TestMemoryUnit::outstandingCountTracksAsymmetry()
{
    MemoryAudit::instance().resetTracking();
    MemoryAudit::instance().trackAllocation(128);
    MemoryAudit::instance().trackAllocation(128);
    MemoryAudit::instance().trackDeallocation(128);
    QCOMPARE(MemoryAudit::instance().outstandingAllocations(), static_cast<std::ptrdiff_t>(1));
    MemoryAudit::instance().trackDeallocation(128);
    QCOMPARE(MemoryAudit::instance().outstandingAllocations(), static_cast<std::ptrdiff_t>(0));
}

void TestMemoryUnit::peakUsageReflectsHighWatermark()
{
    MemoryAudit::instance().resetTracking();
    MemoryAudit::instance().trackAllocation(1000);
    MemoryAudit::instance().trackAllocation(5000);
    QCOMPARE(MemoryAudit::instance().peakUsageBytes(), static_cast<std::size_t>(6000));
    MemoryAudit::instance().trackDeallocation(4000);
    QCOMPARE(MemoryAudit::instance().currentUsageBytes(), static_cast<std::size_t>(2000));
    QCOMPARE(MemoryAudit::instance().peakUsageBytes(), static_cast<std::size_t>(6000));
}

void TestMemoryUnit::formatBytesProducesHumanReadableStrings()
{
    const QString bytes = MemoryAudit::instance().formatBytes(512);
    QVERIFY2(bytes.contains(QStringLiteral("B")), qPrintable(bytes));
    const QString kib = MemoryAudit::instance().formatBytes(2048);
    QVERIFY2(kib.contains(QStringLiteral("KiB")), qPrintable(kib));
    const QString mib = MemoryAudit::instance().formatBytes(5u * 1024u * 1024u);
    QVERIFY2(mib.contains(QStringLiteral("MiB")), qPrintable(mib));
}
