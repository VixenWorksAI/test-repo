#ifndef TEST_SUBTRACTION_UI_INTEGRATION_H
#define TEST_SUBTRACTION_UI_INTEGRATION_H

#include <QObject>

class TestSubtractionUiIntegration : public QObject
{
    Q_OBJECT

private slots:
    void subtractButtonEmitsActiveStateAcrossFocusChanges();
    void inputValidationRejectsNonNumericDuringInput();
    void subtractButtonActiveStateClearsOnSecondClick();
};

#endif
