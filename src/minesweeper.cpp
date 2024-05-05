#include "include/minesweeper.h"

MineSweeper::MineSweeper(size_t N, size_t M, size_t num_mines, QWidget *parent)
    : N(N), M(M), num_mines(num_mines), num_revealed(0), QWidget(parent)
{
    this->gridLayout = new QGridLayout(this);
    this->gridLayout->setSpacing(0);
    this->setLayout(this->gridLayout);

    this->generateMines();

}

MineSweeper::~MineSweeper()
{

}

void MineSweeper::reset() {
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            this->gridLayout->removeWidget(this->gridLayout->itemAtPosition(i, j)->widget());
        }
    }

    this->generateMines();

}

void MineSweeper::generateMines()
{
    int mines = 0;
    while (mines < this->num_mines) {
        int i = rand() % this->N;
        int j = rand() % this->M;

        if (this->gridLayout->itemAtPosition(i, j) != nullptr) {
            continue;
        }

        Cell* cell = new Cell(i, j, -1, this);
        this->gridLayout->addWidget(cell, i, j);
        connect(cell, &Cell::revealedSignal, this, &MineSweeper::revealedSlot);

        mines++;
    }

     for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (this->gridLayout->itemAtPosition(i, j) != nullptr) {
                continue;
            }
            Cell* cell = new Cell(i, j, this->getNumber(i, j), this);
            this->gridLayout->addWidget(cell, i, j);
            connect(cell, &Cell::revealedSignal, this, &MineSweeper::revealedSlot);
        }
    }
}

size_t MineSweeper::getNumber(int i, int j)
{
    int number = 0;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x < 0 || x >= this->N || y < 0 || y >= this->M) {
                continue;
            }

            if (x == i && y == j) {
                continue;
            }

            if (this->gridLayout->itemAtPosition(x, y) == nullptr) {
                continue;
            }

            Cell* cell = dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(x, y)->widget());
            
            if (cell->isMine()) {
                number++;
            }
        }
    }

    return number;
}

void MineSweeper::revealNeighbors(int i, int j)
{
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x < 0 || x >= this->N || y < 0 || y >= this->M) {
                continue;
            }

            if (x == i && y == j) {
                continue;
            }

            Cell* cell = dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(x, y)->widget());
            
            if (cell->isRevealed() || cell->isMine())
            {
                continue;
            }
             cell->reveal();
        }
    }
}

void MineSweeper::revealedSlot(int i, int j)
{   
    Cell* cell = dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(i, j)->widget());
    if (cell->isMine()) {
        this->gameOver(false);
        return;
    }

    this->num_revealed++;
    emit this->scoreSignal(this->num_revealed);

    if (this->num_revealed == this->N * this->M - this->num_mines) {
        this->gameOver(true);
    }

    if (cell->isEmpty()) {
        this->revealNeighbors(i, j);
    }
}

void MineSweeper::hint()
{
    Cell* cell = dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(0, 0)->widget());
    cell->setHint();
}

void MineSweeper::gameOver(bool win)
{
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            Cell* cell = dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(i, j)->widget());
            if (cell->isRevealed()) {
                continue;
            }
            if (cell->isMine()) {
                cell->setMine();
            }

            cell->setDisabled(true);
            
        }
    }
    if (win) {
        QMessageBox msgBox;
        msgBox.setText("You win!");
        msgBox.exec();

    } else {
        QMessageBox msgBox;
        msgBox.setText("You lose!");
        msgBox.exec();
    }
}