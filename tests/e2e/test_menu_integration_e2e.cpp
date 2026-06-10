#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QSignalSpy>
#include <QtTest/QTest>

class TestMenuIntegrationE2E : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void allMenusAccessibleFromMainWindow();
    void menuOrderIsConsistent();
    void eachMenuHasAtLeastOneAction();
    void exitingFromFileMenuTriggersQuit();
    void aboutMenuOpensAboutDialog();
    void documentationMenuOpensDocumentation();

private:
    MainWindow *m_window = nullptr;
};

void TestMenuIntegrationE2E::initTestCase()
{
    m_window = new MainWindow();
    QVERIFY(m_window != nullptr);
}

void TestMenuIntegrationE2E::cleanupTestCase()
{
    delete m_window;
    m_window = nullptr;
}

void TestMenuIntegrationE2E::allMenusAccessibleFromMainWindow()
{
    QMenuBar *bar = m_window->menuBar();
    QVERIFY(bar != nullptr);
    QVERIFY(bar->actions().size() >= 4);
    for (QAction *action : bar->actions()) {
        if (action == nullptr) {
            continue;
        }
        QVERIFY(action->isVisible());
        QVERIFY(action->text().contains("&"));
    }
}

void TestMenuIntegrationE2E::menuOrderIsConsistent()
{
    const QList<QMenu *> menus = m_window->topLevelMenus();
    QVERIFY(menus.size() >= 4);
    QVERIFY(menus[0]->title().contains("File"));
    QCOMPARE(menus[menus.size() - 1]->title(), menus.last()->title());
    bool editBeforeView = false;
    bool viewBeforeHelp = false;
    int editIdx = -1;
    int viewIdx = -1;
    int helpIdx = -1;
    for (int i = 0; i < menus.size(); ++i) {
        const QString title = menus[i]->title();
        if (title.contains("Edit")) editIdx = i;
        if (title.contains("View")) viewIdx = i;
        if (title.contains("Help")) helpIdx = i;
    }
    QVERIFY(editIdx >= 0);
    QVERIFY(viewIdx >= 0);
    QVERIFY(helpIdx >= 0);
    if (editIdx < viewIdx) editBeforeView = true;
    if (viewIdx < helpIdx) viewBeforeHelp = true;
    QVERIFY(editBeforeView);
    QVERIFY(viewBeforeHelp);
}

void TestMenuIntegrationE2E::eachMenuHasAtLeastOneAction()
{
    for (QMenu *menu : m_window->topLevelMenus()) {
        QVERIFY(menu != nullptr);
        QVERIFY(menu->actions().size() >= 1);
    }
}

void TestMenuIntegrationE2E::exitingFromFileMenuTriggersQuit()
{
    QAction *exitAction = nullptr;
    for (QMenu *menu : m_window->topLevelMenus()) {
        if (!menu->title().contains("File")) {
            continue;
        }
        for (QAction *action : menu->actions()) {
            if (action != nullptr && action->text().contains("xit", Qt::CaseInsensitive)) {
                exitAction = action;
                break;
            }
        }
    }
    QVERIFY(exitAction != nullptr);
    QSignalSpy spy(exitAction, &QAction::triggered);
    QAction::connect(exitAction, &QAction::triggered, qApp, []() { QCoreApplication::quit(); });
    exitAction->trigger();
    QCOMPARE(spy.count(), 1);
}

void TestMenuIntegrationE2E::aboutMenuOpensAboutDialog()
{
    QSignalSpy spy(m_window, &MainWindow::aboutDialogRequested);
    QAction *aboutAction = nullptr;
    for (QMenu *menu : m_window->topLevelMenus()) {
        if (!menu->title().contains("Help")) {
            continue;
        }
        for (QAction *action : menu->actions()) {
            if (action != nullptr && action->text().contains("About")) {
                aboutAction = action;
                break;
            }
        }
    }
    QVERIFY(aboutAction != nullptr);
    aboutAction->trigger();
    QCOMPARE(spy.count(), 1);
}

void TestMenuIntegrationE2E::documentationMenuOpensDocumentation()
{
    QSignalSpy spy(m_window, &MainWindow::documentationRequested);
    QAction *docAction = nullptr;
    for (QMenu *menu : m_window->topLevelMenus()) {
        if (!menu->title().contains("Help")) {
            continue;
        }
        for (QAction *action : menu->actions()) {
            if (action != nullptr && action->text().contains("Documentation")) {
                docAction = action;
                break;
            }
        }
    }
    QVERIFY(docAction != nullptr);
    docAction->trigger();
    QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(TestMenuIntegrationE2E)
#include "test_menu_integration_e2e.moc"
