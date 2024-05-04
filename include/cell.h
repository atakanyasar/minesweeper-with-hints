#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton
{
    Q_OBJECT

public:

    Cell(int row, int col, size_t number, QWidget* parent = nullptr);
    ~Cell();

    int row;
    int col;

    void setEmpty();
    void setMine();
    void setFlag();
    void setNumber();

    bool isMine() const;
    bool isRevealed() const;
    bool isEmpty() const;

    void reveal();
    void toggleFlag();

private:

    bool mine;
    bool flag;
    bool revealed;
    bool hint;
    size_t number;

signals:
    void revealNeighborsSignal(int i, int j);


};

#endif // CELL_H