#ifndef COUPLET_H
#define COUPLET_H
#include <vector>
#include <iostream>
#include <QString>
class Couplet
{
protected:
    int numberOfCouplet;
    QString textOfCouplet;
public:
    Couplet() = default;

    Couplet(int n, QString vec){numberOfCouplet = n; textOfCouplet = vec;}

    int getNumberOfCouplet(){return numberOfCouplet;}
    void setnumberOfCouplet(int num){numberOfCouplet = num;}

    QString getTextOfCouplet(){return textOfCouplet;}
    void setTextOfCouplet(QString text){textOfCouplet = text;}
};

#endif // COUPLET_H
