#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>

#include "include/cell.h"

class MineSweeper : public QWidget
{
    Q_OBJECT

public:
    MineSweeper(size_t N, size_t M, size_t num_mines, QWidget *parent = nullptr);
    ~MineSweeper();
    void generateMines();

private:
    size_t N;
    size_t M;
    size_t num_mines;
    QGridLayout* gridLayout;
    size_t getNumber(int i, int j);

public slots:
    void revealNeighborsSlot(int i, int j);

};
#endif // MINESWEEPER_H
