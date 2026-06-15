#ifndef TEST_LAZY_LOADING_UNIT_H
#define TEST_LAZY_LOADING_UNIT_H

#include <QObject>

class TestLazyLoadingUnit : public QObject
{
    Q_OBJECT

private slots:
    void essentialComponentsConstructedEagerly();
    void deferredInitializationRunsOnce();
    void deferredHookIdempotentUnderRepeatedCalls();
};

#endif
