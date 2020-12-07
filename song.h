#ifndef SONG_H
#define SONG_H
#include "couplet.h"
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QRegExp>
#include <iostream>
#include <QString>
#include <QVector>
#include <QListWidgetItem>
#include "couplet.h"
class Song
{
private:
    QString author;
    QString name;
    int countOfCouplets;
    QVector<Couplet> songText;
    bool isSaved;
public:
    Song() = default;

    Song(QVector<Couplet> text,QString auth,
    QString nam, int count){songText = text;author = auth; name = nam;countOfCouplets = count;}

    Song(Song& old){this->songText = old.getSongText();
                    this->author = old.getAuthor();
                    this->name = old.getName();
                    this->countOfCouplets = old.getCountOfCouplets();}

    ~Song() = default;

    QString getAuthor(){return author;}
    void setAuthor(QString auth){author = auth;}

    QString getName(){return name;}
    void setName(QString nam){name = nam;}

    int getCountOfCouplets(){return countOfCouplets;}
    void setCountOfCouplets(int num){countOfCouplets = num;}

    bool getIsSaved(){return isSaved;}
    void setIsSaved(bool num){isSaved = num;}

    QVector<Couplet>& getSongText(){return songText;}
    void setSongText(QVector<Couplet>& text){songText = text;}

    void readFromFile(QString fileName);
    void saveToFile(QString fileName);

    friend QTextStream &operator>>(QTextStream& in, Song& song);
    friend QTextStream &operator<<(QTextStream& in, Song& song);
    friend void operator<<(QListWidget *listWidget, Song &song);
};

#endif // SONG_H
