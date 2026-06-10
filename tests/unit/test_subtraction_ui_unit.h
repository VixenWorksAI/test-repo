#ifndef TEST_SUBTRACTION_UI_UNIT_H
#define TEST_SUBTRACTION_UI_UNIT_H

#include <QObject>

class TestSubtractionUiUnit : public QObject
{
    Q_OBJECT

private slots:
    void subtractButtonIsLabeledWithMinusSign();
    void subtractButtonIsNotActiveByDefault();
    void firstOperandInputIsNumericOnly();
    void secondOperandInputIsNumericOnly();
    void subtractButtonActivatesOnClick();
    void subtractButtonDifferentiatesFromAddButton();
};

#endif
