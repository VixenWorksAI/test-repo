#include <QAction>
#include <QMenu>
#include <QtTest>

#include "mainwindow.h"
#include "ui_mainwindow.h"

class TestEditMenuUnit : public QObject
{
    Q_OBJECT

private slots:
    void menuBarContainsEditMenu();
    void editMenuContainsCopyAndPastePlaceholders();
    void addingEditMenuPreservesExistingFileMenu();
};

void TestEditMenuUnit::menuBarContainsEditMenu()
{
    MainWindow window;
    QMenuBar *menubar = window.menuBar();
    QVERIFY(menubar != nullptr);

    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY2(editMenu != nullptr, "Edit menu must exist in main window");
    QCOMPARE(editMenu->title(), QString("&Edit"));

    QVERIFY2(menubar->actions().contains(editMenu->menuAction()),
             "Edit menu must be attached to the main window menu bar");
    QCOMPARE(editMenu->menuAction()->text(), QString("&Edit"));
}

void TestEditMenuUnit::editMenuContainsCopyAndPastePlaceholders()
{
    MainWindow window;
    QMenu *editMenu = window.findChild<QMenu *>(QStringLiteral("menuEdit"));
    QVERIFY(editMenu != nullptr);

    QAction *copyAction = window.findChild<QAction *>(QStringLiteral("actionCopy"));
    QAction *pasteAction = window.findChild<QAction *>(QStringLiteral("actionPaste"));
    QVERIFY2(copyAction != nullptr, "Copy placeholder action must exist");
    QVERIFY2(pasteAction != nullptr, "Paste placeholder action must exist");

    QCOMPARE(copyAction->text(), QString("&Copy"));
    QCOMPARE(pasteAction->text(), QString("&Paste"));

    const QList<QAction *> editActions = editMenu->actions();
    QVERIFY(editActions.contains(copyAction));
    QVERIFY(editActions.contains(pasteAction));
}

void TestEditMenuUnit::addingEditMenuPreservesExistingFileMenu()
{
    MainWindow window;
    QMenuBar *menubar = window.menuBar();
    QVERIFY(menubar != nullptr);

    QMenu *fileMenu = window.findChild<QMenu *>(QStringLiteral("menuFile"));
    QVERIFY2(fileMenu != nullptr, "File menu must remain after adding Edit menu");
    QCOMPARE(fileMenu->title(), QString("&File"));
    QVERIFY(menubar->actions().contains(fileMenu->menuAction()));

    QAction *exitAction = window.findChild<QAction *>(QStringLiteral("actionExit"));
    QVERIFY2(exitAction != nullptr, "Exit action must remain after adding Edit menu");
    const QList<QAction *> fileActions = fileMenu->actions();
    QVERIFY(fileActions.contains(exitAction));
}

QTEST_MAIN(TestEditMenuUnit)
#include "test_edit_menu_unit.moc"
