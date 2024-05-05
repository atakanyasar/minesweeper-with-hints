#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QMouseEvent>

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
    void setHint();
    void setNumber();

    bool isMine() const;
    bool isRevealed() const;
    bool isEmpty() const;

    void reveal();
    void toggleFlag();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool mine;
    bool flag;
    bool revealed;
    bool hint;
    size_t number;

signals:
    void revealedSignal(int i, int j);


};

#endif // CELL_H