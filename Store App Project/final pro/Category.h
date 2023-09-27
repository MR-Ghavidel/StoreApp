#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Category
{
    protected:
        int IDC;
        string name, place;
    public:
    
        Category();
        ~Category();

        // Place
        //void setPlace();
        void setPlace(string pla);
        string getPlace();

        // Name
        //void setName();
        void setName(string cna);
        string getName();

        // IDC
       // void setIDC();
        void setIDC(int idc);
        int getIDC();

        string removeSpace(string text);
};

