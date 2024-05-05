#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(0);
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();
    return a.exec();
}
