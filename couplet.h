#ifndef COUPLET_H
#define COUPLET_H
#include <vector>
#include <iostream>
#include <QString>
class Couplet
{
protected:
    int numberOfCouplet;
    std::vector<QString> textOfCouplet;
public:
    Couplet();

    Couplet(int n, std::vector<QString> vec){numberOfCouplet = n; textOfCouplet = vec;}

    Couplet(Couplet& old){this->textOfCouplet = old.getTextOfCouplet();
                          this->numberOfCouplet = old.getNumberOfCouplet();}

    int getNumberOfCouplet(){return numberOfCouplet;}
    void setnumberOfCouplet(int num){numberOfCouplet = num;}

    std::vector<QString> getTextOfCouplet(){return textOfCouplet;}
    void setTextOfCouplet(std::vector<QString> text){textOfCouplet = text;}
};

#endif // COUPLET_H
