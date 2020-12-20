#include "song.h"
#include "OpenFileException.h"
#include "SaveFileException.h"
void Song::readFromFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        throw OpenFileException();
    }
    QTextStream in(&file);
    in >> (*this);
    isSaved = false;
    file.close();
}
void Song::saveToFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        throw SaveFileException();
    }
    QTextStream out(&file);
    out << *(this);
    isSaved = true;
    file.close();

}
QTextStream &operator<<(QTextStream &out, Song &song)
{
    out<<"Name:"<<song.name<<"\n";
    out<<"Author:"<<song.author<<"\n";
    for(int i = 0; i < song.getCountOfCouplets(); i++)
    {
        out<<"Couplet:"<<i+1<<"\n"<<song.songText[i].getTextOfCouplet();
    }
    return out;
}

QTextStream &operator>>(QTextStream &in, Song &song)
{
    QString text = in.readAll();
    QStringList coupletList = text.split(QRegExp("Couplet:[0-9]+"), QString::SkipEmptyParts);
    for (int i = 0; i < coupletList.size();i++) {
        if(i){
        Couplet temp;
        QString tmp = coupletList[i];
        //QString deletestr = QString::number(i)+"\n";
        //tmp.remove(deletestr);
        temp.setTextOfCouplet(tmp);
        temp.setnumberOfCouplet(i);
        song.songText.push_back(temp);}
        else{
            QStringList list = coupletList[0].split(QRegExp("\n"), QString::SkipEmptyParts);
            for (int j = 0; j < list.size();j++) {
                if(j==1){
                    QString author = list[j];
                    author.remove("Author:");
                    song.setAuthor(author);
                }
                if(!j){
                    QString name = list[j];
                    name.remove("Name:");
                    song.setName(name);
                }
            }
        }
    }
    song.setCountOfCouplets(coupletList.size()-1);
    song.isSaved = true;
    return in;
}
void operator<<(QListWidget *listWidget, Song &song){
    QString output = "";
    output+="Name:"+song.getName()+"\n";
    output+="Author:"+song.getAuthor()+"\n";
    for(int i = 0; i < song.getCountOfCouplets(); i++)
    {
        output+="Couplet:"+QString::number(i+1)+(song.getSongText())[i].getTextOfCouplet();
    }
    QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(output.toLocal8Bit());
        listWidget->addItem(newItem);
}
QString Song::findWordInCouplet(QString word, int numOfCouplet, int* count)
{
    QString output = "";
    QStringList list = (this->getSongText())[numOfCouplet].getTextOfCouplet().split(QRegExp("\r\n"));
    for(int i = 0; i < list.size(); i++)
        if(list[i].contains(word, Qt::CaseInsensitive)){ output += list[i]+"\n"; (*count)++;}
    if(output == ""){
        output = "Not found input word\n";
    }
    return output;
}

QString Song::findWordInSong(QString word, int* count)
{
    QString output = "";
    QStringList list;
    for(int i = 0; i<this->getCountOfCouplets();i++)
    {
        list = (this->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
        for(int j = 0; j < list.size(); j++)
            if(list[j].contains(word, Qt::CaseInsensitive))
            {
                output += (j == list.size()-1) ? list[j] : list[j]+"\n";
                (*count)++;
            }
    }
    if(output == ""){
        output = "Not found input word\n";
    }
    return output;
}

void Song::changeLineInCouplet(QString text, int numOfCouplet, int numOfLineInCouplet)
{
    QStringList list = (this->getSongText())[numOfCouplet].getTextOfCouplet().split(QRegExp("\r\n"));
    list[numOfLineInCouplet] = (numOfLineInCouplet == list.size()-1)?text+"\n":text;
    (this->getSongText())[numOfCouplet].setTextOfCouplet(list.join("\r\n"));
}
void Song::swapTwoCoupets(int numOfFirstCouplet, int numOfSecondCouplet){
    QString temp1 = (this->getSongText())[numOfFirstCouplet].getTextOfCouplet();
    QString temp2 = (this->getSongText())[numOfSecondCouplet].getTextOfCouplet();
    (this->getSongText())[numOfFirstCouplet].setTextOfCouplet(temp2);
    (this->getSongText())[numOfSecondCouplet].setTextOfCouplet(temp1);
}
QString Song::printLastLines(int num){
    QString output = "";
    QStringList list;
    for(int i = 0; i<this->getCountOfCouplets();i++){
        list = (this->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
        output +=(QString)list.takeLast()+"\r\n";
    }
    return output;
}
QString Song::typeOfSonnet()
{
    QVector<int> arr;
    QStringList list;
    int sum = 0;
    QString result = "It's not sonnet!";
    if(this->getCountOfCouplets()>1 && this->getCountOfCouplets()<5){
        for(int i = 0; i<this->getCountOfCouplets();i++){
            list = (this->getSongText())[i].getTextOfCouplet().split(QRegExp("\r\n"),QString::SkipEmptyParts);
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
    return result;
}
