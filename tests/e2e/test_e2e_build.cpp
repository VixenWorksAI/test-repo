#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QtTest/QtTest>

class E2EBuildTest : public QObject
{
    Q_OBJECT

private slots:
    void projectBuildsSuccessfully();
};

void E2EBuildTest::projectBuildsSuccessfully()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QDir buildDir(repoRoot + "/build");
    if (buildDir.exists()) {
        buildDir.removeRecursively();
    }
    buildDir.mkdir(".");

    QProcess qmake;
    qmake.setWorkingDirectory(buildDir.absolutePath());
    qmake.start("qmake6", QStringList() << repoRoot + "/Calculator.pro");
    QVERIFY2(qmake.waitForStarted(30000), "Failed to start qmake6");
    QVERIFY2(qmake.waitForFinished(60000), "qmake6 timed out");
    QVERIFY2(qmake.exitCode() == 0, "qmake6 did not exit cleanly");

    QVERIFY(QFile::exists(buildDir.absoluteFilePath("Makefile")));

    QProcess make;
    make.setWorkingDirectory(buildDir.absolutePath());
    const int cores = QThread::idealThreadCount();
    make.start("make", QStringList() << "-j" << QString::number(cores > 0 ? cores : 1));
    QVERIFY2(make.waitForStarted(30000), "Failed to start make");
    QVERIFY2(make.waitForFinished(300000), "make timed out");
    QVERIFY2(make.exitCode() == 0, "make did not exit cleanly");
}

QTEST_MAIN(E2EBuildTest)
#include "test_e2e_build.moc"
