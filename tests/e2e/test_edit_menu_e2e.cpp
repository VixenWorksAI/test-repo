#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QPoint>
#include <QRect>
#include <QString>
#include <QtTest>

#include "mainwindow.h"

class TestEditMenuE2E : public QObject
{
    Q_OBJECT

private slots:
    void editMenuAppearsOnMainWindow();
    void editMenuIsPositionedNearFileMenu();
    void copyAndPastePlaceholdersAreVisibleInEditMenu();

private:
    static int menubarHeightOf(const QWidget *window);
};

void TestEditMenuE2E::editMenuAppearsOnMainWindow()
{
    MainWindow window;
    window.resize(800, 600);
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window));

    QMenuBar *menubar = window.menuBar();
    QVERIFY(menubar != nullptr);
    QVERIFY(menubar->isVisible());

    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(editMenu != nullptr);
    QCOMPARE(editMenu->title(), QString("&Edit"));
    QVERIFY(editMenu->actions().size() >= 2);
}

void TestEditMenuE2E::editMenuIsPositionedNearFileMenu()
{
    MainWindow window;
    window.resize(800, 600);
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window));

    QMenuBar *menubar = window.menuBar();
    QMenu *fileMenu = window.findChild<QMenu *>(QStringLiteral("menuFile"));
    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(fileMenu != nullptr);
    QVERIFY(editMenu != nullptr);

    const QRect fileGeom = menubar->actionGeometry(fileMenu->menuAction());
    const QRect editGeom = menubar->actionGeometry(editMenu->menuAction());
    QVERIFY(fileGeom.isValid());
    QVERIFY(editGeom.isValid());
    QVERIFY2(!editGeom.intersects(fileGeom),
             "Edit menu must not overlap File menu in the menu bar");
}

void TestEditMenuE2E::copyAndPastePlaceholdersAreVisibleInEditMenu()
{
    MainWindow window;
    window.resize(800, 600);
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window));

    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(editMenu != nullptr);
    editMenu->popup(window.mapToGlobal(QPoint(0, menubarHeightOf(&window))));
    QVERIFY(QTest::qWaitForWindowExposed(editMenu));

    QAction *copyAction = nullptr;
    QAction *pasteAction = nullptr;
    for (QAction *action : editMenu->actions()) {
        if (action->text() == QString("&Copy")) {
            copyAction = action;
        } else if (action->text() == QString("&Paste")) {
            pasteAction = action;
        }
    }
    QVERIFY2(copyAction != nullptr, "Copy placeholder must be visible in Edit menu");
    QVERIFY2(pasteAction != nullptr, "Paste placeholder must be visible in Edit menu");

    editMenu->hide();
}

int TestEditMenuE2E::menubarHeightOf(const QWidget *window)
{
    QMenuBar *menubar = window->findChild<QMenuBar *>();
    return menubar ? menubar->height() : 0;
}

QTEST_MAIN(TestEditMenuE2E)
#include "test_edit_menu_e2e.moc"
