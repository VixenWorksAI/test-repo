#include "calculatorcontroller.h"
#include "arithmeticoperations.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include <cmath>

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

void CalculatorController::bindMultiply(QPushButton *multiplyButton)
{
    if (multiplyButton != nullptr) {
        connect(multiplyButton, &QPushButton::clicked,
                this, &CalculatorController::onMultiplyButtonClicked);
    }
}

void CalculatorController::bindDivide(QPushButton *divideButton)
{
    if (divideButton != nullptr) {
        connect(divideButton, &QPushButton::clicked,
                this, &CalculatorController::onDivideButtonClicked);
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
    emit displayUpdated(m_resultDisplay->text());
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
    emit displayUpdated(m_resultDisplay->text());
}

void CalculatorController::onMultiplyButtonClicked()
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

    const double product = arithmetic::multiplyNumbers(first, second);
    m_resultDisplay->setText(QString::number(product));
    clearError();
    emit displayUpdated(m_resultDisplay->text());
}

void CalculatorController::onDivideButtonClicked()
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

    const double quotient = arithmetic::divideNumbers(first, second);
    if (std::isnan(quotient)) {
        setError(QStringLiteral("Division by zero"));
        return;
    }
    m_resultDisplay->setText(QString::number(quotient));
    clearError();
    emit displayUpdated(m_resultDisplay->text());
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
    emit displayUpdated(m_resultDisplay != nullptr ? m_resultDisplay->text()
                                                   : QString());
}

void CalculatorController::clearError()
{
    if (m_statusLabel != nullptr) {
        m_statusLabel->setText(QString());
    }
}
