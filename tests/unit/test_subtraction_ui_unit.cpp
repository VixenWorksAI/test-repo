#include "test_subtraction_ui_unit.h"
#include "mainwindow.h"

#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>

void TestSubtractionUiUnit::subtractButtonIsLabeledWithMinusSign()
{
    MainWindow window;
    QCOMPARE(window.buttonSubtract()->text(), QStringLiteral("-"));
}

void TestSubtractionUiUnit::subtractButtonIsNotActiveByDefault()
{
    MainWindow window;
    QVERIFY(!window.isSubtractButtonActive());
    QVERIFY(!window.buttonSubtract()->isChecked());
}

void TestSubtractionUiUnit::firstOperandInputIsNumericOnly()
{
    MainWindow window;
    QLineEdit *input = window.firstOperandInput();
    QVERIFY(input != nullptr);
    QVERIFY(input->validator() != nullptr);
    QDoubleValidator *validator = const_cast<QDoubleValidator *>(qobject_cast<const QDoubleValidator *>(input->validator()));
    QVERIFY(validator != nullptr);

    int pos = 0;
    QString validNumber = QStringLiteral("12.34");
    QVERIFY(validator->validate(validNumber, pos) == QValidator::Acceptable);

    QString alphabetic = QStringLiteral("abc");
    QVERIFY(validator->validate(alphabetic, pos) != QValidator::Acceptable);
}

void TestSubtractionUiUnit::secondOperandInputIsNumericOnly()
{
    MainWindow window;
    QLineEdit *input = window.secondOperandInput();
    QVERIFY(input != nullptr);
    QVERIFY(input->validator() != nullptr);
    QDoubleValidator *validator = const_cast<QDoubleValidator *>(qobject_cast<const QDoubleValidator *>(input->validator()));
    QVERIFY(validator != nullptr);

    int pos = 0;
    QString validNumber = QStringLiteral("-7.5");
    QVERIFY(validator->validate(validNumber, pos) == QValidator::Acceptable);

    QString alphabetic = QStringLiteral("xyz");
    QVERIFY(validator->validate(alphabetic, pos) != QValidator::Acceptable);
}

void TestSubtractionUiUnit::subtractButtonActivatesOnClick()
{
    MainWindow window;
    QPushButton *button = window.buttonSubtract();
    QVERIFY(button->isCheckable());

    QSignalSpy activeSpy(&window, &MainWindow::subtractButtonActiveChanged);
    button->toggle();
    QCOMPARE(activeSpy.count(), 1);
    QCOMPARE(activeSpy.takeFirst().at(0).toBool(), true);
    QVERIFY(window.isSubtractButtonActive());

    button->toggle();
    QVERIFY(!window.isSubtractButtonActive());
}

void TestSubtractionUiUnit::subtractButtonDifferentiatesFromAddButton()
{
    MainWindow window;
    QVERIFY(window.buttonSubtract() != window.buttonAdd());
    QCOMPARE(window.buttonSubtract()->text(), QStringLiteral("-"));
    QCOMPARE(window.buttonAdd()->text(), QStringLiteral("+"));
    QVERIFY(window.buttonSubtract()->styleSheet() != window.buttonAdd()->styleSheet());
}

