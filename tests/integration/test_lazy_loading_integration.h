#ifndef TEST_LAZY_LOADING_INTEGRATION_H
#define TEST_LAZY_LOADING_INTEGRATION_H

#include <QObject>

class TestLazyLoadingIntegration : public QObject
{
    Q_OBJECT

private slots:
    void mainWindowShowsBeforeDeferredHookFires();
    void interactionSequenceBetweenMainWindowAndDeferredHook();
};

#endif
