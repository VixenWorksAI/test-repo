#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_viewMenu(nullptr)
    , m_toolbarsSubMenu(nullptr)
    , m_toggleSidebar(nullptr)
    , m_toggleStatusbar(nullptr)
    , m_toggleMainToolbar(nullptr)
    , m_zoomIn(nullptr)
    , m_zoomOut(nullptr)
    , m_resetZoom(nullptr)
    , m_zoomPercent(kDefaultZoomPercent)
{
    ui->setupUi(this);
    setupViewMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupViewMenu()
{
    m_toggleSidebar = ui->actionToggle_Sidebar;
    m_toggleStatusbar = ui->actionToggle_Statusbar;
    m_toggleMainToolbar = ui->actionToggle_Main_Toolbar;
    m_zoomIn = ui->actionZoom_In;
    m_zoomOut = ui->actionZoom_Out;
    m_resetZoom = ui->actionReset_Zoom;

    QMenuBar *menuBar = ui->menubar;
    if (menuBar != nullptr) {
        m_viewMenu = menuBar->findChild<QMenu *>(QStringLiteral("menuView"));
    }

    if (m_viewMenu != nullptr) {
        m_toolbarsSubMenu = m_viewMenu->findChild<QMenu *>(QStringLiteral("menuToolbars"));
    }
}

QMenu *MainWindow::viewMenu() const
{
    return m_viewMenu;
}

QAction *MainWindow::actionToggleSidebar() const
{
    return m_toggleSidebar;
}

QAction *MainWindow::actionToggleStatusbar() const
{
    return m_toggleStatusbar;
}

QAction *MainWindow::actionToggleMainToolbar() const
{
    return m_toggleMainToolbar;
}

QAction *MainWindow::actionZoomIn() const
{
    return m_zoomIn;
}

QAction *MainWindow::actionZoomOut() const
{
    return m_zoomOut;
}

QAction *MainWindow::actionResetZoom() const
{
    return m_resetZoom;
}

bool MainWindow::isSidebarVisible() const
{
    return m_toggleSidebar != nullptr && m_toggleSidebar->isChecked();
}

bool MainWindow::isStatusBarVisible() const
{
    return m_toggleStatusbar != nullptr && m_toggleStatusbar->isChecked();
}

bool MainWindow::isMainToolbarVisible() const
{
    return m_toggleMainToolbar != nullptr && m_toggleMainToolbar->isChecked();
}

int MainWindow::currentZoomPercent() const
{
    return m_zoomPercent;
}

QList<QMenu *> MainWindow::topLevelMenus() const
{
    QList<QMenu *> menus;
    if (ui->menubar == nullptr) {
        return menus;
    }
    const QList<QAction *> actions = ui->menubar->actions();
    for (QAction *action : actions) {
        if (action == nullptr) {
            continue;
        }
        QMenu *menu = action->menu();
        if (menu != nullptr) {
            menus.append(menu);
        }
    }
    return menus;
}

bool MainWindow::hasUniqueMenuTitles() const
{
    QSet<QString> titles;
    const QList<QMenu *> menus = topLevelMenus();
    for (const QMenu *menu : menus) {
        if (menu == nullptr) {
            continue;
        }
        if (menu->title().isEmpty()) {
            return false;
        }
        if (titles.contains(menu->title())) {
            return false;
        }
        titles.insert(menu->title());
    }
    return !titles.isEmpty();
}

QLineEdit *MainWindow::displayEdit() const
{
    return ui->displayEdit;
}

void MainWindow::on_actionToggle_Sidebar_triggered()
{
}

void MainWindow::on_actionToggle_Statusbar_triggered()
{
    if (m_toggleStatusbar == nullptr || ui->statusbar == nullptr) {
        return;
    }
    ui->statusbar->setVisible(m_toggleStatusbar->isChecked());
}

void MainWindow::on_actionToggle_Main_Toolbar_triggered()
{
}

void MainWindow::on_actionZoom_In_triggered()
{
    applyZoom(m_zoomPercent + kZoomStepPercent);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    applyZoom(m_zoomPercent - kZoomStepPercent);
}

void MainWindow::on_actionReset_Zoom_triggered()
{
    applyZoom(kDefaultZoomPercent);
}

void MainWindow::on_actionAbout_triggered()
{
    emit aboutDialogRequested();
}

void MainWindow::on_actionDocumentation_triggered()
{
    emit documentationRequested();
}

void MainWindow::applyZoom(int percent)
{
    if (percent < kMinZoomPercent) {
        percent = kMinZoomPercent;
    }
    if (percent > kMaxZoomPercent) {
        percent = kMaxZoomPercent;
    }
    m_zoomPercent = percent;
}
