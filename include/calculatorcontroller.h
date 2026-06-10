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

signals:
    void displayUpdated(const QString &text) const;

public slots:
    void onAddButtonClicked();
    void onSubtractButtonClicked();
    void onMultiplyButtonClicked();
    void onDivideButtonClicked();

private:
    bool parseOperand(const QString &raw, double &out) const;
    void setError(const QString &message);
    void clearError();

    QLineEdit *m_firstOperand;
    QLineEdit *m_secondOperand;
    QLineEdit *m_resultDisplay;
    QLabel *m_statusLabel;
};

#endif
