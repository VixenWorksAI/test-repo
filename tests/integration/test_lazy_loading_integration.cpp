#include "test_lazy_loading_integration.h"

#include <QtTest>
#include <QApplication>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"

void TestLazyLoadingIntegration::mainWindowShowsBeforeDeferredHookFires()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window, 1000));

    QVERIFY(window.displayEdit()->isVisible());
    QVERIFY(window.buttonAdd()->isVisible());
    QVERIFY(!window.isDeferredInitialized());

    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);
    QVERIFY(QTest::qWaitFor([&]() { return window.isDeferredInitialized(); }, 1000));
}

void TestLazyLoadingIntegration::interactionSequenceBetweenMainWindowAndDeferredHook()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window, 1000));

    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);
    QVERIFY(QTest::qWaitFor([&]() { return window.isDeferredInitialized(); }, 1000));

    QVERIFY(window.displayEdit()->isVisible());
    QVERIFY(window.buttonAdd()->isVisible());
    QVERIFY(window.isDeferredInitialized());
}
