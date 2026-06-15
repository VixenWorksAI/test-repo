#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>

class QLineEdit;
class QLabel;
class QPushButton;

class CalculatorController : public QObject
{
    Q_OBJECT

public:
    explicit CalculatorController(QLineEdit *firstOperand,
                                  QLineEdit *secondOperand,
                                  QLineEdit *resultDisplay,
                                  QLabel *statusLabel,
                                  QObject *parent = nullptr);

    void bind(QPushButton *addButton);
    void bindSubtract(QPushButton *subtractButton);
    void bindMultiply(QPushButton *multiplyButton);
    void bindDivide(QPushButton *divideButton);
    void bindDigit(QPushButton *digitButton, int digit);
    void bindEquals(QPushButton *equalsButton);
    void bindClear(QPushButton *clearButton);
    void discoverAndBindKeypad();

signals:
    void displayUpdated(const QString &text) const;

public slots:
    void onAddButtonClicked();
    void onSubtractButtonClicked();
    void onMultiplyButtonClicked();
    void onDivideButtonClicked();
    void handleDigitButton();
    void handleOperatorButton();
    void handleEquals();
    void handleClearButton();

private:
    void storeOperandA();
    void computeResult();
    void resetForNewCalculation();
    void refreshDisplay(const QString &text);
    void showStatus(const QString &message);
    void showError(const QString &message);
    void setError(const QString &message);
    void clearError();
    bool pendingDivisionByZero() const;
    char operatorSymbol(const QString &op) const;
    bool applyOperator(char op, double a, double b, double &out) const;
    bool parseOperand(const QString &raw, double &out) const;

    QLineEdit *m_firstOperand;
    QLineEdit *m_secondOperand;
    QLineEdit *m_resultDisplay;
    QLabel *m_statusLabel;

    QPushButton *m_digitButton;
    int m_digitValue;
    QPushButton *m_pendingOperatorButton;
    QPushButton *m_equalsButton;
    QPushButton *m_clearButton;
};

#endif
