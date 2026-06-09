#include <QtTest>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSizePolicy>

#include "mainwindow.h"
#include "test_placeholder_responsiveness_unit.h"

void TestPlaceholderResponsivenessUnit::gridHasEqualColumnStretches()
{
    MainWindow window;
    QGridLayout *grid = window.findChild<QGridLayout *>(QStringLiteral("keypadGridLayout"));
    QVERIFY2(grid != nullptr, "keypadGridLayout must exist");

    for (int column = 0; column < grid->columnCount(); ++column) {
        QCOMPARE(grid->columnStretch(column), 1);
    }
}

void TestPlaceholderResponsivenessUnit::gridHasEqualRowStretches()
{
    MainWindow window;
    QGridLayout *grid = window.findChild<QGridLayout *>(QStringLiteral("keypadGridLayout"));
    QVERIFY2(grid != nullptr, "keypadGridLayout must exist");

    for (int row = 0; row < grid->rowCount(); ++row) {
        QCOMPARE(grid->rowStretch(row), 1);
    }
}

void TestPlaceholderResponsivenessUnit::gridHasPerColumnMinimumWidths()
{
    MainWindow window;
    QGridLayout *grid = window.findChild<QGridLayout *>(QStringLiteral("keypadGridLayout"));
    QVERIFY2(grid != nullptr, "keypadGridLayout must exist");
    QVERIFY(grid->columnCount() >= 4);

    for (int column = 0; column < 4; ++column) {
        QVERIFY2(grid->columnMinimumWidth(column) >= 60,
                 "Column minimum width must be at least 60px to keep buttons usable");
    }
}

void TestPlaceholderResponsivenessUnit::gridHasPerRowMinimumHeights()
{
    MainWindow window;
    QGridLayout *grid = window.findChild<QGridLayout *>(QStringLiteral("keypadGridLayout"));
    QVERIFY2(grid != nullptr, "keypadGridLayout must exist");
    QVERIFY(grid->rowCount() >= 4);

    for (int row = 0; row < 4; ++row) {
        QVERIFY2(grid->rowMinimumHeight(row) >= 48,
                 "Row minimum height must be at least 48px to keep buttons usable");
    }
}

void TestPlaceholderResponsivenessUnit::centralLayoutEnforcesMinimumSizeConstraint()
{
    MainWindow window;
    QBoxLayout *central = window.findChild<QBoxLayout *>(QStringLiteral("centralLayout"));
    QVERIFY2(central != nullptr, "centralLayout must exist");
    QCOMPARE(central->sizeConstraint(), QLayout::SetMinimumSize);
}

void TestPlaceholderResponsivenessUnit::placeholderButtonsAreExpanding()
{
    MainWindow window;
    const QList<QPushButton *> buttons = window.findChildren<QPushButton *>();
    QVERIFY2(buttons.size() >= 16, "All 16 keypad placeholders must be present");

    for (QPushButton *button : buttons) {
        const QSizePolicy policy = button->sizePolicy();
        const bool horizontalExpanding =
            policy.horizontalPolicy() == QSizePolicy::Expanding
            || policy.horizontalPolicy() == QSizePolicy::Preferred;
        const bool verticalExpanding =
            policy.verticalPolicy() == QSizePolicy::Expanding
            || policy.verticalPolicy() == QSizePolicy::Preferred;
        QVERIFY2(horizontalExpanding,
                 "Placeholder button must use an expanding horizontal policy");
        QVERIFY2(verticalExpanding,
                 "Placeholder button must use an expanding vertical policy");
    }
}

void TestPlaceholderResponsivenessUnit::displayIsExpanding()
{
    MainWindow window;
    QLineEdit *display = window.findChild<QLineEdit *>(QStringLiteral("displayEdit"));
    QVERIFY2(display != nullptr, "displayEdit must exist");

    const QSizePolicy policy = display->sizePolicy();
    QVERIFY(policy.horizontalPolicy() == QSizePolicy::Expanding
            || policy.horizontalPolicy() == QSizePolicy::Preferred);
}
