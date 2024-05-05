#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/assets/mine.png"));

    this->centralWidget = new QWidget(this);
    this->setCentralWidget(this->centralWidget);

    this->verticalLayout = new QVBoxLayout(this->centralWidget);
    this->centralWidget->setLayout(this->verticalLayout);

    this->scoreLabel = new QLabel("Score: 0");
    this->restartButton = new QPushButton("Restart");
    this->hintButton = new QPushButton("Hint");
    
    this->buttonsWidget = new QWidget(this->centralWidget);
    this->horizontalButtonLayout = new QHBoxLayout();

    this->horizontalButtonLayout->addWidget(this->scoreLabel);
    this->horizontalButtonLayout->addWidget(this->restartButton);
    this->horizontalButtonLayout->addWidget(this->hintButton);

    this->buttonsWidget->setLayout(this->horizontalButtonLayout);
    this->verticalLayout->addWidget(this->buttonsWidget);

    this->minesweeper = new MineSweeper(10, 10, 10);
    this->verticalLayout->addWidget(minesweeper);

    connect(this->minesweeper, &MineSweeper::scoreSignal, this, &MainWindow::updateScore);
    connect(this->restartButton, &QPushButton::clicked, this->minesweeper, &MineSweeper::reset);
    connect(this->hintButton, &QPushButton::clicked, this->minesweeper, &MineSweeper::hint);
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateScore(int score)
{
    this->scoreLabel->setText("Score: " + QString::number(score));
}