#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QApplication>
#include <QtTest/QtTest>
#include "mainwindow.h"

class TestFileMenuUnit : public QObject
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

    void fileMenuCreationDoesNotAffectOtherUi()
    {
        QMenuBar *menuBar = window->menuBar();
        QVERIFY(menuBar != nullptr);

        QMenu *fileMenu = window->findChild<QMenu *>("menuFile");
        QVERIFY(fileMenu != nullptr);
        QCOMPARE(fileMenu->title(), QString("&File"));

        QStatusBar *statusBar = window->statusBar();
        QVERIFY(statusBar != nullptr);
        QCOMPARE(statusBar->objectName(), QString("statusbar"));

        QWidget *central = window->centralWidget();
        QVERIFY(central != nullptr);
        QVERIFY(central->objectName().isEmpty() || central->objectName() == QString("centralwidget"));
    }

private:
    QApplication *app = nullptr;
    MainWindow *window = nullptr;
};

QTEST_MAIN(TestFileMenuUnit)
#include "test_file_menu_unit.moc"
