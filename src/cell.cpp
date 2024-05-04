#include "include/cell.h"

Cell::Cell(int row, int col, size_t number, QWidget* parent)
    : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->row = row;
    this->col = col;

    this->mine = (number == -1);
    this->flag = false;
    this->revealed = false;
    this->hint = false;
    this->number = number;

    connect(this, &QPushButton::clicked, this, &Cell::reveal);
    // connect(this, &QPushButton::rightClicked, this, &Cell::toggleFlag);

}

Cell::~Cell()
{

}

bool Cell::isMine() const
{
    return this->mine;
}

bool Cell::isRevealed() const
{
    return this->revealed;
}

bool Cell::isEmpty() const
{
    return this->number == 0;
}

void Cell::reveal()
{
    if (this->revealed) {
        return;
    }
    
    this->revealed = true;

    if (this->mine) {
        this->setMine();
    } else {
        this->setNumber();
    }
}

void Cell::toggleFlag()
{
    if (this->revealed) {
        return;
    }

    if (this->flag) {
        this->flag = false;
        this->setEmpty();
    } else {
        this->flag = true;
        this->setFlag();
    }
}

void Cell::setEmpty()
{
    this->setStyleSheet("border-image:url(:/assets/0.png);");
}

void Cell::setMine()
{
    this->setStyleSheet("border-image:url(:/assets/mine.png);");
}

void Cell::setFlag()
{
    this->setStyleSheet("border-image:url(:/assets/flag.png);");
}

void Cell::setNumber()
{
    assert (this->number >= 0 && this->number <= 8);

    if (this->number == 0) {
        this->setEmpty();
        emit revealNeighborsSignal(this->row, this->col);
    } else {
        std::string path = ":/assets/" + std::to_string(this->number) + ".png";
        const QString filename = QString::fromStdString(path);
        this->setStyleSheet("border-image:url(" + filename + ");");
    }
    
    this->blockSignals(true);
}