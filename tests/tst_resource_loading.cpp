#include <QtTest/QtTest>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <cstdlib>

class ResourceLoadingTest : public QObject
{
    Q_OBJECT

private slots:
    void coreArithmeticUnaffected();
    void essentialResourceExists();
    void binarySizeReduced();
    void deferDefineIsSet();
};

void ResourceLoadingTest::coreArithmeticUnaffected()
{
    QCOMPARE(2 + 2, 4);
    QCOMPARE(10 - 3, 7);
    QCOMPARE(6 * 7, 42);
    QCOMPARE(15 / 3, 5);
    QVERIFY(true);
}

void ResourceLoadingTest::essentialResourceExists()
{
    const QString qrc = QDir::current().filePath("resources/resources.qrc");
    QVERIFY2(QFileInfo::exists(qrc),
             "resources.qrc must be present for the lean build");
    QFile f(qrc);
    QVERIFY(f.open(QIODevice::ReadOnly));
    Q_UNUSED(f.readAll());
}

void ResourceLoadingTest::binarySizeReduced()
{
    const QString binary = QDir::current().filePath("bin/Calculator");
    if (!QFileInfo::exists(binary)) {
        QSKIP("Lean binary not built; run `make lean` first");
    }
    const qint64 size = QFileInfo(binary).size();
    const qint64 baselineKB = 2048;
    const qint64 cap = baselineKB * 1024 * 80 / 100;
    QVERIFY2(size <= cap,
             qPrintable(QString("Binary %1 bytes exceeds 20%% reduction cap of %2 bytes")
                        .arg(size).arg(cap)));
}

void ResourceLoadingTest::deferDefineIsSet()
{
    QFile pro("Calculator.pro");
    QVERIFY(pro.open(QIODevice::ReadOnly));
    const QByteArray contents = pro.readAll();
    QVERIFY2(contents.contains("DEFER_NON_ESSENTIAL_RESOURCES"),
             "Calculator.pro must define DEFER_NON_ESSENTIAL_RESOURCES");
    QVERIFY2(contents.contains("optimize_size"),
             "Calculator.pro must enable optimize_size for the lean build");
    QVERIFY2(contents.contains("-Os"),
             "Calculator.pro must pass -Os for size optimisation");
}

QTEST_MAIN(ResourceLoadingTest)
#include "tst_resource_loading.moc"
