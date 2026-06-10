#include <QtTest>
#include <QApplication>
#include <QPushButton>
#include <QVector>
#include <QSize>

#include "mainwindow.h"
#include "test_placeholder_responsiveness_e2e.h"

void TestPlaceholderResponsivenessE2E::resizeAndProcess(MainWindow &window,
                                                       int width,
                                                       int height)
{
    window.resize(width, height);
    QResizeEvent event(window.size(), window.size());
    QApplication::sendEvent(&window, &event);
    QApplication::processEvents();
}

TestPlaceholderResponsivenessE2E::Snapshot
TestPlaceholderResponsivenessE2E::captureSnapshot(MainWindow &window, int width, int height)
{
    resizeAndProcess(window, width, height);
    QApplication::processEvents();

    Snapshot snapshot;
    snapshot.windowSize = window.size();

    const QList<QPushButton *> buttons = window.findChildren<QPushButton *>();
    QVector<QRect> rects;
    rects.reserve(buttons.size());
    for (QPushButton *button : buttons) {
        rects.append(QRect(button->mapTo(&window, QPoint(0, 0)), button->size()));
    }
    snapshot.buttonRects = rects;
    return snapshot;
}

void TestPlaceholderResponsivenessE2E::placeholdersRemainConsistentAcrossResolutions()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QApplication::processEvents();

    const Snapshot small = captureSnapshot(window, 360, 480);
    const Snapshot medium = captureSnapshot(window, 720, 720);
    const Snapshot large = captureSnapshot(window, 1280, 960);

    QCOMPARE(small.buttonRects.size(), medium.buttonRects.size());
    QCOMPARE(medium.buttonRects.size(), large.buttonRects.size());
    QVERIFY(small.buttonRects.size() >= 16);

    for (int index = 0; index < small.buttonRects.size(); ++index) {
        const QRect &smallRect = small.buttonRects.at(index);
        const QRect &mediumRect = medium.buttonRects.at(index);
        const QRect &largeRect = large.buttonRects.at(index);

        QVERIFY2(smallRect.width() > 0 && smallRect.height() > 0,
                 "Placeholder must be visible at small resolution");
        QVERIFY2(mediumRect.width() > 0 && mediumRect.height() > 0,
                 "Placeholder must be visible at medium resolution");
        QVERIFY2(largeRect.width() > 0 && largeRect.height() > 0,
                 "Placeholder must be visible at large resolution");
    }
}

void TestPlaceholderResponsivenessE2E::placeholdersFormUniformGridAcrossResolutions()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QApplication::processEvents();

    const Snapshot snapshot = captureSnapshot(window, 800, 800);

    Q_ASSERT(snapshot.buttonRects.size() >= 16);
    for (int index = 0; index < 16; ++index) {
        const QRect &rect = snapshot.buttonRects.at(index);
        QVERIFY2(rect.width() >= 40,
                 "Every grid placeholder must keep a usable width on resize");
        QVERIFY2(rect.height() >= 32,
                 "Every grid placeholder must keep a usable height on resize");
    }

    const QRect first = snapshot.buttonRects.at(0);
    const QRect secondInRow = snapshot.buttonRects.at(1);
    QVERIFY2(qAbs(first.height() - secondInRow.height()) <= 2,
             "Adjacent row buttons must share the same height");
}

void TestPlaceholderResponsivenessE2E::minimumSizeConstraintHoldsAcrossResolutions()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    QApplication::processEvents();

    const QSize minSize = window.minimumSize();

    const QVector<QSize> attempts = {
        QSize(120, 120),
        QSize(200, 200),
        QSize(320, 420),
        QSize(640, 480),
        QSize(1280, 800)
    };

    for (const QSize &requested : attempts) {
        window.resize(requested);
        QApplication::processEvents();
        const QSize actual = window.size();
        QVERIFY2(actual.width() >= minSize.width(),
                 "Window must not shrink below layout-imposed minimum width");
        QVERIFY2(actual.height() >= minSize.height(),
                 "Window must not shrink below layout-imposed minimum height");
    }
}
