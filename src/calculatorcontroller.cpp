#include "calculatorcontroller.h"
#include "arithmeticoperations.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

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
    , m_digitButton(nullptr)
    , m_digitValue(0)
    , m_pendingOperatorButton(nullptr)
    , m_equalsButton(nullptr)
    , m_clearButton(nullptr)
{
}

void CalculatorController::bind(QPushButton *addButton)
{
    if (addButton != nullptr) {
        m_pendingOperatorButton = addButton;
        connect(addButton, &QPushButton::clicked,
                this, &CalculatorController::handleOperatorButton);
    }
}

void CalculatorController::bindSubtract(QPushButton *subtractButton)
{
    if (subtractButton != nullptr) {
        m_pendingOperatorButton = subtractButton;
        connect(subtractButton, &QPushButton::clicked,
                this, &CalculatorController::handleOperatorButton);
    }
}

void CalculatorController::bindMultiply(QPushButton *multiplyButton)
{
    if (multiplyButton != nullptr) {
        m_pendingOperatorButton = multiplyButton;
        connect(multiplyButton, &QPushButton::clicked,
                this, &CalculatorController::handleOperatorButton);
    }
}

void CalculatorController::bindDivide(QPushButton *divideButton)
{
    if (divideButton != nullptr) {
        m_pendingOperatorButton = divideButton;
        connect(divideButton, &QPushButton::clicked,
                this, &CalculatorController::handleOperatorButton);
    }
}

void CalculatorController::bindDigit(QPushButton *digitButton, int digit)
{
    if (digitButton != nullptr) {
        m_digitButton = digitButton;
        m_digitValue = digit;
        connect(digitButton, &QPushButton::clicked,
                this, &CalculatorController::handleDigitButton);
    }
}

void CalculatorController::bindEquals(QPushButton *equalsButton)
{
    if (equalsButton != nullptr) {
        m_equalsButton = equalsButton;
        connect(equalsButton, &QPushButton::clicked,
                this, &CalculatorController::handleEquals);
    }
}

void CalculatorController::bindClear(QPushButton *clearButton)
{
    if (clearButton != nullptr) {
        m_clearButton = clearButton;
        connect(clearButton, &QPushButton::clicked,
                this, &CalculatorController::handleClearButton);
    }
}

