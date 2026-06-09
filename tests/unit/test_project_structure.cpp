#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QtTest/QtTest>

class ProjectStructureTest : public QObject
{
    Q_OBJECT

private slots:
    void directoryStructureExists();
    void calculatorProExists();
    void proFileReferencesAllDirectories();
    void qmakeGeneratesMakefile();
};

void ProjectStructureTest::directoryStructureExists()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QDir src(repoRoot + "/src");
    QDir include(repoRoot + "/include");
    QDir resources(repoRoot + "/resources");
    QDir forms(repoRoot + "/forms");

    QVERIFY2(src.exists(), "src directory missing");
    QVERIFY2(include.exists(), "include directory missing");
    QVERIFY2(resources.exists(), "resources directory missing");
    QVERIFY2(forms.exists(), "forms directory missing");
}

void ProjectStructureTest::calculatorProExists()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QFile proFile(repoRoot + "/Calculator.pro");
    QVERIFY2(proFile.exists(), "Calculator.pro file missing");
    QVERIFY(proFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QVERIFY(proFile.size() > 0);
}

void ProjectStructureTest::proFileReferencesAllDirectories()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QFile proFile(repoRoot + "/Calculator.pro");
    QVERIFY(proFile.open(QIODevice::ReadOnly | QIODevice::Text));
    const QString contents = proFile.readAll();

    QVERIFY2(contents.contains("SOURCES"), "Calculator.pro missing SOURCES section");
    QVERIFY2(contents.contains("HEADERS"), "Calculator.pro missing HEADERS section");
    QVERIFY2(contents.contains("RESOURCES"), "Calculator.pro missing RESOURCES section");
    QVERIFY2(contents.contains("FORMS"), "Calculator.pro missing FORMS section");
}

void ProjectStructureTest::qmakeGeneratesMakefile()
{
    const QString repoRoot = QCoreApplication::applicationDirPath() + "/../..";
    QDir buildDir(repoRoot + "/build");
    if (!buildDir.exists()) {
        buildDir.mkdir(".");
    }

    const int exitCode = QProcess::execute("qmake6", QStringList() << repoRoot + "/Calculator.pro"
                                                                    << "-o" << repoRoot + "/build/Makefile");
    QFile makefile(repoRoot + "/build/Makefile");
    Q_UNUSED(exitCode);
    QVERIFY2(makefile.exists() || QFile::exists(repoRoot + "/build-build/Makefile"), "Makefile not generated");
}

QTEST_MAIN(ProjectStructureTest)
#include "test_project_structure.moc"
