#ifndef TEST_MULTIPLICATION_UI_E2E_H
#define TEST_MULTIPLICATION_UI_E2E_H

#include <QObject>

class TestMultiplicationUiE2E : public QObject
{
    Q_OBJECT

public:
    explicit TestMultiplicationUiE2E(QObject *parent = nullptr);

private slots:
    void uiComponentsAreResponsiveToUserActions();
    void multiplyButtonVisualStateChangesWhenActive();
    void multiplyButtonRespondsToRepeatedClicks();
    void allOperatorButtonsAreResponsive();
    void inputFieldsAcceptValidNumbers();
    void inputFieldsRejectInvalidCharacters();

    void e2eMultiplicationProducesCorrectProduct();
    void e2eMultiplicationWithNegativeNumbersProducesCorrectProduct();
    void e2eMultiplicationWithLargeNumbersSaturates();
    void e2eMultiplicationWithZeroProducesZero();

    void e2eTypingThenClickingMultiplyUpdatesDisplay();
    void e2eInvalidInputSurfacesErrorInStatusLabel();
};

#endif