void CalculatorController::discoverAndBindKeypad()
{
    QObject *parentObject = parent();
    if (parentObject == nullptr) {
        return;
    }
    auto *root = qobject_cast<QWidget *>(parentObject);
    if (root == nullptr) {
        return;
    }

    for (int digit = 0; digit <= 9; ++digit) {
        const QString name = QStringLiteral("button%1").arg(digit);
        if (auto *btn = root->findChild<QPushButton *>(name)) {
            m_digitButton = btn;
            m_digitValue = digit;
            connect(btn, &QPushButton::clicked,
                    this, &CalculatorController::handleDigitButton);
        }
    }

    if (auto *btn = root->findChild<QPushButton *>(QStringLiteral("buttonEquals"))) {
        m_equalsButton = btn;
        connect(btn, &QPushButton::clicked,
                this, &CalculatorController::handleEquals);
    }

    if (auto *btn = root->findChild<QPushButton *>(QStringLiteral("buttonClear"))) {
        m_clearButton = btn;
        connect(btn, &QPushButton::clicked,
                this, &CalculatorController::handleClearButton);
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

void CalculatorController::handleDigitButton()
{
    if (m_resultDisplay == nullptr) {
        return;
    }

    if (m_digitButton == nullptr) {
        showError(QStringLiteral("Digit button is not bound"));
        return;
    }

    const QString current = m_resultDisplay->text();
    QString updated = current;
    if (updated == QStringLiteral("0")) {
        updated = QString::number(m_digitValue);
    } else if (updated == QStringLiteral("Error: Division by zero")
               || updated.startsWith(QStringLiteral("Error"))) {
        updated = QString::number(m_digitValue);
    } else {
        updated.append(QString::number(m_digitValue));
    }
    refreshDisplay(updated);
    showStatus(QString());
}

void CalculatorController::handleOperatorButton()
{
    if (m_resultDisplay == nullptr) {
        return;
    }

    if (m_pendingOperatorButton == nullptr) {
        showError(QStringLiteral("Operator button is not bound"));
        return;
    }

    storeOperandA();
    const char op = operatorSymbol(m_pendingOperatorButton->text());
    showStatus(QStringLiteral("A=%1 %2").arg(m_firstOperand != nullptr
                                                ? m_firstOperand->text()
                                                : QStringLiteral("0"),
                                            QChar(op)));
    refreshDisplay(QString());
}

void CalculatorController::handleEquals()
{
    if (m_resultDisplay == nullptr || m_firstOperand == nullptr) {
        return;
    }

    computeResult();
}

void CalculatorController::handleClearButton()
{
    resetForNewCalculation();
    showStatus(QString());
}

void CalculatorController::storeOperandA()
{
    if (m_resultDisplay == nullptr || m_firstOperand == nullptr) {
        return;
    }
    const QString text = m_resultDisplay->text();
    if (!text.isEmpty() && !text.startsWith(QStringLiteral("Error"))) {
        m_firstOperand->setText(text);
    }
    if (m_secondOperand != nullptr) {
        m_secondOperand->clear();
    }
}

void CalculatorController::computeResult()
{
    if (m_pendingOperatorButton == nullptr) {
        showError(QStringLiteral("No operator selected"));
        return;
    }

    const char op = operatorSymbol(m_pendingOperatorButton->text());
    const QString secondText = m_resultDisplay->text();

    double first = 0.0;
    double second = 0.0;
    if (m_firstOperand == nullptr || !parseOperand(m_firstOperand->text(), first)) {
        showError(QStringLiteral("A is not a valid number"));
        return;
    }
    if (!parseOperand(secondText, second)) {
        showError(QStringLiteral("B is not a valid number"));
        return;
    }

    double result = 0.0;
    if (!applyOperator(op, first, second, result)) {
        showError(QStringLiteral("Error: Division by zero"));
        return;
    }

    refreshDisplay(QString::number(result));
    showStatus(QStringLiteral("A=%1 %2 B=%3 = %4")
                   .arg(QString::number(first))
                   .arg(QChar(op))
                   .arg(QString::number(second))
                   .arg(QString::number(result)));
    if (m_secondOperand != nullptr) {
        m_secondOperand->setText(secondText);
    }
    resetForNewCalculation();
}

void CalculatorController::resetForNewCalculation()
{
    if (m_firstOperand != nullptr) {
        m_firstOperand->clear();
    }
    if (m_secondOperand != nullptr) {
        m_secondOperand->clear();
    }
    m_pendingOperatorButton = nullptr;
    m_digitButton = nullptr;
    m_digitValue = 0;
    if (m_resultDisplay != nullptr) {
        m_resultDisplay->setText(QStringLiteral("0"));
    }
}

void CalculatorController::refreshDisplay(const QString &text)
{
    if (m_resultDisplay == nullptr) {
        return;
    }
    if (text.isEmpty()) {
        m_resultDisplay->setText(QStringLiteral("0"));
    } else {
        m_resultDisplay->setText(text);
    }
    emit displayUpdated(m_resultDisplay->text());
}

void CalculatorController::showStatus(const QString &message)
{
    if (m_statusLabel != nullptr) {
        m_statusLabel->setText(message);
    }
}

void CalculatorController::showError(const QString &message)
{
    refreshDisplay(message);
    if (m_statusLabel != nullptr) {
        m_statusLabel->setText(message);
    }
}

bool CalculatorController::pendingDivisionByZero() const
{
    if (m_pendingOperatorButton == nullptr) {
        return false;
    }
    const char op = operatorSymbol(m_pendingOperatorButton->text());
    if (op != '/') {
        return false;
    }
    if (m_resultDisplay == nullptr) {
        return false;
    }
    const QString text = m_resultDisplay->text().trimmed();
    return text == QStringLiteral("0") || text == QStringLiteral("0.0");
}

char CalculatorController::operatorSymbol(const QString &op) const
{
    const QString trimmed = op.trimmed();
    if (trimmed == QStringLiteral("+")) {
        return '+';
    }
    if (trimmed == QStringLiteral("-")) {
        return '-';
    }
    if (trimmed == QStringLiteral("\xC3\x97") || trimmed == QStringLiteral("*")) {
        return '*';
    }
    if (trimmed == QStringLiteral("\xC3\xB7") || trimmed == QStringLiteral("/")) {
        return '/';
    }
    return '+';
}

bool CalculatorController::applyOperator(char op, double a, double b, double &out) const
{
    if (op == '+') {
        out = arithmetic::addNumbers(a, b);
        return true;
    }
    if (op == '-') {
        out = arithmetic::subtractNumbers(a, b);
        return true;
    }
    if (op == '*') {
        out = arithmetic::multiplyNumbers(a, b);
        return true;
    }
    if (op == '/') {
        if (b == 0.0) {
            return false;
        }
        out = arithmetic::divideNumbers(a, b);
        return !std::isnan(out);
    }
    return false;
}
