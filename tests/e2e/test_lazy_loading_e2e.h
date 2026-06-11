#ifndef TEST_LAZY_LOADING_E2E_H
#define TEST_LAZY_LOADING_E2E_H

#include <QObject>

class TestLazyLoadingE2E : public QObject
{
    Q_OBJECT

private slots:
    void startupToFullUiReadinessUnderOneSecond();
};

#endif
