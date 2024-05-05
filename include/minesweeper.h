#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>

#include "include/cell.h"

class MineSweeper : public QWidget
{
    Q_OBJECT

public:
    MineSweeper(size_t N, size_t M, size_t num_mines, QWidget *parent = nullptr);
    ~MineSweeper();
    void reset();
    void generateMines();
    void hint();
    void gameOver(bool win);

private:
    size_t N;
    size_t M;
    size_t num_mines;
    size_t num_revealed;
    QGridLayout* gridLayout;
    size_t getNumber(int i, int j);
    void revealNeighbors(int i, int j);

signals:
    void scoreSignal(int score);

public slots:
    void revealedSlot(int i, int j);

};
#endif // MINESWEEPER_H
