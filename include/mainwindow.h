#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLayout>
#include <QLabel>

#include "include/minesweeper.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget* centralWidget;
    QLayout* verticalLayout;
    QWidget* buttonsWidget;
    QLayout* horizontalButtonLayout;
    MineSweeper* minesweeper;
    QLabel* scoreLabel;
    QPushButton* restartButton;
    QPushButton* hintButton;

public slots:
    void updateScore(int score);
};

#endif // MAINWINDOW_H