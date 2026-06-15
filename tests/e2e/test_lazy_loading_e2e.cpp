#include "test_lazy_loading_e2e.h"

#include <QtTest>
#include <QApplication>
#include <QTime>
#include <QTimer>

#include "mainwindow.h"

void TestLazyLoadingE2E::startupToFullUiReadinessUnderOneSecond()
{
    const QTime start = QTime::currentTime();

    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window, 1000));

    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);
    QVERIFY(QTest::qWaitFor([&]() { return window.isDeferredInitialized(); }, 1000));

    const qint64 elapsedMs = start.msecsTo(QTime::currentTime());
    QVERIFY2(elapsedMs < 1000,
             qPrintable(QString("Startup exceeded 1s budget: %1 ms").arg(elapsedMs)));
}
