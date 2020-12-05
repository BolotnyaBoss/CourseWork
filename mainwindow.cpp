#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()//find word
{

}

void MainWindow::on_pushButton_2_clicked()//change line of couplet
{

}

void MainWindow::on_pushButton_3_clicked()//swap two lines
{

}

void MainWindow::on_pushButton_4_clicked()//print last lines of every couplet
{

}

void MainWindow::on_pushButton_5_clicked()//is sonnet?
{

}
