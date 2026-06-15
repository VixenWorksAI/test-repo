#ifndef TEST_MEMORY_E2E_H
#define TEST_MEMORY_E2E_H

#include <QObject>

class TestMemoryE2E : public QObject
{
    Q_OBJECT

private slots:
    void longRunningStabilityHoldsBelowLimit();
    void longRunningStabilityHasNoNetLeakGrowth();
};

#endif
