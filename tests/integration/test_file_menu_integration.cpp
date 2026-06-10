#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QApplication>
#include <QtTest/QtTest>
#include "mainwindow.h"

class TestFileMenuIntegration : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        int argc = 0;
        char **argv = nullptr;
        app = new QApplication(argc, argv);
        window = new MainWindow();
    }

    void cleanupTestCase()
    {
        delete window;
        delete app;
    }

    void fileMenuIsVisibleAndInteractive()
    {
        window->show();
        QVERIFY(window->isVisible());

        QMenuBar *menuBar = window->menuBar();
        QVERIFY(menuBar != nullptr);
        QVERIFY(menuBar->isVisible());

        QMenu *fileMenu = window->findChild<QMenu *>("menuFile");
        QVERIFY(fileMenu != nullptr);
        QCOMPARE(fileMenu->title(), QString("&File"));

        QAction *exitAction = window->findChild<QAction *>("actionExit");
        QVERIFY(exitAction != nullptr);
        QCOMPARE(exitAction->text(), QString("E&xit"));
        QVERIFY(exitAction->isEnabled());

        QList<QAction *> actions = fileMenu->actions();
        bool exitFound = false;
        for (QAction *a : actions) {
            if (a == exitAction) {
                exitFound = true;
                break;
            }
        }
        QVERIFY(exitFound);
    }

private:
    QApplication *app = nullptr;
    MainWindow *window = nullptr;
};

QTEST_MAIN(TestFileMenuIntegration)
#include "test_file_menu_integration.moc"
