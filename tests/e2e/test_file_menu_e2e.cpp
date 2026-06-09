#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QApplication>
#include <QtTest/QtTest>
#include "mainwindow.h"

class TestFileMenuE2E : public QObject
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

    void fileMenuAppearsInMainWindow()
    {
        window->show();
        QVERIFY(window->isVisible());
        QCOMPARE(window->windowTitle(), QString("Calculator"));

        QMenuBar *menuBar = window->menuBar();
        QVERIFY(menuBar != nullptr);

        QList<QAction *> topLevel = menuBar->actions();
        bool fileMenuPresent = false;
        for (QAction *a : topLevel) {
            if (a->text() == QString("&File")) {
                fileMenuPresent = true;
                break;
            }
        }
        QVERIFY(fileMenuPresent);

        QMenu *fileMenu = window->findChild<QMenu *>("menuFile");
        QVERIFY(fileMenu != nullptr);

        QAction *exitAction = window->findChild<QAction *>("actionExit");
        QVERIFY(exitAction != nullptr);
        QCOMPARE(exitAction->text(), QString("E&xit"));
        QVERIFY(fileMenu->actions().contains(exitAction));
    }

private:
    QApplication *app = nullptr;
    MainWindow *window = nullptr;
};

QTEST_MAIN(TestFileMenuE2E)
#include "test_file_menu_e2e.moc"
