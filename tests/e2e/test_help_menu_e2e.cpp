#include <QtTest>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QRect>

#include "mainwindow.h"

class TestHelpMenuE2E : public QObject
{
    Q_OBJECT

private slots:
    void helpMenuPresentsPlaceholdersWhenOpened();
};

void TestHelpMenuE2E::helpMenuPresentsPlaceholdersWhenOpened()
{
    MainWindow window;
    window.resize(1024, 768);
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window));

    QMenuBar *menuBar = window.menuBar();
    QVERIFY(menuBar != nullptr);

    QMenu *helpMenu = window.findChild<QMenu *>(QStringLiteral("menuHelp"));
    QVERIFY(helpMenu != nullptr);
    QVERIFY(helpMenu->title() == QStringLiteral("&Help"));

    QAction *helpMenuAction = helpMenu->menuAction();
    const QRect menuActionRect = menuBar->actionGeometry(helpMenuAction);
    QVERIFY(!menuActionRect.isEmpty());
    QTest::mouseClick(menuBar, Qt::LeftButton, Qt::NoModifier, menuActionRect.center());

    QTRY_VERIFY(helpMenu->isVisible());

    const QList<QAction *> actions = helpMenu->actions();
    QCOMPARE(actions.size(), 2);
    QVERIFY(actions.at(0)->text() == QStringLiteral("&About"));
    QVERIFY(actions.at(1)->text() == QStringLiteral("&Documentation"));
    QVERIFY(actions.at(0)->isVisible());
    QVERIFY(actions.at(1)->isVisible());

    helpMenu->close();
    QVERIFY(!helpMenu->isVisible());
}

QTEST_MAIN(TestHelpMenuE2E)
#include "test_help_menu_e2e.moc"
