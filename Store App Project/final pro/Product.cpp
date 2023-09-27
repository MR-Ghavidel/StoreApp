#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

Product::Product()
{
}
Product :: ~Product()
{
}


//------------------IDP-------------------
void Product::setIDP(int idp)
{
    IDP = idp;
}
int Product::getIDP()
{
    return IDP;
}

//------------------Price-------------------
void Product::setPrice(int p)
{
    price = p;
}
int Product::getPrice()
{
    return price;
}

//-------------------Stock------------------
void Product::setStock(int st)
{
    stock = st;
}
int Product::getStock()
{
    return stock;
}

//-------------------Name------------------
void Product::setName(string pna)
{
    Pname = removeSpace(pna);
    //Pname = pna;
}
string Product::getName()
{
    return Pname;
}

//---------------------File----------------
void Product::writeFile()
{
	ofstream text("Super Market - Public/Products.txt", ios::app);
	text << IDP <<' ';
    text << Pname << ' ';
    text << price << ' ';
    text << stock << ' ';
    text << name << ' ';
    text << IDC << ' ';
    text << place << ' ';
    text << Bname << ' ';
    text << IDB << endl;
}

void Product::deletedFile()
{
    ofstream text("Super Market - Public/Deleted-Products.txt", ios::app);
    text << IDP << ' ';
    text << Pname << ' ';
    text << price << ' ';
    text << stock << ' ';
    text << name << ' ';
    text << IDC << ' ';
    text << place << ' ';
    text << Bname << ' ';
    text << IDB << endl;
}

string Product::removeSpace(string text)
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



