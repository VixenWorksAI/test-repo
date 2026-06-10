#include <QtTest>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>

#include "calculatorcontroller.h"

namespace {

class SignalCapture : public QObject
{
    Q_OBJECT

public:
    explicit SignalCapture(CalculatorController *controller, QObject *parent = nullptr)
        : QObject(parent)
    {
        connect(controller,
                &CalculatorController::displayUpdated,
                this,
                &SignalCapture::onDisplayUpdated);
    }

    QStringList received() const { return m_received; }
    QString lastReceived() const
    {
        return m_received.isEmpty() ? QString() : m_received.last();
    }

private slots:
    void onDisplayUpdated(const QString &text)
    {
        m_received.append(text);
    }

private:
    QStringList m_received;
};

CalculatorController *makeController(QObject *parent,
                                    QLineEdit *&firstOut,
                                    QLineEdit *&secondOut,
                                    QLineEdit *&displayOut,
                                    QLabel *&statusOut)
{
    firstOut = new QLineEdit(parent);
    firstOut->setText(QStringLiteral("0"));
    secondOut = new QLineEdit(parent);
    secondOut->setText(QStringLiteral("0"));
    displayOut = new QLineEdit(parent);
    statusOut = new QLabel(parent);

    return new CalculatorController(firstOut, secondOut, displayOut, statusOut, parent);
}

}

class TestCalculationLogicRealtimeUnit : public QObject
{
    Q_OBJECT

private slots:
    void additionEmitsDisplayUpdatedWithSum();
    void subtractionEmitsDisplayUpdatedWithDifference();
    void multiplicationEmitsDisplayUpdatedWithProduct();
    void divisionEmitsDisplayUpdatedWithQuotient();
    void divisionByZeroEmitsDisplayUpdatedWithEmptyString();
    void setErrorEmitsDisplayUpdatedWithEmptyString();
};

void TestCalculationLogicRealtimeUnit::additionEmitsDisplayUpdatedWithSum()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("2"));
    second->setText(QStringLiteral("3"));
    controller->onAddButtonClicked();

    QCOMPARE(capture.received().size(), 1);
    QCOMPARE(capture.lastReceived(), QStringLiteral("5"));
    QCOMPARE(display->text(), QStringLiteral("5"));
}

void TestCalculationLogicRealtimeUnit::subtractionEmitsDisplayUpdatedWithDifference()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("9"));
    second->setText(QStringLiteral("4"));
    controller->onSubtractButtonClicked();

    QCOMPARE(capture.received().size(), 1);
    QCOMPARE(capture.lastReceived(), QStringLiteral("5"));
    QCOMPARE(display->text(), QStringLiteral("5"));
}

void TestCalculationLogicRealtimeUnit::multiplicationEmitsDisplayUpdatedWithProduct()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("6"));
    second->setText(QStringLiteral("7"));
    controller->onMultiplyButtonClicked();

    QCOMPARE(capture.received().size(), 1);
    QCOMPARE(capture.lastReceived(), QStringLiteral("42"));
    QCOMPARE(display->text(), QStringLiteral("42"));
}

void TestCalculationLogicRealtimeUnit::divisionEmitsDisplayUpdatedWithQuotient()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("8"));
    second->setText(QStringLiteral("2"));
    controller->onDivideButtonClicked();

    QCOMPARE(capture.received().size(), 1);
    QCOMPARE(capture.lastReceived(), QStringLiteral("4"));
    QCOMPARE(display->text(), QStringLiteral("4"));
}

void TestCalculationLogicRealtimeUnit::divisionByZeroEmitsDisplayUpdatedWithEmptyString()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("5"));
    second->setText(QStringLiteral("0"));
    controller->onDivideButtonClicked();

    QCOMPARE(capture.received().size(), 1);
    QCOMPARE(capture.lastReceived(), QString());
    QCOMPARE(display->text(), QString());
}

