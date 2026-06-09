#include <QtTest>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include "mainwindow.h"

class TestHelpMenuUnit : public QObject
{
    Q_OBJECT

private slots:
    void helpMenuIsRegisteredInMenuBar();
    void helpMenuExposesAboutAction();
    void helpMenuExposesDocumentationAction();
    void helpMenuPlaceholdersAreVisible();
};

void TestHelpMenuUnit::helpMenuIsRegisteredInMenuBar()
{
    MainWindow window;
    QMenuBar *menuBar = window.findChild<QMenuBar *>();
    QVERIFY(menuBar != nullptr);

    QMenu *helpMenu = menuBar->findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);
    QVERIFY(helpMenu->title() == QStringLiteral("&Help"));
    QVERIFY(menuBar->actions().contains(helpMenu->menuAction()));
}

static QAction *findActionByName(const QMenu *menu, const QString &name)
{
    for (QAction *action : menu->actions()) {
        if (action->objectName() == name) {
            return action;
        }
    }
    return nullptr;
}

void TestHelpMenuUnit::helpMenuExposesAboutAction()
{
    MainWindow window;
    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);

    QAction *aboutAction = findActionByName(helpMenu, QStringLiteral("actionAbout"));
    QVERIFY(aboutAction != nullptr);
    QVERIFY(aboutAction->text() == QStringLiteral("&About"));
}

void TestHelpMenuUnit::helpMenuExposesDocumentationAction()
{
    MainWindow window;
    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);

    QAction *documentationAction = findActionByName(helpMenu, QStringLiteral("actionDocumentation"));
    QVERIFY(documentationAction != nullptr);
    QVERIFY(documentationAction->text() == QStringLiteral("&Documentation"));
}

void TestHelpMenuUnit::helpMenuPlaceholdersAreVisible()
{
    MainWindow window;
    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);

    const QList<QAction *> actions = helpMenu->actions();
    QCOMPARE(actions.size(), 2);
    QVERIFY(actions.at(0)->text() == QStringLiteral("&About"));
    QVERIFY(actions.at(1)->text() == QStringLiteral("&Documentation"));
    QVERIFY(actions.at(0)->isVisible());
    QVERIFY(actions.at(1)->isVisible());
}

QTEST_MAIN(TestHelpMenuUnit)
#include "test_help_menu_unit.moc"
