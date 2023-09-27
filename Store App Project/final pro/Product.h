#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Category.h"
#include "Brand.h"

using namespace std;

class Product : public Category, public Brand
{
        int IDP, price, stock, obj;
        string Pname;
    public:
    
        Product();
        ~Product();

        // IDP
        //void setIDP();
        void setIDP(int id);
        int getIDP();

        // Price
       // void setPrice();
        void setPrice(int p);
        int getPrice();

        // Stock
        //void setStock();
        void setStock(int st);
        int getStock();

        // Name
        //void setName();
        void setName(string pna);
        string getName();

        //file writes
        void writeFile();
        void deletedFile();
        
        string removeSpace(string text);
};

