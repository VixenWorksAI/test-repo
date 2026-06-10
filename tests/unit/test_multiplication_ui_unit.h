#ifndef TEST_MULTIPLICATION_UI_UNIT_H
#define TEST_MULTIPLICATION_UI_UNIT_H

#include <QObject>

class TestMultiplicationUiUnit : public QObject
{
    Q_OBJECT

public:
    explicit TestMultiplicationUiUnit(QObject *parent = nullptr);

private slots:
    void multiplyButtonExists();
    void multiplyButtonDisplaysStarSymbol();
    void multiplyButtonIsCheckable();
    void multiplyButtonStartsInactive();
    void firstOperandInputExists();
    void secondOperandInputExists();
    void firstOperandInputHasNumericValidator();
    void secondOperandInputHasNumericValidator();
    void firstOperandInputRejectsAlpha();
    void secondOperandInputRejectsAlpha();
};

#endif
