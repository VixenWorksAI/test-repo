#ifndef TEST_MULTIPLICATION_UI_INTEGRATION_H
#define TEST_MULTIPLICATION_UI_INTEGRATION_H

#include <QObject>

class TestMultiplicationUiIntegration : public QObject
{
    Q_OBJECT

public:
    explicit TestMultiplicationUiIntegration(QObject *parent = nullptr);

private slots:
    void multiplyButtonClicksToggleActiveState();
    void multiplyButtonClickChangesButtonToChecked();
    void multiplyButtonIsClickableWithKeyboard();
    void multiplyButtonReceivesFocusAndClick();
    void firstAndSecondInputsAreIndependent();
    void multiplyButtonLabelIsMultiplicationGlyph();
    void multiplyButtonRespondsToMousePressAndRelease();

    void multiplicationLogicProducesProductFromUiInputs();
    void multiplicationLogicHandlesNegativeNumbersFromUiInputs();
    void multiplicationLogicHandlesOverflowFromUiInputs();
    void multiplicationLogicHandlesZeroFromUiInputs();
};

#endif
