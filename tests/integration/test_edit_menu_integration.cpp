#include <QAction>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QtTest>

#include "mainwindow.h"

class TestEditMenuIntegration : public QObject
{
    Q_OBJECT

private slots:
    void editMenuIsWiredIntoMainWindow();
    void editMenuPositionedAlongsideFileMenu();
    void copyAndPastePlaceholdersAreAccessibleViaMainWindow();
};

void TestEditMenuIntegration::editMenuIsWiredIntoMainWindow()
{
    MainWindow window;
    QMenuBar *menubar = window.menuBar();
    QVERIFY(menubar != nullptr);

    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(editMenu != nullptr);
    QVERIFY(editMenu->parent() != nullptr);
    QCOMPARE(editMenu->parent(), menubar);
}

void TestEditMenuIntegration::editMenuPositionedAlongsideFileMenu()
{
    MainWindow window;
    QMenuBar *menubar = window.menuBar();
    QVERIFY(menubar != nullptr);

    QMenu *fileMenu = window.findChild<QMenu *>(QStringLiteral("menuFile"));
    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(fileMenu != nullptr);
    QVERIFY(editMenu != nullptr);

    const QList<QAction *> menubarActions = menubar->actions();
    const int fileIndex = menubarActions.indexOf(fileMenu->menuAction());
    const int editIndex = menubarActions.indexOf(editMenu->menuAction());
    QVERIFY(fileIndex >= 0);
    QVERIFY(editIndex >= 0);
    QVERIFY2(fileIndex < editIndex,
             "Edit menu must appear after File menu in the main window menu bar");
}

void TestEditMenuIntegration::copyAndPastePlaceholdersAreAccessibleViaMainWindow()
{
    MainWindow window;

    QAction *copyAction = window.findChild<QAction *>(QStringLiteral("actionCopy"));
    QAction *pasteAction = window.findChild<QAction *>(QStringLiteral("actionPaste"));
    QVERIFY(copyAction != nullptr);
    QVERIFY(pasteAction != nullptr);
    QVERIFY(copyAction->parent() != nullptr);
    QVERIFY(pasteAction->parent() != nullptr);
    QVERIFY(!copyAction->text().isEmpty());
    QVERIFY(!pasteAction->text().isEmpty());
}

QTEST_MAIN(TestEditMenuIntegration)
#include "test_edit_menu_integration.moc"
