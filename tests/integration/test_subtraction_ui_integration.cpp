#include "test_subtraction_ui_integration.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QtTest>

void TestSubtractionUiIntegration::subtractButtonEmitsActiveStateAcrossFocusChanges()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonSubtract();
    QSignalSpy activeSpy(&window, &MainWindow::subtractButtonActiveChanged);

    button->setChecked(true);
    QCOMPARE(activeSpy.count(), 1);
    QVERIFY(activeSpy.takeFirst().at(0).toBool());

    window.firstOperandInput()->setFocus();
    button->setChecked(false);
    QCOMPARE(activeSpy.count(), 1);
    QVERIFY(!activeSpy.takeFirst().at(0).toBool());
}

void TestSubtractionUiIntegration::inputValidationRejectsNonNumericDuringInput()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QLineEdit *input = window.firstOperandInput();
    QDoubleValidator *validator = const_cast<QDoubleValidator *>(qobject_cast<const QDoubleValidator *>(input->validator()));
    QVERIFY(validator != nullptr);

    int pos = 0;
    QString mixed = QStringLiteral("12a3");
    QVERIFY(validator->validate(mixed, pos) != QValidator::Acceptable);
    QString special = QStringLiteral("$5");
    QVERIFY(validator->validate(special, pos) != QValidator::Acceptable);
    QString numeric = QStringLiteral("125.5");
    QVERIFY(validator->validate(numeric, pos) == QValidator::Acceptable);
}

void TestSubtractionUiIntegration::subtractButtonActiveStateClearsOnSecondClick()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QPushButton *button = window.buttonSubtract();
    QSignalSpy activeSpy(&window, &MainWindow::subtractButtonActiveChanged);

    button->click();
    QVERIFY(window.isSubtractButtonActive());

    button->click();
    QVERIFY(!window.isSubtractButtonActive());
    QCOMPARE(activeSpy.count(), 2);
    QVERIFY(activeSpy.at(0).at(0).toBool());
    QVERIFY(!activeSpy.at(1).at(0).toBool());
}
