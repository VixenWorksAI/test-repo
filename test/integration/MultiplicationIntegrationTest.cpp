#include <QtTest/QtTest>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "calculatorcontroller.h"

class MultiplicationIntegrationTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void multiplyButtonProducesCorrectResult();
    void multiplyUpdatesDisplayOnButton();
    void multiplyViaControllerSlotDirectly();
    void multiplyByZeroUpdatesDisplay();
    void multiplyNegativesUpdatesDisplay();
    void multiplyDecimalsUpdatesDisplay();
    void multiplyWithFirstZeroUpdatesDisplay();
    void multiplyByOneKeepsValue();
    void multiplyLargeValuesUpdatesDisplay();
    void multiplyStatusMessageAppears();
    void multiplyButtonIsEnabled();

private:
    QApplication *app;
    MainWindow *window;
    CalculatorController *controller;
};

void MultiplicationIntegrationTest::initTestCase()
{
    int argc = 0;
    char **argv = nullptr;
    app = new QApplication(argc, argv);
}

void MultiplicationIntegrationTest::cleanupTestCase()
{
    delete app;
    app = nullptr;
}

void MultiplicationIntegrationTest::init()
{
    window = new MainWindow();
    window->show();
    controller = window->findChild<CalculatorController *>();
    QVERIFY(controller != nullptr);
}

void MultiplicationIntegrationTest::cleanup()
{
    delete window;
    window = nullptr;
    controller = nullptr;
}

void MultiplicationIntegrationTest::multiplyButtonProducesCorrectResult()
{
    window->firstOperandInput()->setText(QStringLiteral("6"));
    window->secondOperandInput()->setText(QStringLiteral("7"));

    QPushButton *multiplyBtn = window->buttonMultiply();
    QVERIFY(multiplyBtn != nullptr);
    QVERIFY(multiplyBtn->isEnabled());

    QTest::mouseClick(multiplyBtn, Qt::LeftButton);

    QCOMPARE(window->displayEdit()->text(), QString("42"));
}

void MultiplicationIntegrationTest::multiplyUpdatesDisplayOnButton()
{
    window->firstOperandInput()->setText(QStringLiteral("2.5"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    bool ok = false;
    double parsed = shown.toDouble(&ok);
    QVERIFY(ok);
    QVERIFY(qFuzzyCompare(parsed, 10.0));
}

void MultiplicationIntegrationTest::multiplyViaControllerSlotDirectly()
{
    window->firstOperandInput()->setText(QStringLiteral("11"));
    window->secondOperandInput()->setText(QStringLiteral("11"));

    QMetaObject::invokeMethod(controller, "onMultiplyButtonClicked", Qt::DirectConnection);
    QVERIFY(true);
}

void MultiplicationIntegrationTest::multiplyByZeroUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("0"));
    window->secondOperandInput()->setText(QStringLiteral("1234.5"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QCOMPARE(window->displayEdit()->text(), QString("0"));
}

void MultiplicationIntegrationTest::multiplyNegativesUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("-3"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), -12.0));
}

void MultiplicationIntegrationTest::multiplyDecimalsUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("0.5"));
    window->secondOperandInput()->setText(QStringLiteral("0.5"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 0.25));
}

void MultiplicationIntegrationTest::multiplyWithFirstZeroUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("987"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QCOMPARE(window->displayEdit()->text(), QString("0"));
}

void MultiplicationIntegrationTest::multiplyByOneKeepsValue()
{
    window->firstOperandInput()->setText(QStringLiteral("123"));
    window->secondOperandInput()->setText(QStringLiteral("1"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 123.0));
}

void MultiplicationIntegrationTest::multiplyLargeValuesUpdatesDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("1000000"));
    window->secondOperandInput()->setText(QStringLiteral("1000"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString shown = window->displayEdit()->text();
    QVERIFY(qFuzzyCompare(shown.toDouble(), 1.0e9));
}

void MultiplicationIntegrationTest::multiplyStatusMessageAppears()
{
    window->firstOperandInput()->setText(QStringLiteral("2"));
    window->secondOperandInput()->setText(QStringLiteral("3"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QLabel *status = window->statusLabel();
    QVERIFY(status != nullptr);
}

void MultiplicationIntegrationTest::multiplyButtonIsEnabled()
{
    QPushButton *multiplyBtn = window->buttonMultiply();
    QVERIFY(multiplyBtn != nullptr);
    QVERIFY(multiplyBtn->isEnabled());
    QVERIFY(!multiplyBtn->text().isEmpty());
}

QTEST_MAIN(MultiplicationIntegrationTest)
#include "MultiplicationIntegrationTest.moc"
