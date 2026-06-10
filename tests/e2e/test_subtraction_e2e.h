#ifndef TEST_SUBTRACTION_E2E_H
#define TEST_SUBTRACTION_E2E_H

#include <QObject>

class TestSubtractionE2E : public QObject
{
    Q_OBJECT

private slots:
    void userSubtractsTwoPositiveIntegersEndToEnd();
    void userSubtractsResultingInNegativeEndToEnd();
    void userSubtractsWithZeroEndToEnd();
    void userSubtractsFractionalValuesEndToEnd();
    void userEntersInvalidSubtractionTextAndReceivesError();
    void userRecoversFromInvalidSubtractionEntryAndComputesAgain();
};

#endif
