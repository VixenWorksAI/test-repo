#include "test_subtraction_ui_e2e.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QtTest>

void TestSubtractionUiE2e::userCanEnterTwoNumericOperands()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.firstOperandInput()->setText(QStringLiteral("15"));
    window.secondOperandInput()->setText(QStringLiteral("6"));
    QCOMPARE(window.firstOperandInput()->text(), QStringLiteral("15"));
    QCOMPARE(window.secondOperandInput()->text(), QStringLiteral("6"));
}

void TestSubtractionUiE2e::userTogglingSubtractButtonChangesActiveHighlight()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonSubtract();
    QSignalSpy activeSpy(&window, &MainWindow::subtractButtonActiveChanged);

    QVERIFY(!button->isChecked());
    QVERIFY(button->styleSheet().contains(QStringLiteral("checked")));

    button->click();
    QVERIFY(button->isChecked());
    QVERIFY(window.isSubtractButtonActive());

    button->click();
    QVERIFY(!button->isChecked());
    QVERIFY(!window.isSubtractButtonActive());
    QCOMPARE(activeSpy.count(), 2);
}

void TestSubtractionUiE2e::userCannotTypeAlphaCharactersInOperandFields()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *first = window.firstOperandInput();
    QLineEdit *second = window.secondOperandInput();
    QVERIFY(first->validator() != nullptr);
    QVERIFY(second->validator() != nullptr);

    int pos = 0;
    QString alpha = QStringLiteral("hello");
    QVERIFY(first->validator()->validate(alpha, pos) != QValidator::Acceptable);
    QVERIFY(second->validator()->validate(alpha, pos) != QValidator::Acceptable);
}
