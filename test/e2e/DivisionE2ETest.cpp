#include <QtTest/QtTest>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "calculatorcontroller.h"

class DivisionE2ETest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void fullSessionTwoPositives();
    void fullSessionTwoNegatives();
    void fullSessionMixedSigns();
    void fullSessionZeroNumerator();
    void fullSessionDecimalOperands();
    void fullSessionDivideByOne();
    void fullSessionOneDividedByValue();
    void fullSessionDivideByZeroShowsError();
    void fullSessionDecimalDividedByZeroShowsError();
    void fullSessionLargeValues();
    void fullSessionFractionalOutput();
    void fullSessionNegationPath();
    void fullSessionResultPersistsInDisplay();
    void fullSessionResultMatchesStatus();
    void fullSessionEmitsDisplayChangedSignal();

private:
    QApplication *app;
    MainWindow *window;
    CalculatorController *controller;
};

void DivisionE2ETest::initTestCase()
{
    int argc = 0;
    char **argv = nullptr;
    app = new QApplication(argc, argv);
}

void DivisionE2ETest::cleanupTestCase()
{
    delete app;
    app = nullptr;
}

void DivisionE2ETest::init()
{
    window = new MainWindow();
    window->show();
    controller = window->findChild<CalculatorController *>();
    QVERIFY(controller != nullptr);
    controller->bindDivide(window->buttonDivide());
}

void DivisionE2ETest::cleanup()
{
    delete window;
    window = nullptr;
    controller = nullptr;
}

void DivisionE2ETest::fullSessionTwoPositives()
{
    window->firstOperandInput()->setText(QStringLiteral("20"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 5.0));
}

void DivisionE2ETest::fullSessionTwoNegatives()
{
    window->firstOperandInput()->setText(QStringLiteral("-12"));
    window->secondOperandInput()->setText(QStringLiteral("-3"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 4.0));
}

void DivisionE2ETest::fullSessionMixedSigns()
{
    window->firstOperandInput()->setText(QStringLiteral("15"));
    window->secondOperandInput()->setText(QStringLiteral("-5"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), -3.0));
}

void DivisionE2ETest::fullSessionZeroNumerator()
{
    window->firstOperandInput()->setText(QStringLiteral("0"));
    window->secondOperandInput()->setText(QStringLiteral("1234.5"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 0.0));
}

void DivisionE2ETest::fullSessionDecimalOperands()
{
    window->firstOperandInput()->setText(QStringLiteral("0.5"));
    window->secondOperandInput()->setText(QStringLiteral("0.25"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 2.0));
}

void DivisionE2ETest::fullSessionDivideByOne()
{
    window->firstOperandInput()->setText(QStringLiteral("123"));
    window->secondOperandInput()->setText(QStringLiteral("1"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 123.0));
}

void DivisionE2ETest::fullSessionOneDividedByValue()
{
    window->firstOperandInput()->setText(QStringLiteral("1"));
    window->secondOperandInput()->setText(QStringLiteral("4"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 0.25));
}

void DivisionE2ETest::fullSessionDivideByZeroShowsError()
{
    window->firstOperandInput()->setText(QStringLiteral("5"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

void DivisionE2ETest::fullSessionDecimalDividedByZeroShowsError()
{
    window->firstOperandInput()->setText(QStringLiteral("3.14"));
    window->secondOperandInput()->setText(QStringLiteral("0"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(window->displayEdit()->text().isEmpty());
    QVERIFY(window->statusLabel() != nullptr);
    QVERIFY(!window->statusLabel()->text().isEmpty());
}

void DivisionE2ETest::fullSessionLargeValues()
{
    window->firstOperandInput()->setText(QStringLiteral("1000000"));
    window->secondOperandInput()->setText(QStringLiteral("1000"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 1000.0));
}

void DivisionE2ETest::fullSessionFractionalOutput()
{
    window->firstOperandInput()->setText(QStringLiteral("22"));
    window->secondOperandInput()->setText(QStringLiteral("7"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qAbs(window->displayEdit()->text().toDouble() - 22.0 / 7.0) < 1.0e-3);
}

void DivisionE2ETest::fullSessionNegationPath()
{
    window->firstOperandInput()->setText(QStringLiteral("-12.5"));
    window->secondOperandInput()->setText(QStringLiteral("2"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), -6.25));
}

void DivisionE2ETest::fullSessionResultPersistsInDisplay()
{
    window->firstOperandInput()->setText(QStringLiteral("9"));
    window->secondOperandInput()->setText(QStringLiteral("3"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QString firstRead = window->displayEdit()->text();
    QTest::qWait(50);
    QString secondRead = window->displayEdit()->text();

    QCOMPARE(firstRead, secondRead);
    QVERIFY(qFuzzyCompare(firstRead.toDouble(), 3.0));
}

void DivisionE2ETest::fullSessionResultMatchesStatus()
{
    window->firstOperandInput()->setText(QStringLiteral("14"));
    window->secondOperandInput()->setText(QStringLiteral("2"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 7.0));

    QLabel *status = window->statusLabel();
    QVERIFY(status != nullptr);
}

void DivisionE2ETest::fullSessionEmitsDisplayChangedSignal()
{
    window->firstOperandInput()->setText(QStringLiteral("8"));
    window->secondOperandInput()->setText(QStringLiteral("2"));

    QTest::mouseClick(window->buttonDivide(), Qt::LeftButton);

    QVERIFY(qFuzzyCompare(window->displayEdit()->text().toDouble(), 4.0));
}

QTEST_MAIN(DivisionE2ETest)
#include "DivisionE2ETest.moc"
