#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QtTest/QTest>

class TestMenuIntegrationUnit : public QObject
{
    Q_OBJECT

private slots:
    void allRequiredMenusPresent();
    void menuTitlesAreUnique();
    void menusAreAccessibleViaMenuBar();
    void menuActionsDoNotShareObjectIdentity();
    void fileMenuContainsExitAction();
    void viewMenuContainsToggleAndZoomActions();
    void helpMenuContainsAboutAndDocumentation();
    void editMenuIsWiredIntoMenuBar();
};

void TestMenuIntegrationUnit::allRequiredMenusPresent()
{
    MainWindow window;
    const QList<QMenu *> menus = window.topLevelMenus();
    QCOMPARE(menus.size(), 4);
}

void TestMenuIntegrationUnit::menuTitlesAreUnique()
{
    MainWindow window;
    QVERIFY(window.hasUniqueMenuTitles());
}

void TestMenuIntegrationUnit::menusAreAccessibleViaMenuBar()
{
    MainWindow window;
    QMenuBar *bar = window.menuBar();
    QVERIFY(bar != nullptr);
    const QList<QAction *> actions = bar->actions();
    QVERIFY(actions.size() >= 4);

    bool hasFile = false;
    bool hasEdit = false;
    bool hasView = false;
    bool hasHelp = false;
    for (QAction *action : actions) {
        if (action == nullptr || action->menu() == nullptr) {
            continue;
        }
        const QString title = action->menu()->title();
        if (title.contains("File")) hasFile = true;
        if (title.contains("Edit")) hasEdit = true;
        if (title.contains("View")) hasView = true;
        if (title.contains("Help")) hasHelp = true;
    }
    QVERIFY(hasFile);
    QVERIFY(hasEdit);
    QVERIFY(hasView);
    QVERIFY(hasHelp);
}

void TestMenuIntegrationUnit::menuActionsDoNotShareObjectIdentity()
{
    MainWindow window;
    QAction *sidebar = window.actionToggleSidebar();
    QAction *statusbar = window.actionToggleStatusbar();
    QAction *toolbar = window.actionToggleMainToolbar();
    QVERIFY(sidebar != nullptr);
    QVERIFY(statusbar != nullptr);
    QVERIFY(toolbar != nullptr);
    QVERIFY(sidebar != statusbar);
    QVERIFY(sidebar != toolbar);
    QVERIFY(statusbar != toolbar);
}

void TestMenuIntegrationUnit::fileMenuContainsExitAction()
{
    MainWindow window;
    bool found = false;
    for (QMenu *menu : window.topLevelMenus()) {
        if (menu->title().contains("File")) {
            for (QAction *action : menu->actions()) {
                if (action != nullptr && action->text().contains("xit", Qt::CaseInsensitive)) {
                    found = true;
                    break;
                }
            }
        }
    }
    QVERIFY(found);
}

void TestMenuIntegrationUnit::viewMenuContainsToggleAndZoomActions()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);

    bool hasToggleSidebar = false;
    bool hasToggleStatusbar = false;
    bool hasZoomIn = false;
    bool hasZoomOut = false;
    bool hasResetZoom = false;
    for (QAction *action : view->actions()) {
        if (action == nullptr) {
            continue;
        }
        const QString text = action->text();
        if (text.contains("Sidebar")) hasToggleSidebar = true;
        if (text.contains("Status")) hasToggleStatusbar = true;
        if (text.contains("Zoom") && text.contains("In")) hasZoomIn = true;
        if (text.contains("Zoom") && text.contains("Out")) hasZoomOut = true;
        if (text.contains("Reset")) hasResetZoom = true;
    }
    QVERIFY(hasToggleSidebar);
    QVERIFY(hasToggleStatusbar);
    QVERIFY(hasZoomIn);
    QVERIFY(hasZoomOut);
    QVERIFY(hasResetZoom);
}

void TestMenuIntegrationUnit::helpMenuContainsAboutAndDocumentation()
{
    MainWindow window;
    bool hasAbout = false;
    bool hasDocumentation = false;
    for (QMenu *menu : window.topLevelMenus()) {
        if (!menu->title().contains("Help")) {
            continue;
        }
        for (QAction *action : menu->actions()) {
            if (action == nullptr) {
                continue;
            }
            const QString text = action->text();
            if (text.contains("About")) hasAbout = true;
            if (text.contains("Documentation")) hasDocumentation = true;
        }
    }
    QVERIFY(hasAbout);
    QVERIFY(hasDocumentation);
}

void TestMenuIntegrationUnit::editMenuIsWiredIntoMenuBar()
{
    MainWindow window;
    bool hasEdit = false;
    for (QMenu *menu : window.topLevelMenus()) {
        if (menu->title().contains("Edit")) {
            hasEdit = true;
            QVERIFY(menu->actions().size() >= 2);
        }
    }
    QVERIFY(hasEdit);
}

QTEST_MAIN(TestMenuIntegrationUnit)
#include "test_menu_integration_unit.moc"
