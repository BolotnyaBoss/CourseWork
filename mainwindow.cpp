#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
bool openfile = false;
QString file = "";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    song = new Song();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//find word
{
    if(openfile){
        if(ui->lineEdit->text().isEmpty() || !((ui->radioButton->isChecked() && ui->spinBox->text().toInt())|| ui->radioButton_2->isChecked() ))
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Enter data corectly");
            msgBox.exec();
            return;
        }
        QString word = ui->lineEdit->text(), output = "Lines that contains input word << "+word+">>:\n";
        int count = 0;
        if(ui->radioButton->isChecked())
        {
            if(ui->spinBox->text().toInt()<=song->getCountOfCouplets())
            {
                output += song->findWordInCouplet(word, ui->spinBox->text().toInt()-1, &count);
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Incorect input data");
                msgBox.exec();
                return;
            }
        }
        if(ui->radioButton_2->isChecked()){
            output += song->findWordInSong(word, &count);
        }
        if(!count){
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Not found input word");
            msgBox.exec();
        }
        QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(output);
            ui->listWidget_2->addItem(newItem);
            QString message = "Program found " +QString::number(count)+ " words";
            ui->statusbar->showMessage(message);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Firstly read data from file");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()//change line of couplet
{
    if(openfile)
    {
        if(ui->lineEdit_2->text().isEmpty()|| ui->spinBox_2->text().toInt() == 0|| ui->spinBox_3->text().toInt() == 0)
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Incorect input data");
            msgBox.exec();
            return;
        }
        if(ui->spinBox_2->text().toInt()<=song->getCountOfCouplets())
        {
            QString text = ui->lineEdit_2->text();
            song->changeLineInCouplet(text,ui->spinBox_2->text().toInt()-1,ui->spinBox_3->text().toInt());
            ui->listWidget->clear();
            ui->listWidget<<*song;
            ui->statusbar->showMessage("Line was written");
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Incorect input data");
            msgBox.exec();
            return;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Firstly read data from file");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_3_clicked()//swap two lines
{
    if(openfile)
    {
        if(ui->spinBox_4->text().toInt()<=song->getCountOfCouplets() && ui->spinBox_6->text().toInt()<=song->getCountOfCouplets())
        {
            if(ui->spinBox_4->text().toInt() != 0  && ui->spinBox_6->text().toInt() != 0)
            {
                song->swapTwoCoupets(ui->spinBox_4->text().toInt()-1,ui->spinBox_6->text().toInt()-1);
                ui->listWidget->clear();
                ui->listWidget<<*song;
                }
            else{
                QMessageBox msgBox;
                msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Enter please data");
                msgBox.exec();
                return;
            }
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Incorect input data");
            msgBox.exec();
            return;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Firstly read data from file");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_4_clicked()//print last lines of every couplet
{
    if(openfile)
    {
    QString output = "Current last lines of song:\n";
    output += song->printLastLines(ui->spinBox_3->text().toInt()-1);
    QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(output);
        ui->listWidget_2->addItem(newItem);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Firstly read data from file");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_5_clicked()//is sonnet?
{
    if(openfile)
    {
    QString result = song->typeOfSonnet();
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(result);
    msgBox.exec();
    ui->label_10->setText(result);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Firstly read data from file");
        msgBox.exec();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open some file");

       try {
           song->readFromFile(fileName);
           ui->statusbar->showMessage("Data was readed from file");
       } catch (OpenFileException& error){
           QMessageBox::critical(this, "File Openning Error", error.what());
           return;
       }
    file = fileName;
    openfile = true;
    ui->listWidget->clear();
    ui->listWidget<<*song;


}

void MainWindow::on_actionSave_triggered()
{
    try {
           if(song->getIsSaved()){
               song->saveToFile(file);
           } else {
               on_actionSave_As_triggered();
           }
       } catch (SaveFileException& error) {
           QMessageBox::critical(this, "File Saving Error", error.what());
           return;
       }
}

void MainWindow::on_actionSave_As_triggered()
{
    try {
            QString fileName = QFileDialog::getSaveFileName(this, "Save as");
            file = fileName;
            song->saveToFile(fileName);
            ui->statusbar->showMessage("Data was saved");
        } catch (SaveFileException& error) {
            QMessageBox::critical(this, "File Saving Error", error.what());
            return;
        }
}

void MainWindow::on_actionExit_triggered()
{
    if(!song->getIsSaved()){
            QMessageBox warning;
            warning.setWindowTitle("Closing application");
            warning.setWindowIcon(QIcon("D:\\Qt projects\\Kursova\\my_logo.jpg"));
            warning.setIcon(QMessageBox::Warning);
            warning.setText("You forgot to save data.\n"
                            "Do you want exit without saving?");
            warning.setStandardButtons(QMessageBox::No |
                                       QMessageBox::Yes);

            int result = warning.exec();

            if(result == QMessageBox::Yes){
                close();
            } else if(result == QMessageBox::No) {
                on_actionSave_triggered();
            }
     }
    else close();
}
