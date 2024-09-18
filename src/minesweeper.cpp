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

    this->num_revealed = 0;
    emit this->scoreSignal(0);

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

Cell* MineSweeper::getCell(int i, int j)
{
    return dynamic_cast<Cell*>(this->gridLayout->itemAtPosition(i, j)->widget());
}

std::vector<std::pair<int, int>> MineSweeper::getNeighbors(int i, int j, std::function<bool(int, int)> filter)
{
    std::vector<std::pair<int, int>> cells;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x < 0 || x >= this->N || y < 0 || y >= this->M) {
                continue;
            }

            if (x == i && y == j) {
                continue;
            }

            if (filter(x, y) == false) {
                continue;
            }

            cells.push_back(std::make_pair(x, y));
        }
    }

    return cells;
}

size_t MineSweeper::getNumber(int i, int j)
{
    return getNeighbors(i, j, [this](int x, int y) {
        return this->gridLayout->itemAtPosition(x, y) != nullptr && getCell(x, y)->isMine();
    }).size();
}

void MineSweeper::revealNeighbors(int i, int j)
{
    for (auto [x, y] : getNeighbors(i, j)) {

        Cell* cell = getCell(x, y);
        
        if (cell->isRevealed() || cell->isMine())
        {
            continue;
        }

        cell->reveal();   
    }
}

void MineSweeper::revealedSlot(int i, int j)
{   
    Cell* cell = getCell(i, j);
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

int MineSweeper::getNumAdjacentReveals(int i, int j)
{
    return getNeighbors(i, j, [this](int x, int y) {
        return getCell(x, y)->isRevealed();
    }).size();
}

void MineSweeper::hint()
{
    bool activeHint = false;
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            if (getCell(i, j)->isRevealed()) {
                continue;
            }
            if (getCell(i, j)->isHint()) {
                getCell(i, j)->reveal();
                activeHint = true;
            }
        }
    }

    if (activeHint) {
        return;
    }

    std::vector<std::vector<bool>> mineDetected(this->N, std::vector<bool>(this->M, false));

    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            if (getCell(i, j)->isRevealed() == false) {
                continue;
            }
            
            int unreveals = 8 - getNumAdjacentReveals(i, j);
            
            if (unreveals != getNumber(i, j)) {
                continue;
            }

            getNeighbors(i, j, [&](int x, int y) {
                if (getCell(x, y)->isRevealed() == false) {
                    mineDetected[x][y] = true;
                }
                return true;
            });
        }
    }

    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            if (getCell(i, j)->isRevealed() == false) {
                continue;
            }

            if (mineDetected[i][j]) {
                continue;
            }

            int mines = getNeighbors(i, j, [&](int x, int y) {
                return mineDetected[x][y];
            }).size();

            if (getNumber(i, j) != mines) {
                continue;
            }

            auto hintCells = getNeighbors(i, j, [&](int x, int y) {
                return mineDetected[x][y] == false && getCell(x, y)->isRevealed() == false;
            });

            for (auto [x, y] : hintCells) {
                getCell(x, y)->setHint();
            }
        }
    }

}

void MineSweeper::gameOver(bool win)
{
    for (int i = 0; i < this->N; i++) {
        for (int j = 0; j < this->M; j++) {
            Cell* cell = getCell(i, j);
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