#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QAction;
class QMenu;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMenu *viewMenu() const;
    QAction *actionToggleSidebar() const;
    QAction *actionToggleStatusbar() const;
    QAction *actionToggleMainToolbar() const;
    QAction *actionZoomIn() const;
    QAction *actionZoomOut() const;
    QAction *actionResetZoom() const;

    bool isSidebarVisible() const;
    bool isStatusBarVisible() const;
    bool isMainToolbarVisible() const;
    int currentZoomPercent() const;

    QList<QMenu *> topLevelMenus() const;
    bool hasUniqueMenuTitles() const;

    QLineEdit *displayEdit() const;

signals:
    void aboutDialogRequested();
    void documentationRequested();

private slots:
    void on_actionToggle_Sidebar_triggered();
    void on_actionToggle_Statusbar_triggered();
    void on_actionToggle_Main_Toolbar_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionReset_Zoom_triggered();
    void on_actionAbout_triggered();
    void on_actionDocumentation_triggered();

private:
    void setupViewMenu();
    void applyZoom(int percent);

    Ui::MainWindow *ui;
    QMenu *m_viewMenu;
    QMenu *m_toolbarsSubMenu;
    QAction *m_toggleSidebar;
    QAction *m_toggleStatusbar;
    QAction *m_toggleMainToolbar;
    QAction *m_zoomIn;
    QAction *m_zoomOut;
    QAction *m_resetZoom;
    int m_zoomPercent;

    static constexpr int kDefaultZoomPercent = 100;
    static constexpr int kZoomStepPercent = 10;
    static constexpr int kMinZoomPercent = 50;
    static constexpr int kMaxZoomPercent = 400;
};

#endif
