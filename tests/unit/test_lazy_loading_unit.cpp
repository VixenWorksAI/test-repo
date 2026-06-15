#include "test_lazy_loading_unit.h"

#include <QtTest>
#include <QApplication>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"

void TestLazyLoadingUnit::essentialComponentsConstructedEagerly()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QVERIFY(window.displayEdit() != nullptr);
    QVERIFY(window.buttonAdd() != nullptr);
    QVERIFY(window.buttonSubtract() != nullptr);
    QVERIFY(window.buttonMultiply() != nullptr);
    QVERIFY(window.buttonDivide() != nullptr);
    QVERIFY(window.firstOperandInput() != nullptr);
    QVERIFY(window.secondOperandInput() != nullptr);
    QVERIFY(window.statusLabel() != nullptr);
    QVERIFY(!window.isDeferredInitialized());
}

void TestLazyLoadingUnit::deferredInitializationRunsOnce()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;

    QVERIFY(!window.isDeferredInitialized());

    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);
    QVERIFY(QTest::qWaitFor([&]() { return window.isDeferredInitialized(); }, 1000));

    QVERIFY(window.isDeferredInitialized());
}

void TestLazyLoadingUnit::deferredHookIdempotentUnderRepeatedCalls()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);
    QVERIFY(QTest::qWaitFor([&]() { return window.isDeferredInitialized(); }, 1000));

    window.deferredInitialization();
    QVERIFY(window.isDeferredInitialized());
}
