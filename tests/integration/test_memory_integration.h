#ifndef TEST_MEMORY_INTEGRATION_H
#define TEST_MEMORY_INTEGRATION_H

#include <QObject>

class TestMemoryIntegration : public QObject
{
    Q_OBJECT

private slots:
    void mixedOperationsStayUnder50MiB();
    void bufferAllocationsAreNetZeroAfterWorkload();
    void concurrentScopedBuffersDoNotLeak();
};

#endif
