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
        output+="Couplet:"+QString::number(i+1)+(song.getSongText())[i].getTextOfCouplet();//
    }
    QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(output);
        listWidget->addItem(newItem);
}
