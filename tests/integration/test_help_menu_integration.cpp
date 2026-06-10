#include <QtTest>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QStatusBar>

#include "mainwindow.h"

class TestHelpMenuIntegration : public QObject
{
    Q_OBJECT

private slots:
    void helpMenuCoexistsWithExistingMenus();
    void triggeringAboutSlotDoesNotCrash();
    void triggeringDocumentationSlotDoesNotCrash();
};

void TestHelpMenuIntegration::helpMenuCoexistsWithExistingMenus()
{
    MainWindow window;
    QMenuBar *menuBar = window.menuBar();
    QVERIFY(menuBar != nullptr);

    const QList<QMenu *> menus = menuBar->findChildren<QMenu *>();
    const QStringList menuNames = {
        QStringLiteral("menuFile"),
        QStringLiteral("menuEdit"),
        QStringLiteral("menuView"),
        QStringLiteral("menuHelp")
    };
    for (const QString &name : menuNames) {
        QVERIFY2(menus.contains(menuBar->findChild<QMenu *>(name)),
                 qPrintable(QStringLiteral("Missing menu: ") + name));
    }
}

void TestHelpMenuIntegration::triggeringAboutSlotDoesNotCrash()
{
    MainWindow window;
    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);

    QAction *aboutAction = nullptr;
    for (QAction *action : helpMenu->actions()) {
        if (action->objectName() == QLatin1String("actionAbout")) {
            aboutAction = action;
            break;
        }
    }
    QVERIFY(aboutAction != nullptr);

    aboutAction->trigger();
    QVERIFY(aboutAction->isEnabled());
}

void TestHelpMenuIntegration::triggeringDocumentationSlotDoesNotCrash()
{
    MainWindow window;
    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);

    QAction *documentationAction = nullptr;
    for (QAction *action : helpMenu->actions()) {
        if (action->objectName() == QLatin1String("actionDocumentation")) {
            documentationAction = action;
            break;
        }
    }
    QVERIFY(documentationAction != nullptr);

    documentationAction->trigger();
    QVERIFY(documentationAction->isEnabled());
}

QTEST_MAIN(TestHelpMenuIntegration)
#include "test_help_menu_integration.moc"
