#include "calculatorcontroller.h"
#include "arithmeticoperations.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

CalculatorController::CalculatorController(QLineEdit *firstOperand,
                                           QLineEdit *secondOperand,
                                           QLineEdit *resultDisplay,
                                           QLabel *statusLabel,
                                           QObject *parent)
    : QObject(parent)
    , m_firstOperand(firstOperand)
    , m_secondOperand(secondOperand)
    , m_resultDisplay(resultDisplay)
    , m_statusLabel(statusLabel)
{
}

void CalculatorController::bind(QPushButton *addButton)
{
    if (addButton != nullptr) {
        connect(addButton, &QPushButton::clicked,
                this, &CalculatorController::onAddButtonClicked);
    }
}

void CalculatorController::bindSubtract(QPushButton *subtractButton)
{
    if (subtractButton != nullptr) {
        connect(subtractButton, &QPushButton::clicked,
                this, &CalculatorController::onSubtractButtonClicked);
    }
}

void CalculatorController::onAddButtonClicked()
{
    if (m_firstOperand == nullptr || m_secondOperand == nullptr
            || m_resultDisplay == nullptr) {
        return;
    }

    double first = 0.0;
    double second = 0.0;
    if (!parseOperand(m_firstOperand->text(), first)) {
        setError(QStringLiteral("First operand is not a valid number"));
        return;
    }
    if (!parseOperand(m_secondOperand->text(), second)) {
        setError(QStringLiteral("Second operand is not a valid number"));
        return;
    }

    const double sum = arithmetic::addNumbers(first, second);
    m_resultDisplay->setText(QString::number(sum));
    clearError();
}

void CalculatorController::onSubtractButtonClicked()
{
    if (m_firstOperand == nullptr || m_secondOperand == nullptr
            || m_resultDisplay == nullptr) {
        return;
    }

    double first = 0.0;
    double second = 0.0;
    if (!parseOperand(m_firstOperand->text(), first)) {
        setError(QStringLiteral("First operand is not a valid number"));
        return;
    }
    if (!parseOperand(m_secondOperand->text(), second)) {
        setError(QStringLiteral("Second operand is not a valid number"));
        return;
    }

    const double difference = arithmetic::subtractNumbers(first, second);
    m_resultDisplay->setText(QString::number(difference));
    clearError();
}

bool CalculatorController::parseOperand(const QString &raw, double &out) const
{
    if (raw.trimmed().isEmpty()) {
        return false;
    }
    bool ok = false;
    const double value = raw.toDouble(&ok);
    if (!ok) {
        return false;
    }
    out = value;
    return true;
}

void CalculatorController::setError(const QString &message)
{
    if (m_resultDisplay != nullptr) {
        m_resultDisplay->setText(QString());
    }
    if (m_statusLabel != nullptr) {
        m_statusLabel->setText(message);
    }
}

void CalculatorController::clearError()
{
    if (m_statusLabel != nullptr) {
        m_statusLabel->setText(QString());
    }
}
