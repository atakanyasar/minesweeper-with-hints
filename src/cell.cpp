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

    this->setEmpty();

}

Cell::~Cell()
{

}

void Cell::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        this->reveal();
    } 
    if (event->button() == Qt::RightButton) {
        this->toggleFlag();
    }
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
    emit revealedSignal(this->row, this->col);
    this->blockSignals(true);
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
    this->setStyleSheet("border-image:url(:/assets/empty.png);");
}

void Cell::setMine()
{
    this->setStyleSheet("border-image:url(:/assets/mine.png);");
}

void Cell::setFlag()
{
    this->setStyleSheet("border-image:url(:/assets/flag.png);");
}

void Cell::setHint()
{
    this->setStyleSheet("border-image:url(:/assets/hint.png);");
}

void Cell::setNumber()
{
    assert (this->number >= 0 && this->number <= 8);

    std::string path = ":/assets/" + std::to_string(this->number) + ".png";
    const QString filename = QString::fromStdString(path);
    this->setStyleSheet("border-image:url(" + filename + ");");
}