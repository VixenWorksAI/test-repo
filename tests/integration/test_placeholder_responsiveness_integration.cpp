#include <QtTest>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>

#include "mainwindow.h"
#include "test_placeholder_responsiveness_integration.h"

void TestPlaceholderResponsivenessIntegration::resizeAndProcess(MainWindow &window,
                                                                 int width,
                                                                 int height)
{
    window.resize(width, height);
    QResizeEvent event(window.size(), window.size());
    QApplication::sendEvent(&window, &event);
    QApplication::processEvents();
}

void TestPlaceholderResponsivenessIntegration::windowHasUsableMinimumSize()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    const QSize minimum = window.minimumSize();
    QVERIFY2(minimum.width() >= 320, "Window minimum width must allow keypad to render");
    QVERIFY2(minimum.height() >= 420, "Window minimum height must allow keypad to render");
}

void TestPlaceholderResponsivenessIntegration::buttonsStayAboveMinimumAtTinyWindowSize()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    resizeAndProcess(window, 240, 320);
    QApplication::processEvents();

    const QList<QPushButton *> buttons = window.findChildren<QPushButton *>();
    QVERIFY(buttons.size() >= 16);

    for (QPushButton *button : buttons) {
        QVERIFY2(button->width() >= 40,
                 "Button width must not collapse below usable size");
        QVERIFY2(button->height() >= 32,
                 "Button height must not collapse below usable size");
    }
}

void TestPlaceholderResponsivenessIntegration::buttonsRemainVisibleAtVeryLargeWindowSize()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    resizeAndProcess(window, 1600, 1200);
    QApplication::processEvents();

    const QList<QPushButton *> buttons = window.findChildren<QPushButton *>();
    QVERIFY(buttons.size() >= 16);

    for (QPushButton *button : buttons) {
        QVERIFY2(button->width() > 0, "Button must remain visible (positive width)");
        QVERIFY2(button->height() > 0, "Button must remain visible (positive height)");
    }
}

void TestPlaceholderResponsivenessIntegration::allPlaceholdersRemainInsideCentralWidget()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    Q_UNUSED(app);

    MainWindow window;
    window.show();
    resizeAndProcess(window, 800, 600);
    QApplication::processEvents();

    const QWidget *central = window.centralWidget();
    QVERIFY(central != nullptr);
    const QRect centralRect = central->rect();

    const QList<QPushButton *> buttons = window.findChildren<QPushButton *>();
    QVERIFY(buttons.size() >= 16);

    for (QPushButton *button : buttons) {
        const QRect buttonRect(button->mapTo(central, QPoint(0, 0)), button->size());
        QVERIFY2(centralRect.intersects(buttonRect)
                     || centralRect.contains(buttonRect),
                 "Placeholder must remain inside the central widget when the window is resized");
    }
}
