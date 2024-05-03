#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class MineSweeper : public QWidget
{
    Q_OBJECT

public:
    MineSweeper(size_t N, size_t M, size_t num_mines, QWidget *parent = nullptr);
    ~MineSweeper();

private:
    size_t N;
    size_t M;
    size_t num_mines;
    QGridLayout* gridLayout;

};
#endif // MINESWEEPER_H
