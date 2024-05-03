#include "include/minesweeper.h"

MineSweeper::MineSweeper(size_t N, size_t M, size_t num_mines, QWidget *parent)
    : N(N), M(M), num_mines(num_mines), QWidget(parent)
{
    gridLayout = new QGridLayout(this);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            gridLayout->addWidget(new QPushButton(this), i, j);
        }
    }

}

MineSweeper::~MineSweeper()
{

}

