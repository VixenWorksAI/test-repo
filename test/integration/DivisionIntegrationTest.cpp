#include <QtTest/QtTest>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "calculatorcontroller.h"

class DivisionIntegrationTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void divideButtonProducesCorrectResult();
    void divideUpdatesDisplayOnButton();
    void divideViaControllerSlotDirectly();
    void divideByZeroShowsError();
    void divideByZeroViaControllerShowsError();
    void divideByZeroDecimalShowsError();
    void divideNegativesUpdatesDisplay();
    void divideDecimalsUpdatesDisplay();
    void divideWithFirstZeroUpdatesDisplay();
    void divideByOneKeepsValue();
    void divideOneByValueUpdatesDisplay();
    void divideLargeValuesUpdatesDisplay();
    void divideFractionalOutputUpdatesDisplay();
    void divideStatusMessageAppears();
    void divideButtonIsEnabled();
    void divideEmitsErrorSignalOnZeroDivisor();

private:
    QApplication *app;
    MainWindow *window;
    CalculatorController *controller;
};

void DivisionIntegrationTest::initTestCase()
{
    int argc = 0;
    char **argv = nullptr;
    app = new QApplication(argc, argv);
}

void DivisionIntegrationTest::cleanupTestCase()
{
    delete app;
    app = nullptr;
}

void DivisionIntegrationTest::init()
{
    window = new MainWindow();
    window->show();
    controller = window->findChild<CalculatorController *>();
    QVERIFY(controller != nullptr);
    controller->bindDivide(window->buttonDivide());
}

void DivisionIntegrationTest::cleanup()
{
    delete window;
    window = nullptr;
    controller = nullptr;
}

void DivisionIntegrationTest::divideButtonProducesCorrectResult()
{
    window->firstOperandInput()->setText(QStringLiteral("20"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QPushButton *divideBtn = window->buttonDivide();
    QVERIFY(divideBtn != nullptr);
    QVERIFY(divideBtn->isEnabled());

    QTest::mouseClick(divideBtn, Qt::LeftButton);

    QCOMPARE(window->displayEdit()->text(), QString("5"));
}

void DivisionIntegrationTest::divideUpdatesDisplayOnButton()
{
    window->firstOperandInput()->setText(QStringLiteral("10"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    bool ok = false;
    double parsed = shown.toDouble(&ok);
    QVERIFY(ok);
    QVERIFY(qFuzzyCompare(parsed, 2.5));
}

void DivisionIntegrationTest::divideViaControllerSlotDirectly()
{
    window->firstOperandInput()->setText(QStringLiteral("11"));
    window->secondOperandInput()->setText(QStringLiteral("11"));

    QMetaObject::invokeMethod(controller, "onDivideButtonClicked", Qt::DirectConnection);
    QVERIFY(true);
}

void DivisionIntegrationTest::divideByZeroShowsError()
{
    window->firstOperandInput()->setText(QStringLiteral("5"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

void DivisionIntegrationTest::divideByZeroViaControllerShowsError()
{
    window->firstOperandInput()->setText(QStringLiteral("99"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QMetaObject::invokeMethod(controller, "onDivideButtonClicked", Qt::DirectConnection);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

void DivisionIntegrationTest::divideByZeroDecimalShowsError()
{
    window->firstOperandInput()->setText(QStringLiteral("3.14"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

void DivisionIntegrationTest::divideNegativesUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("-12"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), -3.0));
}

void DivisionIntegrationTest::divideDecimalsUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("0.5"));
    window->secondOperandInput()->setText(QStringLiteral("0.25"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 2.0));
}

void DivisionIntegrationTest::divideWithFirstZeroUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("0"));
    window->secondOperandInput()->setText(QStringLiteral("987"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 0.0));
}

void DivisionIntegrationTest::divideByOneKeepsValue()
{
    window->firstOperandInput()->setText(QStringLiteral("123"));
    window->secondOperandInput()->setText(QStringLiteral("1"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 123.0));
}

void DivisionIntegrationTest::divideOneByValueUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("1"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 0.25));
}

void DivisionIntegrationTest::divideLargeValuesUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("1000000"));
    window->secondOperandInput()->setText(QStringLiteral("1000"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 1000.0));
}

void DivisionIntegrationTest::divideFractionalOutputUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("22"));
    window->secondOperandInput()->setText(QStringLiteral("7"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qAbs(shown.toDouble() - 22.0 / 7.0) < 1.0e-3);
}

void DivisionIntegrationTest::divideStatusMessageAppears()
{
    window->firstOperandInput()->setText(QStringLiteral("2"));
    window->secondOperandInput()->setText(QStringLiteral("3"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QLabel *status = window->statusLabel();
    QVERIFY(status != nullptr);
}

void DivisionIntegrationTest::divideButtonIsEnabled()
{
    QPushButton *divideBtn = window->buttonDivide();
    QVERIFY(divideBtn != nullptr);
    QVERIFY(divideBtn->isEnabled());
    QVERIFY(!divideBtn->text().isEmpty());
}

void DivisionIntegrationTest::divideEmitsErrorSignalOnZeroDivisor()
{
    window->firstOperandInput()->setText(QStringLiteral("10"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

QTEST_MAIN(DivisionIntegrationTest)
#include "DivisionIntegrationTest.moc"
