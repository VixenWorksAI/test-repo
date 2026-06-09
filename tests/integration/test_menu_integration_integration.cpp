#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QtTest/QTest>

class TestMenuIntegrationIntegration : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void allMenusFunctionInMainWindow();
    void togglingActionsDoesNotRemoveMenuEntries();
    void noActionBelongsToTwoTopLevelMenus();

private:
    MainWindow *m_window = nullptr;
};

void TestMenuIntegrationIntegration::initTestCase()
{
    qApp->setQuitOnLastWindowClosed(false);
    m_window = new MainWindow();
}

void TestMenuIntegrationIntegration::allMenusFunctionInMainWindow()
{
    QVERIFY(m_window != nullptr);
    QMenuBar *bar = m_window->menuBar();
    QVERIFY(bar != nullptr);
    QCOMPARE(bar->actions().size(), m_window->topLevelMenus().size());

    for (QMenu *menu : m_window->topLevelMenus()) {
        QVERIFY(menu != nullptr);
        QVERIFY(menu->isEnabled());
        QVERIFY(menu->menuAction()->isVisible());
    }
}

void TestMenuIntegrationIntegration::togglingActionsDoesNotRemoveMenuEntries()
{
    QVERIFY(m_window != nullptr);
    const int initialCount = m_window->topLevelMenus().size();
    QVERIFY(initialCount >= 4);

    m_window->actionToggleSidebar()->trigger();
    m_window->actionToggleStatusbar()->trigger();
    m_window->actionToggleMainToolbar()->trigger();
    m_window->actionZoomIn()->trigger();
    m_window->actionZoomOut()->trigger();
    m_window->actionResetZoom()->trigger();

    QCOMPARE(m_window->topLevelMenus().size(), initialCount);
    QVERIFY(m_window->hasUniqueMenuTitles());
}

void TestMenuIntegrationIntegration::noActionBelongsToTwoTopLevelMenus()
{
    QVERIFY(m_window != nullptr);
    QList<QAction *> seen;
    for (QMenu *menu : m_window->topLevelMenus()) {
        for (QAction *action : menu->actions()) {
            if (action == nullptr || action->isSeparator()) {
                continue;
            }
            QVERIFY(!seen.contains(action));
            seen.append(action);
        }
    }
}

QTEST_MAIN(TestMenuIntegrationIntegration)
#include "test_menu_integration_integration.moc"
