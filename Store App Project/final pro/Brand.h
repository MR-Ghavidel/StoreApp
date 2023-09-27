#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Brand
{
	protected:
		int IDB;
		string Bname;
	public:
	
		Brand();
		~Brand();

		// Name
		//void setName();
		void setName(string bna);
		string getName();

		// IDB
		//void setIDB();
		void setIDB(int idb);
		int getIDB();


		string removeSpace(string text);
};

