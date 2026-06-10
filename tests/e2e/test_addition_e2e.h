#ifndef TEST_ADDITION_E2E_H
#define TEST_ADDITION_E2E_H

#include <QObject>

class TestAdditionE2E : public QObject
{
    Q_OBJECT

private slots:
    void userAddsTwoPositiveIntegersEndToEnd();
    void userAddsNegativeNumbersEndToEnd();
    void userAddsMixedSignsEndToEnd();
    void userAddsZeroEndToEnd();
    void userEntersInvalidTextAndReceivesError();
    void userRecoversFromInvalidEntryAndComputesAgain();
};

#endif
