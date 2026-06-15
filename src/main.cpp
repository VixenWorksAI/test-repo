#include <QApplication>
#include <QTimer>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    QTimer::singleShot(0, &window, &MainWindow::deferredInitialization);

    return app.exec();
}
