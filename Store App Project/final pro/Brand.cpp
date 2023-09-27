#include "Brand.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Brand::Brand()
{

}
Brand :: ~Brand()
{

}

//------------------Name------------------
void Brand::setName(string bna)
{
    Bname = removeSpace(bna);
    //Bname = bna;
}
string Brand::getName()
{
    return Bname;
}

//------------------IDB------------------
void Brand::setIDB(int idb)
{
    IDB = idb;
}
int Brand::getIDB()
{
    return IDB;
}

string Brand::removeSpace(string text)
{
    for (int i = 0; text[i]; i++)
    {
        if (text[i] == ' ')
        {
            text[i] = '-';
        }
    }
    return text;
}