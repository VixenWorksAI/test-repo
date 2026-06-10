#include <QtTest/QtTest>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "calculatorcontroller.h"

class MultiplicationE2ETest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void fullSessionTwoPositives();
    void fullSessionTwoNegatives();
    void fullSessionZeroAndPositive();
    void fullSessionDecimalOperands();
    void fullSessionMultiplyByOne();
    void fullSessionLargeValues();
    void fullSessionNegationPath();
    void fullSessionResultPersistsInDisplay();
    void fullSessionResultMatchesStatus();

private:
    QApplication *app;
    MainWindow *window;
    CalculatorController *controller;
};

void MultiplicationE2ETest::initTestCase()
{
    int argc = 0;
    char **argv = nullptr;
    app = new QApplication(argc, argv);
}

void MultiplicationE2ETest::cleanupTestCase()
{
    delete app;
    app = nullptr;
}

void MultiplicationE2ETest::init()
{
    window = new MainWindow();
    window->show();
    controller = window->findChild<CalculatorController *>();
    QVERIFY(controller != nullptr);
}

void MultiplicationE2ETest::cleanup()
{
    delete window;
    window = nullptr;
    controller = nullptr;
}

void MultiplicationE2ETest::fullSessionTwoPositives()
{
    window->firstOperandInput()->setText(QStringLiteral("6"));
    window->secondOperandInput()->setText(QStringLiteral("7"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 42.0));
}

void MultiplicationE2ETest::fullSessionTwoNegatives()
{
    window->firstOperandInput()->setText(QStringLiteral("-4"));
    window->secondOperandInput()->setText(QStringLiteral("-5"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 20.0));
}

void MultiplicationE2ETest::fullSessionZeroAndPositive()
{
    window->firstOperandInput()->setText(QStringLiteral("0"));
    window->secondOperandInput()->setText(QStringLiteral("99.9"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 0.0));
}

void MultiplicationE2ETest::fullSessionDecimalOperands()
{
    window->firstOperandInput()->setText(QStringLiteral("2.5"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 10.0));
}

void MultiplicationE2ETest::fullSessionMultiplyByOne()
{
    window->firstOperandInput()->setText(QStringLiteral("77"));
    window->secondOperandInput()->setText(QStringLiteral("1"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 77.0));
}

void MultiplicationE2ETest::fullSessionLargeValues()
{
    window->firstOperandInput()->setText(QStringLiteral("1000"));
    window->secondOperandInput()->setText(QStringLiteral("1000"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 1000000.0));
}

void MultiplicationE2ETest::fullSessionNegationPath()
{
    window->firstOperandInput()->setText(QStringLiteral("-12.5"));
    window->secondOperandInput()->setText(QStringLiteral("2"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), -25.0));
}

void MultiplicationE2ETest::fullSessionResultPersistsInDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("9"));
    window->secondOperandInput()->setText(QStringLiteral("8"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QString firstRead = window->displayEdit()->text();
    QTest::qWait(50);
    QString secondRead = window->displayEdit()->text();

    QCOMPARE(firstRead, secondRead);
    QVERIFY(qFuzzyCompare(firstRead.toDouble(), 72.0));
}

void MultiplicationE2ETest::fullSessionResultMatchesStatus()
{
    window->firstOperandInput()->setText(QStringLiteral("3"));
    window->secondOperandInput()->setText(QStringLiteral("14"));

    QTest::mouseClick(window->buttonMultiply(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 42.0));

    QLabel *status = window->statusLabel();
    QVERIFY(status != nullptr);
}

QTEST_MAIN(MultiplicationE2ETest)
#include "MultiplicationE2ETest.moc"
