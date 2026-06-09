#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QtTest/QtTest>

class ProFileIntegrationTest : public QObject
{
    Q_OBJECT

private slots:
    void proConfiguresAllSourceDirectories();
    void proListsActualFiles();
};

void ProFileIntegrationTest::proConfiguresAllSourceDirectories()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QFile proFile(repoRoot + "/Calculator.pro");
    QVERIFY(proFile.open(QIODevice::ReadOnly | QIODevice::Text));

    const QString contents = proFile.readAll();

    QVERIFY2(contents.contains("$$PWD/src"), "Calculator.pro must reference src directory");
    QVERIFY2(contents.contains("$$PWD/include"), "Calculator.pro must reference include directory");
    QVERIFY2(contents.contains("$$PWD/forms"), "Calculator.pro must reference forms directory");
    QVERIFY2(contents.contains("$$PWD/resources"), "Calculator.pro must reference resources directory");
    QVERIFY2(contents.contains("INCLUDEPATH"), "Calculator.pro must set INCLUDEPATH");
}

void ProFileIntegrationTest::proListsActualFiles()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QFile proFile(repoRoot + "/Calculator.pro");
    QVERIFY(proFile.open(QIODevice::ReadOnly | QIODevice::Text));
    const QString contents = proFile.readAll();

    QVERIFY2(contents.contains("main.cpp"), "Calculator.pro must list main.cpp");
    QVERIFY2(contents.contains("mainwindow.cpp"), "Calculator.pro must list mainwindow.cpp");
    QVERIFY2(contents.contains("mainwindow.h"), "Calculator.pro must list mainwindow.h");
    QVERIFY2(contents.contains("mainwindow.ui"), "Calculator.pro must list mainwindow.ui");
    QVERIFY2(contents.contains("resources.qrc"), "Calculator.pro must list resources.qrc");
}

QTEST_MAIN(ProFileIntegrationTest)
#include "test_profile_integration.moc"
