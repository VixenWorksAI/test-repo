#ifndef CALCULATOR_MEMORY_H
#define CALCULATOR_MEMORY_H

#include <QString>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>

class MemoryAudit
{
public:
    static constexpr std::size_t MemoryLimitBytes = 50u * 1024u * 1024u;

    static MemoryAudit &instance();

    void trackAllocation(std::size_t bytes);
    void trackDeallocation(std::size_t bytes);
    void resetTracking();

    std::size_t currentUsageBytes() const;
    std::size_t peakUsageBytes() const;
    std::uint64_t totalAllocations() const;
    std::uint64_t totalDeallocations() const;
    std::ptrdiff_t outstandingAllocations() const;

    bool validateMemoryLimit() const;
    bool validateNoLeaks() const;

    QString formatBytes(std::size_t bytes) const;

private:
    MemoryAudit() = default;

    std::atomic<std::size_t> m_currentBytes {0};
    std::atomic<std::size_t> m_peakBytes {0};
    std::atomic<std::uint64_t> m_totalAllocations {0};
    std::atomic<std::uint64_t> m_totalDeallocations {0};
};

class ScopedBuffer
{
public:
    explicit ScopedBuffer(std::size_t size);
    ~ScopedBuffer();

    ScopedBuffer(const ScopedBuffer &) = delete;
    ScopedBuffer &operator=(const ScopedBuffer &) = delete;
    ScopedBuffer(ScopedBuffer &&) = delete;
    ScopedBuffer &operator=(ScopedBuffer &&) = delete;

    std::size_t size() const noexcept;
    const char *data() const noexcept;
    char *data() noexcept;

private:
    std::unique_ptr<char[]> m_storage;
    std::size_t m_size;
};

class AllocationGuard
{
public:
    explicit AllocationGuard(std::size_t bytes);
    ~AllocationGuard();

    AllocationGuard(const AllocationGuard &) = delete;
    AllocationGuard &operator=(const AllocationGuard &) = delete;
    AllocationGuard(AllocationGuard &&) = delete;
    AllocationGuard &operator=(AllocationGuard &&) = delete;

private:
    std::size_t m_bytes;
};

#endif
