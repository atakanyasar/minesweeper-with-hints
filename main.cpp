#include "include/minesweeper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineSweeper w(10, 10, 10);
    w.show();
    return a.exec();
}
