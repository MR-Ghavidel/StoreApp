#include "Category.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Category::Category()
{

}

Category ::~Category()
{

}
//------------------Name------------------
void Category::setName(string cna)
{
    name = removeSpace(cna);
    //name = cna;
}
string Category::getName()
{
    return name;
}

//------------------IDC------------------
void Category::setIDC(int idc)
{
    IDC = idc;
}
int Category::getIDC()
{
    return IDC;
}

//------------------Place------------------
void Category::setPlace(string pla)
{
    place = removeSpace(pla);
    //place = pla;
}
string Category::getPlace()
{
    return place;
}

string Category::removeSpace(string text)
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