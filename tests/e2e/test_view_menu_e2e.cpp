#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QtTest/QTest>

class TestViewMenuE2E : public QObject
{
    Q_OBJECT

private slots:
    void viewMenuIsPresentInMainWindow();
    void viewMenuTitleIsAmpersandView();
    void viewMenuActionsAreWiredUp();
    void triggeringViewMenuActionsChangesApplicationState();
    void viewMenuCoexistsWithFileAndEditMenus();
};

void TestViewMenuE2E::viewMenuIsPresentInMainWindow()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);
    QVERIFY(!view->title().isEmpty());
}

void TestViewMenuE2E::viewMenuTitleIsAmpersandView()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);
    QCOMPARE(view->title(), QLatin1String("&View"));
}

void TestViewMenuE2E::viewMenuActionsAreWiredUp()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);
    QVERIFY(!view->actions().isEmpty());

    bool foundToggleSidebar = false;
    bool foundToggleStatusbar = false;
    bool foundZoomIn = false;
    bool foundZoomOut = false;
    bool foundResetZoom = false;
    for (QAction *action : view->actions()) {
        if (action == window.actionToggleSidebar()) {
            foundToggleSidebar = true;
        } else if (action == window.actionToggleStatusbar()) {
            foundToggleStatusbar = true;
        } else if (action == window.actionZoomIn()) {
            foundZoomIn = true;
        } else if (action == window.actionZoomOut()) {
            foundZoomOut = true;
        } else if (action == window.actionResetZoom()) {
            foundResetZoom = true;
        }
    }
    QVERIFY(foundToggleSidebar);
    QVERIFY(foundToggleStatusbar);
    QVERIFY(foundZoomIn);
    QVERIFY(foundZoomOut);
    QVERIFY(foundResetZoom);
}

void TestViewMenuE2E::triggeringViewMenuActionsChangesApplicationState()
{
    MainWindow window;
    QVERIFY(window.viewMenu() != nullptr);

    const bool sidebarBefore = window.isSidebarVisible();
    window.actionToggleSidebar()->trigger();
    QCOMPARE(window.isSidebarVisible(), !sidebarBefore);

    const bool statusBefore = window.isStatusBarVisible();
    window.actionToggleStatusbar()->trigger();
    QCOMPARE(window.isStatusBarVisible(), !statusBefore);

    const int zoomBefore = window.currentZoomPercent();
    window.actionZoomIn()->trigger();
    QCOMPARE(window.currentZoomPercent(), zoomBefore + 10);
    window.actionZoomOut()->trigger();
    QCOMPARE(window.currentZoomPercent(), zoomBefore);
    window.actionResetZoom()->trigger();
    QCOMPARE(window.currentZoomPercent(), 100);
}

void TestViewMenuE2E::viewMenuCoexistsWithFileAndEditMenus()
{
    MainWindow window;
    QMenuBar *bar = window.findChild<QMenuBar *>();
    QVERIFY(bar != nullptr);

    QMenu *file = window.findChild<QMenu *>(QStringLiteral("menuFile"));
    QMenu *edit = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QMenu *view = window.viewMenu();

    QVERIFY(file != nullptr);
    QVERIFY(edit != nullptr);
    QVERIFY(view != nullptr);

    QVERIFY(file->title() != view->title());
    QVERIFY(edit->title() != view->title());
    QVERIFY(file->title() != edit->title());
}

QTEST_MAIN(TestViewMenuE2E)
#include "test_view_menu_e2e.moc"
