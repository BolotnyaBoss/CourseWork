#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
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
    QString word = ui->lineEdit->text(), output = "Lines that contains input word:\n";
    if(ui->radioButton->isChecked()){
        QStringList list = (song->getSongText())[ui->spinBox->text().toInt()-1].getTextOfCouplet().split(QRegExp("\r\n"));
        for(int i = 0; i < list.size(); i++)
            if(list[i].contains(word, Qt::CaseInsensitive)) output += list[i]+"\n";
    }
    if(ui->radioButton_2->isChecked()){
        QStringList list;
        for(int i = 0; i<song->getCountOfCouplets();i++){
            list = (song->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
            for(int j = 0; j < list.size(); j++)
                if(list[j].contains(word, Qt::CaseInsensitive)) output += (j == list.size()-1)?list[j]:list[j]+"\n";
        }
    }
    if(output == "Lines that contains input word:\n"){
        QMessageBox msgBox;
        msgBox.setText("Not found input word");
        msgBox.exec();
        output = "Not found input word\n";
    }
    QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(output);
        ui->listWidget_2->addItem(newItem);
}

void MainWindow::on_pushButton_2_clicked()//change line of couplet
{
    QString text = ui->lineEdit_2->text();
    QStringList list = (song->getSongText())[ui->spinBox_2->text().toInt()-1].getTextOfCouplet().split(QRegExp("\r\n"));
    list[ui->spinBox_3->text().toInt()] = (ui->spinBox_3->text().toInt() == list.size()-1)?text+"\n":text;
    (song->getSongText())[ui->spinBox_2->text().toInt()-1].setTextOfCouplet(list.join("\r\n"));
    ui->listWidget->clear();
    ui->listWidget<<*song;
}

void MainWindow::on_pushButton_3_clicked()//swap two lines
{
    QString line1,line2;
    if(ui->spinBox_4->text().toInt() == ui->spinBox_6->text().toInt())
    {
        Couplet c1 = (song->getSongText())[ui->spinBox_4->text().toInt()-1];
        QStringList list1 = (c1.getTextOfCouplet()).split(QRegExp("\r\n"));
        line1 = list1[ui->spinBox_5->text().toInt()];
        list1[ui->spinBox_5->text().toInt()] = line2;
        list1[ui->spinBox_7->text().toInt()] = line1;
        (song->getSongText())[ui->spinBox_4->text().toInt()-1].setTextOfCouplet(list1.join("\r\n"));
    }
    else
    {
        Couplet c1 = (song->getSongText())[ui->spinBox_4->text().toInt()-1];
        Couplet c2 = (song->getSongText())[ui->spinBox_6->text().toInt()-1];
        QStringList list1 = (c1.getTextOfCouplet()).split(QRegExp("\r\n"));
        QStringList list2 = (c2.getTextOfCouplet()).split(QRegExp("\r\n"));
        line1 = list1[ui->spinBox_5->text().toInt()];
        line2 = list2[ui->spinBox_7->text().toInt()];
        list1[ui->spinBox_5->text().toInt()] = line2;
        list2[ui->spinBox_7->text().toInt()] = line1;
        (song->getSongText())[ui->spinBox_4->text().toInt()-1].setTextOfCouplet(list1.join("\r\n"));
        (song->getSongText())[ui->spinBox_6->text().toInt()-1].setTextOfCouplet(list2.join("\r\n"));
    }
    ui->listWidget->clear();
    ui->listWidget<<*song;
}

void MainWindow::on_pushButton_4_clicked()//print last lines of every couplet
{
    QString output = "Current last lines of song:\n";
    QStringList list;
    for(int i = 0; i<song->getCountOfCouplets();i++){
        list = (song->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
        if(i == ui->spinBox_3->text().toInt()-1)output += (QString)list.takeLast()+"\r\n";
        else output += (QString)list.takeLast();
    }
    QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(output);
        ui->listWidget_2->addItem(newItem);
}

void MainWindow::on_pushButton_5_clicked()//is sonnet?
{
    QVector<int> arr;
    QStringList list;
    int sum = 0;
    QString result = "";
    if(song->getCountOfCouplets()>1 && song->getCountOfCouplets()<5){
        for(int i = 0; i<song->getCountOfCouplets();i++){
            list = (song->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
            arr.push_back(list.size());
        }
        for(int i = 0; i<arr.size(); i++)
            sum += arr[i];
        if(sum == 14 && arr.size() == 4 &&(arr[0] == 4 && arr[1] == 4 && arr[2] == 3 && arr[3] == 3))
            result = "It's sonnet!";
        else if(sum == 10 && arr.size() == 3 &&(arr[0] == 4 && arr[1] == 3 && arr[2] == 3))
            result = "It's headless sonnet!";
        else if(sum == 7 && arr.size() == 2 &&(arr[0] == 4 && arr[1] == 3))
            result = "It's halfsonnet!";
        else result = "It's not sonnet!";
    }
    QMessageBox msgBox;
                msgBox.setText(result);
                msgBox.exec();
    ui->label_10->setText(result);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open some file");

       try {
           song->readFromFile(fileName);
       } catch (OpenFileException& error){
           QMessageBox::warning(this, "File Openning Error", error.what());
           return;
       }
    file = fileName;
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
           QMessageBox::warning(this, "File Saving Error", error.what());
           return;
       }
}

void MainWindow::on_actionSave_As_triggered()
{
    try {
            QString fileName = QFileDialog::getSaveFileName(this, "Save as");
            song->saveToFile(fileName);
        } catch (SaveFileException& error) {
            QMessageBox::warning(this, "File Saving Error", error.what());
            return;
        }
}

void MainWindow::on_actionExit_triggered()
{
    if(!song->getIsSaved()){
            QMessageBox warning;
            warning.setWindowTitle("Closing application");
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
}}
