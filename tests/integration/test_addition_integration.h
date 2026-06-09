#ifndef TEST_ADDITION_INTEGRATION_H
#define TEST_ADDITION_INTEGRATION_H

#include <QObject>

class TestAdditionIntegration : public QObject
{
    Q_OBJECT

private slots:
    void additionResultIsDisplayedInMainWindow();
    void additionWithNegativeOperandsIsDisplayedInMainWindow();
    void additionOverflowClampIsDisplayedInMainWindow();
};

#endif
