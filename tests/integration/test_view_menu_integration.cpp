#include "mainwindow.h"

#include <QAction>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QtTest/QTest>

class TestViewMenuIntegration : public QObject
{
    Q_OBJECT

private slots:
    void viewMenuIsAttachedToMenuBar();
    void viewMenuSitsBetweenEditMenuAndEnd();
    void viewMenuContainsExpectedToggleActions();
    void toolbarsSubMenuContainsMainToolbarToggle();
    void viewMenuDoesNotOverlapWithEditMenu();
    void viewMenuActionsAreCheckableWhereAppropriate();
};

void TestViewMenuIntegration::viewMenuIsAttachedToMenuBar()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);
    QMenuBar *bar = window.findChild<QMenuBar *>();
    QVERIFY(bar != nullptr);
    QVERIFY(bar->actions().contains(view->menuAction()));
}

void TestViewMenuIntegration::viewMenuSitsBetweenEditMenuAndEnd()
{
    MainWindow window;
    QMenuBar *bar = window.findChild<QMenuBar *>();
    QVERIFY(bar != nullptr);

    QList<QMenu *> topLevelMenus = bar->findChildren<QMenu *>();
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);

    QMenu *edit = nullptr;
    for (QMenu *menu : topLevelMenus) {
        if (menu->objectName() == QLatin1String("menuEdit")) {
            edit = menu;
            break;
        }
    }
    QVERIFY(edit != nullptr);

    int editIndex = -1;
    int viewIndex = -1;
    for (int i = 0; i < topLevelMenus.size(); ++i) {
        if (topLevelMenus.at(i) == edit) {
            editIndex = i;
        }
        if (topLevelMenus.at(i) == view) {
            viewIndex = i;
        }
    }
    QVERIFY(editIndex >= 0);
    QVERIFY(viewIndex > editIndex);
}

void TestViewMenuIntegration::viewMenuContainsExpectedToggleActions()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);

    QVERIFY(view->actions().contains(window.actionToggleSidebar()));
    QVERIFY(view->actions().contains(window.actionToggleStatusbar()));
    QVERIFY(view->actions().contains(window.actionZoomIn()));
    QVERIFY(view->actions().contains(window.actionZoomOut()));
    QVERIFY(view->actions().contains(window.actionResetZoom()));
}

void TestViewMenuIntegration::toolbarsSubMenuContainsMainToolbarToggle()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QVERIFY(view != nullptr);

    QMenu *toolbars = nullptr;
    for (QAction *action : view->actions()) {
        if (action->menu() != nullptr && action->menu()->title() == QLatin1String("&Toolbars")) {
            toolbars = action->menu();
            break;
        }
    }
    QVERIFY(toolbars != nullptr);
    QVERIFY(toolbars->actions().contains(window.actionToggleMainToolbar()));
}

void TestViewMenuIntegration::viewMenuDoesNotOverlapWithEditMenu()
{
    MainWindow window;
    QMenu *view = window.viewMenu();
    QMenu *edit = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(view != nullptr);
    QVERIFY(edit != nullptr);
    QVERIFY(view != edit);
    QVERIFY(view->title() != edit->title());

    for (QAction *viewAction : view->actions()) {
        QVERIFY(!edit->actions().contains(viewAction));
    }
}

void TestViewMenuIntegration::viewMenuActionsAreCheckableWhereAppropriate()
{
    MainWindow window;
    QVERIFY(window.actionToggleSidebar()->isCheckable());
    QVERIFY(window.actionToggleStatusbar()->isCheckable());
    QVERIFY(window.actionToggleMainToolbar()->isCheckable());
    QVERIFY(!window.actionZoomIn()->isCheckable());
    QVERIFY(!window.actionZoomOut()->isCheckable());
    QVERIFY(!window.actionResetZoom()->isCheckable());
}

QTEST_MAIN(TestViewMenuIntegration)
#include "test_view_menu_integration.moc"
