#ifndef TEST_MEMORY_UNIT_H
#define TEST_MEMORY_UNIT_H

#include <QObject>

class TestMemoryUnit : public QObject
{
    Q_OBJECT

private slots:
    void allocationSymmetry();
    void scopedBufferReleasesOnDestruction();
    void allocationGuardReleasesOnDestruction();
    void resetTrackingClearsCounters();
    void outstandingCountTracksAsymmetry();
    void peakUsageReflectsHighWatermark();
    void formatBytesProducesHumanReadableStrings();
};

#endif