void TestCalculationLogicRealtimeUnit::setErrorEmitsDisplayUpdatedWithEmptyString()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("1"));
    second->setText(QStringLiteral("2"));
    controller->onAddButtonClicked();
    QCOMPARE(capture.lastReceived(), QStringLiteral("3"));

    first->setText(QString());
    second->setText(QStringLiteral("0"));
    controller->onDivideButtonClicked();
    QCOMPARE(capture.lastReceived(), QString());
    QCOMPARE(capture.received().size(), 2);
    QCOMPARE(display->text(), QString());
}

class TestCalculationLogicRealtimeIntegration : public QObject
{
    Q_OBJECT

private slots:
    void signalSlotWiringUpdatesDisplayValue();
    void consecutiveOperationsEmitOneSignalPerOperation();
};

void TestCalculationLogicRealtimeIntegration::signalSlotWiringUpdatesDisplayValue()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);

    QObject slotTarget;
    int callCount = 0;
    QString lastText;
    QObject::connect(controller,
                     &CalculatorController::displayUpdated,
                     &slotTarget,
                     [&callCount, &lastText](const QString &text) {
                         ++callCount;
                         lastText = text;
                     });

    first->setText(QStringLiteral("10"));
    second->setText(QStringLiteral("4"));
    controller->onSubtractButtonClicked();

    QCOMPARE(callCount, 1);
    QCOMPARE(lastText, QStringLiteral("6"));
}

void TestCalculationLogicRealtimeIntegration::consecutiveOperationsEmitOneSignalPerOperation()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    first->setText(QStringLiteral("1"));
    second->setText(QStringLiteral("2"));
    controller->onAddButtonClicked();

    first->setText(display->text());
    second->setText(QStringLiteral("3"));
    controller->onMultiplyButtonClicked();

    first->setText(display->text());
    second->setText(QStringLiteral("2"));
    controller->onSubtractButtonClicked();

    const QStringList expected = {
        QStringLiteral("3"),
        QStringLiteral("9"),
        QStringLiteral("7"),
    };
    QCOMPARE(capture.received(), expected);
    QCOMPARE(display->text(), QStringLiteral("7"));
}

class TestCalculationLogicRealtimeE2E : public QObject
{
    Q_OBJECT

private slots:
    void fullInputOutputProcessingReflectsCurrentState();
};

void TestCalculationLogicRealtimeE2E::fullInputOutputProcessingReflectsCurrentState()
{
    QObject parent;
    QLineEdit *first = nullptr;
    QLineEdit *second = nullptr;
    QLineEdit *display = nullptr;
    QLabel *status = nullptr;
    auto *controller = makeController(&parent, first, second, display, status);
    SignalCapture capture(controller);

    struct Step {
        const char *first;
        const char *second;
        void (CalculatorController::*op)();
        const char *expected;
    };

    const Step steps[] = {
        {"12", "3", &CalculatorController::onAddButtonClicked,      "15"},
        {"15", "5", &CalculatorController::onSubtractButtonClicked, "10"},
        {"10", "2", &CalculatorController::onMultiplyButtonClicked, "20"},
        {"20", "4", &CalculatorController::onDivideButtonClicked,   "5"},
    };

    for (const Step &step : steps) {
        first->setText(QString::fromLatin1(step.first));
        second->setText(QString::fromLatin1(step.second));
        (controller->*(step.op))();
    }

    const QStringList expected = {
        QStringLiteral("15"),
        QStringLiteral("10"),
        QStringLiteral("20"),
        QStringLiteral("5"),
    };
    QCOMPARE(capture.received(), expected);
    QCOMPARE(display->text(), QStringLiteral("5"));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;
    status |= QTest::qExec(&TestCalculationLogicRealtimeUnit(), argc, argv);
    status |= QTest::qExec(&TestCalculationLogicRealtimeIntegration(), argc, argv);
    status |= QTest::qExec(&TestCalculationLogicRealtimeE2E(), argc, argv);
    return status;
}

#include "test_calculation_logic_realtime.moc"
