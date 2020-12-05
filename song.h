#ifndef SONG_H
#define SONG_H
#include "couplet.h"
#include <iostream>
#include <vector>
#include "couplet.h"
class Song: public Couplet
{
private:
    QString author;
    QString name;
    int countOfCouplets;
public:
    Song():Couplet(),author(""),name(""), countOfCouplets(0){};

    Song(int n, std::vector<QString> vec,QString auth,
    QString nam, int count){Couplet(n,vec);author = auth; name = nam;countOfCouplets = count;}

    Song(Song& old){this->textOfCouplet = old.getTextOfCouplet();
                    this->numberOfCouplet = old.getNumberOfCouplet();
                    this->author = old.getAuthor();
                    this->name = old.getName();
                    this->countOfCouplets = old.getCountOfCouplets();}

    QString getAuthor(){return author;}
    void setAuthor(QString auth){author = auth;}

    QString getName(){return name;}
    void setName(QString nam){name = nam;}

    int getCountOfCouplets(){return countOfCouplets;}
    void setCountOfCouplets(int num){countOfCouplets = num;}
};

#endif // SONG_H
