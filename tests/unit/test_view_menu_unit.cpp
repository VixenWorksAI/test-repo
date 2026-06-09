#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QtTest/QSignalSpy>
#include <QtTest/QTest>

class TestViewMenuUnit : public QObject
{
    Q_OBJECT

private slots:
    void toggleSidebarTogglesCheckedState();
    void toggleStatusbarTogglesCheckedState();
    void toggleMainToolbarTogglesCheckedState();
    void zoomInIncrementsZoomPercent();
    void zoomOutDecrementsZoomPercent();
    void resetZoomReturnsToDefault();
    void zoomInClampsAtMaximum();
    void zoomOutClampsAtMinimum();
};

void TestViewMenuUnit::toggleSidebarTogglesCheckedState()
{
    MainWindow window;
    QAction *action = window.actionToggleSidebar();
    QVERIFY(action != nullptr);
    QVERIFY(action->isCheckable());

    const bool initial = action->isChecked();
    action->toggle();
    QCOMPARE(action->isChecked(), !initial);
    QCOMPARE(window.isSidebarVisible(), action->isChecked());

    action->toggle();
    QCOMPARE(action->isChecked(), initial);
    QCOMPARE(window.isSidebarVisible(), action->isChecked());
}

void TestViewMenuUnit::toggleStatusbarTogglesCheckedState()
{
    MainWindow window;
    QAction *action = window.actionToggleStatusbar();
    QVERIFY(action != nullptr);
    QVERIFY(action->isCheckable());

    const bool initial = action->isChecked();
    action->toggle();
    QCOMPARE(action->isChecked(), !initial);
    QCOMPARE(window.isStatusBarVisible(), action->isChecked());

    action->toggle();
    QCOMPARE(action->isChecked(), initial);
    QCOMPARE(window.isStatusBarVisible(), action->isChecked());
}

void TestViewMenuUnit::toggleMainToolbarTogglesCheckedState()
{
    MainWindow window;
    QAction *action = window.actionToggleMainToolbar();
    QVERIFY(action != nullptr);
    QVERIFY(action->isCheckable());

    const bool initial = action->isChecked();
    action->toggle();
    QCOMPARE(action->isChecked(), !initial);
    QCOMPARE(window.isMainToolbarVisible(), action->isChecked());

    action->toggle();
    QCOMPARE(action->isChecked(), initial);
    QCOMPARE(window.isMainToolbarVisible(), action->isChecked());
}

void TestViewMenuUnit::zoomInIncrementsZoomPercent()
{
    MainWindow window;
    const int before = window.currentZoomPercent();
    QVERIFY(window.actionZoomIn() != nullptr);
    window.actionZoomIn()->trigger();
    QCOMPARE(window.currentZoomPercent(), before + 10);
}

void TestViewMenuUnit::zoomOutDecrementsZoomPercent()
{
    MainWindow window;
    const int before = window.currentZoomPercent();
    QVERIFY(window.actionZoomOut() != nullptr);
    window.actionZoomOut()->trigger();
    QCOMPARE(window.currentZoomPercent(), before - 10);
}

void TestViewMenuUnit::resetZoomReturnsToDefault()
{
    MainWindow window;
    window.actionZoomIn()->trigger();
    window.actionZoomIn()->trigger();
    QVERIFY(window.actionResetZoom() != nullptr);
    window.actionResetZoom()->trigger();
    QCOMPARE(window.currentZoomPercent(), 100);
}

void TestViewMenuUnit::zoomInClampsAtMaximum()
{
    MainWindow window;
    for (int i = 0; i < 100; ++i) {
        window.actionZoomIn()->trigger();
    }
    QCOMPARE(window.currentZoomPercent(), 400);
}

void TestViewMenuUnit::zoomOutClampsAtMinimum()
{
    MainWindow window;
    for (int i = 0; i < 100; ++i) {
        window.actionZoomOut()->trigger();
    }
    QCOMPARE(window.currentZoomPercent(), 50);
}

QTEST_MAIN(TestViewMenuUnit)
#include "test_view_menu_unit.moc"
