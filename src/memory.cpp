#include "memory.h"

#include <QMutex>
#include <QMutexLocker>

#include <algorithm>

namespace
{
QMutex &auditMutex()
{
    static QMutex mutex;
    return mutex;
}

void updatePeakLocked(std::size_t current, std::atomic<std::size_t> &peak)
{
    std::size_t observed = peak.load(std::memory_order_relaxed);
    while (current > observed) {
        if (peak.compare_exchange_weak(observed, current, std::memory_order_relaxed)) {
            return;
        }
    }
}
}

MemoryAudit &MemoryAudit::instance()
{
    static MemoryAudit instance;
    return instance;
}

void MemoryAudit::trackAllocation(std::size_t bytes)
{
    QMutexLocker locker(&auditMutex());
    const std::size_t current = m_currentBytes.fetch_add(bytes, std::memory_order_relaxed) + bytes;
    m_totalAllocations.fetch_add(1, std::memory_order_relaxed);
    updatePeakLocked(current, m_peakBytes);
}

void MemoryAudit::trackDeallocation(std::size_t bytes)
{
    QMutexLocker locker(&auditMutex());
    m_currentBytes.fetch_sub(bytes, std::memory_order_relaxed);
    m_totalDeallocations.fetch_add(1, std::memory_order_relaxed);
}

void MemoryAudit::resetTracking()
{
    QMutexLocker locker(&auditMutex());
    m_currentBytes.store(0, std::memory_order_relaxed);
    m_peakBytes.store(0, std::memory_order_relaxed);
    m_totalAllocations.store(0, std::memory_order_relaxed);
    m_totalDeallocations.store(0, std::memory_order_relaxed);
}

std::size_t MemoryAudit::currentUsageBytes() const
{
    return m_currentBytes.load(std::memory_order_relaxed);
}

std::size_t MemoryAudit::peakUsageBytes() const
{
    return m_peakBytes.load(std::memory_order_relaxed);
}

std::uint64_t MemoryAudit::totalAllocations() const
{
    return m_totalAllocations.load(std::memory_order_relaxed);
}

std::uint64_t MemoryAudit::totalDeallocations() const
{
    return m_totalDeallocations.load(std::memory_order_relaxed);
}

std::ptrdiff_t MemoryAudit::outstandingAllocations() const
{
    const auto allocs = static_cast<std::ptrdiff_t>(m_totalAllocations.load(std::memory_order_relaxed));
    const auto frees = static_cast<std::ptrdiff_t>(m_totalDeallocations.load(std::memory_order_relaxed));
    return allocs - frees;
}

bool MemoryAudit::validateMemoryLimit() const
{
    return peakUsageBytes() <= MemoryLimitBytes;
}

bool MemoryAudit::validateNoLeaks() const
{
    return currentUsageBytes() == 0 && outstandingAllocations() == 0;
}

QString MemoryAudit::formatBytes(std::size_t bytes) const
{
    constexpr double kib = 1024.0;
    constexpr double mib = kib * 1024.0;
    if (bytes >= static_cast<std::size_t>(mib)) {
        return QString::number(static_cast<double>(bytes) / mib, 'f', 2) + QStringLiteral(" MiB");
    }
    if (bytes >= static_cast<std::size_t>(kib)) {
        return QString::number(static_cast<double>(bytes) / kib, 'f', 2) + QStringLiteral(" KiB");
    }
    return QString::number(bytes) + QStringLiteral(" B");
}

ScopedBuffer::ScopedBuffer(std::size_t size)
    : m_storage(size ? std::make_unique<char[]>(size) : nullptr)
    , m_size(size)
{
    if (m_size > 0) {
        MemoryAudit::instance().trackAllocation(m_size);
    }
}

ScopedBuffer::~ScopedBuffer()
{
    if (m_size > 0) {
        MemoryAudit::instance().trackDeallocation(m_size);
    }
}

std::size_t ScopedBuffer::size() const noexcept
{
    return m_size;
}

const char *ScopedBuffer::data() const noexcept
{
    return m_storage.get();
}

char *ScopedBuffer::data() noexcept
{
    return m_storage.get();
}

AllocationGuard::AllocationGuard(std::size_t bytes)
    : m_bytes(bytes)
{
    if (m_bytes > 0) {
        MemoryAudit::instance().trackAllocation(m_bytes);
    }
}

AllocationGuard::~AllocationGuard()
{
    if (m_bytes > 0) {
        MemoryAudit::instance().trackDeallocation(m_bytes);
    }
}
