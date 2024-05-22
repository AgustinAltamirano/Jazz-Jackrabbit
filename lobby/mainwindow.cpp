#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newGameButton_clicked()
{

}


void MainWindow::on_joinGameButton_clicked()
{

}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}
