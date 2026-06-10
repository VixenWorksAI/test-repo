#ifndef TEST_SUBTRACTION_UI_E2E_H
#define TEST_SUBTRACTION_UI_E2E_H

#include <QObject>

class TestSubtractionUiE2e : public QObject
{
    Q_OBJECT

private slots:
    void userCanEnterTwoNumericOperands();
    void userTogglingSubtractButtonChangesActiveHighlight();
    void userCannotTypeAlphaCharactersInOperandFields();
};

#endif
