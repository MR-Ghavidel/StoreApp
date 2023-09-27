#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include <ctime>
#include <windows.h>
#include <dos.h>
#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif
#pragma warning(disable : 4996)

// ------- Headers -------
#include "Category.h"
#include "Product.h"
#include "Brand.h"

using namespace std;
using namespace date;

// global variables
int sum = 0; // count of products
int countInvoice = 0; // count of invoice
char ch;
string license = "0";
char adminPass[9] = "09876543";

// menu fuctions
int mainMenuAdmin(); // admin
int mainMenuCustomer(); // customer
int ProductMenu(); // add - delete - edit
void BuyPro();
int search();
int edit();
void invoice();
void cleaner();
int accountMenuAdmin();
int accountMenuCustomer();

// general function
void includeObj(Product Pro[]);
void displayItem(Product Pro[], int i);
void Delete(Product Pro[], int i);
void tryBuy(int searchId, string search, Product Pro[]);
void deleteHistory();
void displayItemC(int i, string categoryNames[], int categoryIds[]);
int passwordCheck();
void includeCatInfo(string categoryNames[], int categoryIds[]);
bool captcha();
////---------------------------------------------------------
void includeSum(int& sum) // include sum from file // sum is number of products in market (line of text.txt)
{
	ifstream countPro1("Super Market - Public/countPro.txt");
	countPro1 >> sum;
	countPro1.close();
}
void writeSum(int a)
{
	fstream writeInSum("Super Market - Public/countPro.txt");
	writeInSum << a;
	writeInSum.close();
}
void includet(int& countInvoice) // include t from file // t is number of sold products (line of invoice.txt)
{
	ifstream countPro2("Super Market - Public/count-Invoice.txt");
	countPro2 >> countInvoice;
	countPro2.close();
}
void saveStartDate() // zakhire avalin rooz estefade
{
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);

	int year = (now->tm_year + 1900);
	int month = (now->tm_mon + 1);
	int day = now->tm_mday;
	ofstream startDay("C:/Users/Public/Documents/Super Market - Private/startDay.txt");
	startDay << year << ' ' << month << ' ' << day;
	startDay.close();
}
auto currentDate() // tarikh rooz
{
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);

	int currentY = (now->tm_year + 1900);
	int currentM = (now->tm_mon + 1);
	int currentD = now->tm_mday;
	auto y = year{ currentY } / currentM / currentD;
	return y;
}

void includeLicense()
{
	ifstream includeLicense("Super Market - Public/license.txt");
	getline(includeLicense, license);
	includeLicense.close();
}
bool licenseCheck(string license)
{
	if (license[3] == 'M' && license[21] == 'r' && license[14] == 'g' && license[28] == 'h')
	{
		return 1;
	}
	else
		return 0;
}
int licenseExp()
{
	includeLicense();
	int ratio, d;
	int exp1;

	string str, str2, a, b, c;
	str = license[2];

	ratio = stoi(str);
	a = license[6];
	b = license[11];
	c = license[31];
	str2 = a + b + c;
	d = stoi(str2);
	exp1 = ratio * d;
	return exp1;
}
bool licenseExpCheck(string license, int& useTime)
{

	int startY, startM, startD;
	ifstream startDay("C:/Users/Public/Documents/Super Market - Private/startDay.txt");
	startDay >> startY >> startM >> startD;
	startDay.close();
	auto x = year{ startY } / startM / startD; // tarikh avalin estefade
	auto y = currentDate();
	ofstream temp("C:/Users/Public/Documents/Super Market - Private/temp.txt");
	temp << sys_days{ y } - sys_days{ x };
	temp.close();
	ifstream temp1("C:/Users/Public/Documents/Super Market - Private/temp.txt");
	string u;
	getline(temp1, u, 'd');
	temp1.close();
	useTime = stoi(u);
	includeLicense();
	int exp1 = licenseExp();
	if (exp1 > useTime)
	{
		return 1;
	}
	else
		return 0;

}

void createFolder(string dir)
{
#if defined _MSC_VER
	_mkdir(dir.data());
#elif defined __GNUC__
	mkdir(dir.data());
#endif
}
void nameRewrite(string& pname)
{
	if (pname[0] == ' ')
	{
		for (int z = 0; z < pname.length(); z++)
		{
			pname[z] = pname[z + 1];
		}
		cout << pname << "|" << endl;
		system("pause");
	}
}
string removeSpace(string text)
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
string removeWriteSpace(string text)
{
	for (int i = 0; text[i]; i++)
	{
		if (text[i] == '-')
		{
			text[i] = ' ';
		}
	}
	return text;
}

void reverse_String(string& greet, int n, int i) {

	if (n <= i) { return; }

	swap(greet[i], greet[n]);
	reverse_String(greet, n - 1, i + 1);

}
string ownerLicenseName()
{
	string ownerName;
	includeLicense();
	for (int i = 32; i < 80; i++)
	{
		if (license[i] == '@')
		{
			ownerName = license.substr(i + 1, 79);

		}
	}
	reverse_String(ownerName, ownerName.length() - 1, 0);
	return ownerName;

}

bool ActiveLicenseFirst()
{
	int useTime;
	createFolder("C:\\Users\\Public\\Documents\\Super Market - Private");
	createFolder("Super Market - Public");


	includeLicense();
	ifstream myFile("C:/Users/Public/Documents/Super Market - Private/startDay.txt");
	if (myFile.fail()) {
		ofstream myFile2("C:/Users/Public/Documents/Super Market - Private/startDay.txt");
	}

	if (license.length() < 80)
	{
		cout << " ----> Enter Your License Code:\n";
		getline(cin, license);
		ofstream saveLicense("Super Market - Public/license.txt");
		saveLicense << license;
		saveLicense.close();
		if (licenseCheck(license) == 1) // check standard of original license
		{
			saveStartDate(); //////////////////////////////////////////////////////////////////////////////////////
			if (licenseExpCheck(license, useTime) == 1) // barasi etebar license
			{
				int exp1 = licenseExp();
				system("cls");
				cout << "------------------------------------------------------------\n";
				cout << "- The License is Activated for " << exp1 - useTime << " days\n";
				cout << "- Enter Password of 'add' Menu (8 digits): \n ";
				for (int i = 0; i < 9; i++)
				{
					adminPass[i] = _getch();
					cout << "*";
					if (i == 7)
					{
						cout << endl;
						break;
					}

				}
				ofstream passwordSave("C:/Users/Public/Documents/Super Market - Private/password.txt");
				passwordSave << adminPass;
				passwordSave.close();
				return 1;
			}
			else if (licenseExpCheck(license, useTime) == 0) // License Ended
			{
				cout << "----> License Expired <----\n";
				cout << "---------------------------\n";
				ofstream passwordSave("C:/Users/Public/Documents/Super Market - Private/password.txt", ios::trunc);
				passwordSave.close();
				ofstream saveLicense("Super Market - Public/license.txt");
				saveLicense << license + "-EXP";
				saveLicense.close();
				return 0;
			}
		}
		else if (licenseCheck(license) == 0)
		{
			cout << "----> License is not Valid <----\n";
			cout << "--------------------------------\n";
			ofstream saveLicense2("Super Market - Public/license.txt", ios::trunc);
			saveLicense2 << "License_is_not_Valid.";
			saveLicense2.close();
			return 0;
		}

	}
	else if (license.length() == 80)
	{
		if (licenseCheck(license) == 1) // check standard of original license
		{
			if (licenseExpCheck(license, useTime) == 1) // barasi etebar license
			{
				ifstream passwordInclude("C:/Users/Public/Documents/Super Market - Private/password.txt");
				passwordInclude >> adminPass;
				passwordInclude.close();
				return 1;
			}
			else
			{
				cout << "----> License Expired <----\n";
				cout << "---------------------------\n";
				ofstream passwordSave("C:/Users/Public/Documents/Super Market - Private/password.txt", ios::trunc);
				passwordSave.close();
				ofstream saveLicense("Super Market - Public/license.txt");
				saveLicense << license + "-EXP";
				saveLicense.close();
				return 0;
			}
		}
		else if (licenseCheck(license) == 0)
		{
			cout << "----> License is not Valid <----\n";
			cout << "--------------------------------\n";
			ofstream saveLicense("Super Market - Public/license.txt");
			saveLicense << "License is not Valid.";
			saveLicense.close();
			return 0;
		}
	}
	else if (license.length() > 80)
	{
		cout << "----> License is not Valid <----\n";
		cout << "--------------------------------\n";
		ofstream saveLicense2("Super Market - Public/license.txt", ios::trunc);
		saveLicense2 << "****";
		saveLicense2.close();
		return 0;
	}
}
//------------------------------------- Main ------------------------------------------
int main()
{
	if (ActiveLicenseFirst() == 0)
	{
		mainMenuCustomer();
	}
	else if (ActiveLicenseFirst() == 1)
	{
		system("cls");
		cout << "\n ----> Hi " << ownerLicenseName() << " <----\n" << endl;

		Sleep(1000);
		mainMenuAdmin();
	}
	_getch();
	return 0;
}
//-------------------------------------------------------------------------------------

//--------------------------------- Main Menu Admin -----------------------------------
int mainMenuAdmin()
{
	cout << "---> WELCOME TO Super Market <---\n";
	do {
		cout << "-----------------------\n";
		cout << " What Do You Wanna Do : ";
		cout << "\n 1 : Product";
		cout << "\n 2 : Buy";
		cout << "\n 3 : Invoice";
		cout << "\n 4 : Search";
		cout << "\n 5 : Clean All Data";
		cout << "\n 6 : Account";
		cout << "\n 7 : Exit\n";
		//cout << "\n\nChoice : ";
		ch = _getch();

		switch (ch)
		{
		case '1': // add - delete - edit (Product)  // + pass
		{
			int password = passwordCheck();
			if (password == 1) // correct password
			{
				system("cls");
				ProductMenu();// add - delete - edit

			}
			else if (password == 0)
			{
				system("cls");
				cout << " Wrong password!!\n";
				break;
			}
			else if (password == -1)
			{
				system("cls");
				cout << " Canceled.\n";
				mainMenuAdmin();
			}
			break;
		} // case 1

		case '2': // Buy
		{
			system("cls");
			BuyPro();
			break;
		} // case 2


		case '3': // Invoice
		{
			system("cls");

			invoice();
			break;
		} // case 3

		case '4': // Search
		{
			system("cls");
			search();
			break;
		} // case 4

		case '5': // Clean all program files
		{
			system("cls");
			cout << "----> Clean All Program Files <----\n";
			cout << " Are You Sure? (Y/y: Yes | N/n: No)\n";
			char yesNo;
			yesNo = _getch();
			if (yesNo == 'y' or yesNo == 'Y')
			{
				cleaner();
				cout << "-------------------\n";
				break;
			}
			else if (yesNo == 'n' or yesNo == 'N')
			{
				cout << " Cancell.\n";
				cout << "-------------------\n";
				break;
			}

		} // case 5

		case '6': // Account License
		{
			system("cls");
			accountMenuAdmin();
			break;
		} // case 6

		case '7': // Exit
		{
			system("cls");
			cout << " Bye " << ownerLicenseName() << ", Hope to See You Soon.\n";
			cout << "-------------------------------------------------------\n";
			ch = NULL;
			return 0;
		} // case 7

		default:
		{
			system("cls");
			cout << " Invalid Input\n";
			break;
		}


		} // switch
		ch = NULL;
	} while (true);
}
//-------------------------------------------------------------------------------------

//--------------------------------- Main Menu User ------------------------------------
int mainMenuCustomer()
{
	cout << "---> WELCOME TO Super Market <---\n";
	do {
		cout << "-----------------------\n";
		cout << " What Do You Wanna Do : ";
		cout << "\n 1 : Buy";
		cout << "\n 2 : Invoice";
		cout << "\n 3 : Search";
		cout << "\n 4 : Clean All Data";
		cout << "\n 5 : Account";
		cout << "\n 6 : Exit\n";
		ch = _getch();

		switch (ch)
		{

		case '1': // Buy
		{
			system("cls");
			BuyPro();
			break;
		} // case 1


		case '2': // Invoice
		{
			system("cls");
			invoice();
			break;
		} // case 2

		case '3': // Search
		{
			system("cls");
			search();
			break;
		} // case 3

		case '4': // Clean all program files
		{
			system("cls");
			cout << "----> Clean All Program Files <----\n";
			cout << " Are You Sure? (Y/y: Yes | N/n: No)\n";
			char yesNo;
			yesNo = _getch();
			if (yesNo == 'y' or yesNo == 'Y')
			{
				cleaner();
				cout << "-------------------\n";
				break;
			}
			else if (yesNo == 'n' or yesNo == 'N')
			{
				cout << " Cancell.\n";
				cout << "-------------------\n";
				break;
			}

		} // case 4

		case '5': // Account License
		{
			system("cls");
			accountMenuCustomer();
			break;
		} // case 5

		case '6': // Exit
		{
			system("cls");
			cout << " Exit.\n";
			cout << "-------------------\n";
			ch = NULL;
			return 0;
		} // case 6

		default:
		{
			system("cls");
			cout << " Invalid Input\n";
			break;
		}


		}
	} while (true);
}
//-------------------------------------------------------------------------------------

//---------------------------------- Product Menu -------------------------------------
int ProductMenu() // add - delete - delete history
{
	while (true)
	{

		cout << "-------------------\n";
		cout << " 1 : Add";
		cout << "\n 2 : Delete";
		cout << "\n 3 : Delete History";
		cout << "\n 4 : Edit";
		cout << "\n esc : Back\n";
		ch = _getch();
		switch (ch)
		{
		case '1': // add Product
		{
			int n;
			system("cls");
			cout << " How Many Product Do You Want Set:\n --->(Press '0' to Cancel)<---\n";
			cin >> n; // number of products for add in this roand

			if (n == 0)
			{
				system("cls");
				cout << " Cancel.\n";
				cout << "-------------------\n";
				//ProductMenu();
				break;
			}

			ifstream countPro1("Super Market - Public/countPro.txt");
			countPro1 >> sum;
			cout << " You have " << sum << " Products\n";
			ofstream countPro("Super Market - Public/countPro.txt");
			sum = sum + n;
			countPro << sum;


			for (int j = 0; j < n; j++)
			{
				cout << "-------------------\n";
				for (int i = 0; i < 1; i++)
				{
					int integer;
					string str;
					Product Pro;
					/////////////////////////
					cout << " Product ID : ";
					cin >> integer;
					Pro.setIDP(integer); // 1
					/////////////////////////
					cout << "       Name : ";
					getline(cin >> ws, str);
					//cin >> str;
					Pro.setName(str); // 2
					/////////////////////////
					cout << "      Price : ";
					cin >> integer;
					Pro.setPrice(integer); // 3
					/////////////////////////
					cout << "      Stock : ";
					cin >> integer;
					Pro.setStock(integer); // 4
					/////////////////////////
					cout << "   Category : ";
					getline(cin >> ws, str);
					//cin >> str;
					Pro.Category::setName(str); // 5
					/////////////////////////
					cout << "Category ID : ";
					cin >> integer;
					Pro.Category::setIDC(integer); // 6
					/////////////////////////
					cout << "      Place : ";
					getline(cin >> ws, str);
					//cin >> str;
					Pro.Category::setPlace(str); // 7
					/////////////////////////
					cout << "      Brand : ";
					getline(cin >> ws, str);
					//cin >> str;
					Pro.Brand::setName(str); // 8
					/////////////////////////
					cout << "   Brand ID : ";
					cin >> integer;
					Pro.Brand::setIDB(integer); // 9
					/////////////////////////
					Pro.writeFile(); // write all in file
					system("cls");
				}
			}
			break;
		} // case 1

		case '2': // delete Product
		{
			system("cls");
			includeSum(sum); // icluding sum from file "countPro"
			Product* Pro = new Product[sum]; // create Objects[sum]
			includeObj(Pro); // include data from file to Objects


			int search;
			cout << " Enter Product ID You Want to Delete:\n  --->(Press '0' to Cancel)<---\n";
			cin >> search;
			if (search == 0)
			{
				cout << " Cancel.\n";
				cout << "-------------------\n";
				//ProductMenu();
				break;
			}
			for (int i = 0; i < sum; i++)
			{
				if (Pro[i].getIDP() == search)
				{
					displayItem(Pro, i);
					cout << "\n---> Solve The Captcha to Delete <---\n";
					int captchaResult = captcha();

					if (captchaResult == 1)
					{
						system("cls");
						Pro[i].deletedFile(); // save deleted products
						Delete(Pro, i);
						ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
						text.close();
						int tempSum = 0; // shomarande tedad Product ha ke delete shodan;
						//includeSum(sum); // icluding sum from file "countPro"
						for (int i = 0; i < sum; i++)
						{
							tempSum = 0;
							if (Pro[i].getIDP() == 0 && Pro[i].getName() == "0")
							{
								tempSum++;
								/*ofstream countPro5("Super Market - Public/countPro.txt");
								countPro5 << sum - 1;
								cout << "tempSum: " << sum - tempSum<<endl;
								system("pause");*/
							}
							if (Pro[i].getIDP() != 0 && Pro[i].getName() != "0")
							{
								Pro[i].writeFile(); // write pro[i] in file
							}
						}
						includeSum(sum);
						writeSum(sum - 1);
						//ofstream countPro5("Super Market - Public/countPro.txt", ios::trunc);
						//sum = sum - tempSum;
						//countPro5 << sum - tempSum;
						//countPro5.close();
						break;
					}
					else if (captchaResult == 0)
					{
						system("cls");
						cout << " Wrong Answer!\nDelete failed.\n";
						break;
					}
				}
				else if (i == sum - 1)
				{
					cout << " Ther is no such a Product!\n";
					cout << "----------------------\n";
				}
			} // for


			delete[] Pro; // delete all Objects
			cout << "----------------------\n";
			break;
		} // case 2

		case '3': // Delete History
		{
			system("cls");
			deleteHistory();
			break;
		} //case 3

		case '4': // edit
		{
			system("cls");
			edit();
			break;
		} //case 4

		case 27: // back
		{
			system("cls");
			cout << " Backed.\n";
			cout << "-------------------\n";
			ch = NULL;
			return 0;
		} // case back

		default:
		{
			system("cls");
			cout << " Invalid Input\n";
			cout << "-------------------\n";
			break;
		} // default

		} // switch

	} // while

}
//-------------------------------------------------------------------------------------

//---------------------------------- Edit Product -------------------------------------
int edit()
{
	includeSum(sum); // icluding sum from file "countPro"
	Product* Pro = new Product[sum]; // create Objects[sum]
	includeObj(Pro); // include data from file to Objects
	int num, search;
	//int search;
	string st;
	if (sum == 0)
	{
		system("cls");
		cout << " There is no product.\n";
		cout << "-------------------\n";
		return 0;
	}
	else
	{
		while (true)
		{


			cout << "---> Edit Menu <---\n";
			cout << "\n 0 : Edit All Product Info";
			cout << "\n 1 : Edit Product Name";
			cout << "\n 2 : Edit Brand Name";
			cout << "\n 3 : Edit Category Name";
			cout << "\n 4 : Edit Place";
			cout << "\n 5 : Edit Price";
			cout << "\n 6 : Edit Product ID";
			cout << "\n 7 : Edit Category ID";
			cout << "\n 8 : Edit Brand ID";
			cout << "\n 9 : Edit Stock";
			cout << "\n esc : Back\n";

			ch = _getch();
			switch (ch)
			{
			case '0': // All Product Info
			{
				system("cls");
				cout << "\n---> Enter Product ID: ";
				cin >> search;

				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						int integer;
						cout << "   Enter New Product ID : ";
						cin >> integer;
						Pro[i].setIDP(integer); // 1

						cout << " Enter New Product Name : ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].setName(st); // 2

						cout << "        Enter New Price : ";
						cin >> integer;
						Pro[i].setPrice(integer); // 3

						cout << "        Enter New Stock : ";
						cin >> integer;
						Pro[i].setStock(integer); // 4

						cout << "  Enter New Category ID : ";
						cin >> integer;
						Pro[i].Category::setIDC(integer); // 6

						cout << "Enter New Category Name : ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].Category::setName(st); // 5

						cout << "        Enter New Place : ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].Category::setPlace(st); // 7

						cout << "     Enter New Brand ID : ";
						cin >> integer;
						Pro[i].Brand::setIDB(integer); // 9

						cout << "   Enter New Brand Name : ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].Brand::setName(st); // 8

						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
						cout << "-------------------\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				edit();
				break;
			} // case 0

			case '1': // Product Name
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;

				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Product Name: ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].setName(st);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 1

			case '2': // Brand Name
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Brand Name: ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].Brand::setName(st);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 2

			case '3': // Category Name
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Category Name: ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].Category::setName(st);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 3

			case '4': // Place
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Place: ";
						getline(cin >> ws, st);
						//cin >> st;
						Pro[i].setPlace(st);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 4

			case '5': // Price
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Price: ";
						cin >> num;
						Pro[i].setPrice(num);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 5

			case '6': // Product ID
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Product ID: ";
						cin >> num;
						Pro[i].setIDP(num);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 6

			case '7': // Category ID
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Category ID: ";
						cin >> num;
						Pro[i].setIDC(num);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 7

			case '8': // Brand ID
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Brand ID: ";
						cin >> num;
						Pro[i].setIDB(num);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 8

			case '9': // Stock
			{
				int search;
				system("cls");
				cout << "\nEnter Product ID: ";
				cin >> search;
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						cout << " Enter New Stock: ";
						cin >> num;
						Pro[i].setStock(num);
						cout << " DONE.\n";
						cout << "-------------------\n";
						break;
					}
					else if (i == sum - 1)
					{
						cout << " There is no such a Product!\n";
					}

				} // for
				ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
				for (int i = 0; i < sum; i++)
				{
					Pro[i].writeFile();
				}
				break;
			} // case 9

			case 27: // back
			{
				system("cls");
				cout << " Backed.\n";
				cout << "-------------------\n";
				return 0;
			} // case back

			default:
			{
				system("cls");
				cout << " Invalid Input\n";
				cout << "-------------------\n";
				break;
			} // default

			} // switch
		} // while
	}
	delete[] Pro; // delete all Objects
}
//-------------------------------------------------------------------------------------

//---------------------------------- Buy Product --------------------------------------
void BuyPro()
{
	includeSum(sum); // icluding sum from file "countPro"
	Product* Pro = new Product[sum]; // create Objects[sum]
	includeObj(Pro); // include data from file to Objects
	if (sum == 0)
	{
		system("cls");
		cout << " There is no product.\n";
	}
	else
	{
		string search;
		int searchId, count, finallStock, n;

		system("cls");
		cout << "\n------------------ Buy ------------------\n";
		cout << " How many Product do You Want to Buy: \n --->(Press '0' to Cancel)<---\n";
		cin >> n;

		if (n == 0) // cancel
		{
			system("cls");
			cout << " Cancel.\n";
		}

		for (int j = 0; j < n; j++)
		{
			cout << " Enter Product Name: ";
			//cin >> search;
			getline(cin >> ws, search);
			search = removeSpace(search);
			cout << " Enter Product ID: ";
			cin >> searchId;
			cout << " How Many Do You Want: ";
			cin >> count;
			for (int i = 0; i < sum; i++)
			{
				if (Pro[i].getName() == search && Pro[i].getIDP() == searchId)
				{
					if (Pro[i].getStock() >= count)
					{
						finallStock = Pro[i].getStock();
						finallStock -= count;
						int Total = Pro[i].getPrice();
						Pro[i].setStock(finallStock);
						ofstream invoice("Super Market - Public/invoice.txt", ios::app);
						invoice << Pro[i].getName() << "\t";
						invoice << Pro[i].Brand::getName() << "\t";
						invoice << count << "\t";
						invoice << Pro[i].getPrice() << "\t";
						invoice << count * Total << endl;
						cout << " Buy Successfuly Done.\n";
						cout << "========================================\n";
						invoice.close();
						ifstream countPro2("Super Market - Public/count-Invoice.txt");
						countPro2 >> countInvoice;
						countPro2.close();
						ofstream countPro3("Super Market - Public/count-Invoice.txt");
						countInvoice = countInvoice + 1;
						countPro3 << countInvoice;
						countPro3.close();
					}

					else if ((Pro[i].getName() == search && Pro[i].getIDP() == searchId) && (Pro[i].getStock() < count))
					{
						cout << " Stock is less than you want (Stock = " << Pro[i].getStock() << ")\n";
						tryBuy(searchId, search, Pro);
					}
					break;
				}
				else if (i == sum - 1)
				{
					cout << " There is not such a Product\n";
				}
			} // for in
		} // for out
		ofstream text("Super Market - Public/Products.txt", ios::trunc); // (empty file)
		for (int i = 0; i < sum; i++)
		{
			Pro[i].writeFile();
		}

	}
	delete[] Pro; // delete all Objects
}
//////////////////////////////////////////////////////////////////////////////////////|
void tryBuy(int searchId, string search, Product Pro[])
{
	includeSum(sum); // icluding sum from file "countPro"


	int count, finallStock, Total;
	cout << " How Many Do You Want: ";
	cin >> count;
	for (int i = 0; i < sum; i++)
	{
		if (Pro[i].getName() == search && Pro[i].getIDP() == searchId)
		{
			if (Pro[i].getStock() >= count)
			{
				finallStock = Pro[i].getStock();
				finallStock -= count;
				Total = Pro[i].getPrice();
				Pro[i].setStock(finallStock);
				ofstream invoice("Super Market - Public/invoice.txt", ios::app);
				invoice << Pro[i].getName() << ' ';
				invoice << Pro[i].Brand::getName() << ' ';
				invoice << count << ' ';
				invoice << Pro[i].getPrice() << ' ';
				invoice << count * Total << endl;
				cout << " Buy Successfuly Done.\n";
				cout << "========================================\n";

				ifstream countPro2("Super Market - Public/count-Invoice.txt");
				countPro2 >> countInvoice;
				countPro2.close();
				ofstream countPro3("Super Market - Public/count-Invoice.txt");
				countInvoice = countInvoice + 1;
				countPro3 << countInvoice;
				countPro3.close();
			}
			else
			{
				cout << " Stock is less than you want (Stock = " << Pro[i].getStock() << ")\n";
				tryBuy(searchId, search, Pro);
			}
		}
	}
}
//-------------------------------------------------------------------------------------

//------------------------------- accountMenuAdmin ------------------------------------
int accountMenuAdmin()
{
	while (true)
	{

		cout << "-----> Account <-----";
		cout << "\n 1 : License Info";
		cout << "\n 2 : Change License";
		cout << "\n 3 : Change Password";
		cout << "\n esc : Back\n";

		ch = _getch();
		switch (ch)
		{
		case '1': // License Info
		{
			system("cls");
			int useTime;
			licenseExpCheck(license, useTime); // set useTime (call by refrence)
			int startY, startM, startD;
			ifstream startDay("C:/Users/Public/Documents/Super Market - Private/startDay.txt");
			startDay >> startY >> startM >> startD;
			startDay.close();
			cout << "- License Generated for " << ownerLicenseName() << endl;
			cout << "- Your License Activated: " << startY << "/" << startM << "/" << startD << endl;
			cout << "- License EXP Time: " << licenseExp() << " days" << endl;
			cout << "- " << licenseExp() - useTime << " days Left\n";
			accountMenuAdmin();
			break;
		} // case 1

		case '2': // Change License
		{
			system("cls");
			cout << " Change License in Next Update.\n";
			cout << "-------------------\n";
			accountMenuAdmin();
			break;
		} // case 2

		case '3': // Change Password
		{
			system("cls");
			cout << " Change Password in Next Update.\n";
			cout << "-------------------\n";
			accountMenuAdmin();
			break;
		} // case 3

		case 27: // back
		{
			system("cls");
			cout << " Backed.\n";
			cout << "-------------------\n";
			return 0;
		} // case back

		default:
		{
			system("cls");
			cout << " Invalid Input\n";
			cout << "-------------------\n";
			break;
		} // default

		} // switch
	} // while
}
//-------------------------------------------------------------------------------------

//------------------------------ accountMenuCustomer ----------------------------------
int accountMenuCustomer()
{
	while (true)
	{


		cout << "-----> Account <-----";
		cout << "\n 1 : Set License";
		//cout << "\n2 : Change License";
		//cout << "\n3 : Change Password";
		cout << "\n esc : Back\n";

		ch = _getch();
		switch (ch)
		{
		case '1': // License Info
		{
			system("cls");
			if (ActiveLicenseFirst() == 0)
			{
				mainMenuCustomer();
			}
			else if (ActiveLicenseFirst() == 1)
			{
				mainMenuAdmin();
			}
			break;
		} // case 1

		//case '2': // Change License
		//{
		//	system("cls");
		//	cout << "Change License in Next Update.\n";
		//	cout << "-------------------\n";
		//	accountMenu();
		//	break;
		//} // case 2

		//case '3': // Change Password
		//{
		//	system("cls");
		//	cout << "Change Password in Next Update.\n";
		//	cout << "-------------------\n";
		//	accountMenu();
		//	break;
		//} // case 3

		case 27: // back
		{
			system("cls");
			cout << " Backed.\n";
			cout << "-------------------\n";
			return 0;
		} // case back

		default:
		{
			system("cls");
			cout << " Invalid Input\n";
			cout << "-------------------\n";
			break;
		} // default

		} // switch
	} // while
}
//-------------------------------------------------------------------------------------

//------------------------------------ Invoice ----------------------------------------
void invoice()
{
	includet(countInvoice); // icluding t from file "t"
	if (countInvoice == 0)
	{
		system("cls");
		cout << " There is no invoice.\n";
	}
	else
	{
		int count, price, Total, finalTotal1 = 0;
		string name, Bname;
		ifstream invoice("Super Market - Public/invoice.txt");

		for (int i = 0; i < countInvoice; i++)
		{
			invoice >> name;
			cout << name << " ";
			invoice >> Bname;
			cout << Bname << "\t";
			invoice >> count;
			cout << " Count : " << count << "\t";
			invoice >> price;
			cout << " Price : " << price << "\t";
			invoice >> Total;
			cout << " Total : " << Total << "\n";
			finalTotal1 += Total;
			cout << "-------------------------------------------\n";
		}
		cout << " Total Price : " << finalTotal1 << endl;
	}
}
//-------------------------------------------------------------------------------------

//----------------------------------- Search Menu -------------------------------------
int search()
{
	includeSum(sum); // icluding sum from file "countPro"
	Product* Pro = new Product[sum]; // create Objects[sum]
	includeObj(Pro); // include data from file to Objects
	if (sum == 0)
	{
		system("cls");
		cout << " There is no product.\n";
	}
	else
	{
		while (true)
		{


			//char  ch;
			cout << "---> Search Menu <---\n";
			cout << " 0 : Show All Products";
			cout << "\n 1 : By Product Name";
			cout << "\n 2 : By Brand Name";
			cout << "\n 3 : By Category Name";
			cout << "\n 4 : By Place";
			cout << "\n 5 : By Price";
			cout << "\n 6 : By Product ID";
			cout << "\n 7 : By Category ID";
			cout << "\n 8 : By Brand ID";
			cout << "\n 9 : By Stock";
			cout << "\n c : All category\n";
			cout << "\n esc : Back\n";

			ch = _getch();
			switch (ch)
			{
			case '0': // Show All
			{
				system("cls");
				for (int i = 0; i < sum; i++)
				{
					displayItem(Pro, i);
				}
				cout << "----------------------\n";
				break;
			} // case 0

			case 'c': // Show all category
			{
				system("cls");
				includeSum(sum); // icluding sum from file "countPro"
				string* categoryNames = new string[sum];
				int* categoryIds = new int[sum];
				includeCatInfo(categoryNames, categoryIds);
				for (int i = 0; i < sum; i++)
				{
					displayItemC(i, categoryNames, categoryIds);
				}
				cout << "----------------------\n";
				delete[] categoryNames;
				delete[] categoryIds;

				break;
			} // case 0

			case '1': // Product Name
			{
				system("cls");
				string search;
				cout << "\nEnter Name of Product to Search: ";
				//cin >> search;
				getline(cin >> ws, search);
				search = removeSpace(search);
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getName() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 1

			case '2': // Brand Name
			{
				system("cls");
				string search;
				cout << "\nEnter Name of Brand to Search: ";
				//cin >> search;
				getline(cin >> ws, search);
				search = removeSpace(search);
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].Brand::getName() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 2

			case '3': // Category Name
			{
				system("cls");
				string search;
				cout << "\nEnter Name of Category to Search: ";
				//cin >> search;
				getline(cin >> ws, search);
				search = removeSpace(search);
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].Category::getName() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 3

			case '4': // Place
			{
				system("cls");
				string search;
				cout << "\nEnter Place to Search: ";
				//cin >> search;
				getline(cin >> ws, search);
				search = removeSpace(search);
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].Category::getPlace() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 4

			case '5': // Price
			{
				system("cls");
				int search;
				cout << "\nEnter Price to Search: ";
				cin >> search;
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getPrice() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 5

			case '6': // Product ID
			{
				system("cls");
				int search;
				cout << "\nEnter Product ID to Search: ";
				cin >> search;
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getIDP() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 6

			case '7': // Category ID
			{
				system("cls");
				int search;
				cout << "\nEnter Category ID to Search: ";
				cin >> search;
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].Category::getIDC() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 7

			case '8': // Brand ID
			{
				system("cls");
				int search;
				cout << "\nEnter Brand ID to Search: ";
				cin >> search;
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].Brand::getIDB() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 8

			case '9': // Stock
			{
				system("cls");
				int search;
				cout << "\nEnter Stock to Search: ";
				cin >> search;
				int j = 0; // shomaresh tedad found ha
				for (int i = 0; i < sum; i++)
				{
					if (Pro[i].getStock() == search)
					{
						displayItem(Pro, i);
						//cout << "----------------------\n";
						j++;
						if (i == sum - 1)
						{
							break;
						}

					}
				} // for
				if (j == 0)
				{
					cout << " Not Found!\n";
					cout << "----------------------\n";
				}

				break;
			} // case 9

			case 27: // back
			{
				system("cls");
				cout << " Backed.\n";
				return 0;
			} // case back

			default:
			{
				system("cls");
				cout << " Invalid Input\n";
				break;
			} // default

			} // switch
		} // while
	}
	delete[] Pro; // delete all Objects
}
//-------------------------------------------------------------------------------------

//----------------------------------- Display Items -----------------------------------
void displayItem(Product Pro[], int i) // for printing all data from a product
{
	cout << "----------------------\n";
	cout << "Product[" << i + 1 << "] : \n";
	cout << " Product ID : " << Pro[i].getIDP() << endl;
	cout << "       Name : " << removeWriteSpace(Pro[i].getName()) << endl;
	cout << "      Price : " << Pro[i].getPrice() << endl;
	cout << "      Stock : " << Pro[i].getStock() << endl;
	cout << "   Category : " << removeWriteSpace(Pro[i].Category::getName()) << endl;
	cout << "Category ID : " << Pro[i].Category::getIDC() << endl;
	cout << "      Place : " << removeWriteSpace(Pro[i].Category::getPlace()) << endl;
	cout << "      Brand : " << removeWriteSpace(Pro[i].Brand::getName()) << endl;
	cout << "   Brand ID : " << Pro[i].Brand::getIDB() << endl;
}
//-------------------------------------------------------------------------------------

//------------------------------ Include Category Info --------------------------------
void includeCatInfo(string categoryNames[], int categoryIds[])
{
	int idp, price, stock, idc, idb;
	string pname, cname, place, bname;
	ifstream text("Super Market - Public/Products.txt");
	for (int j = 0; j < sum; j++) // include data from file to Objects
	{
		text >> idp; // 1
		text >> pname; // 2
		text >> price; // 3
		text >> stock; // 4
		text >> cname; // 5
		categoryNames[j] = cname; // 5
		for (int i = 0; i < j; i++)
		{
			if (categoryNames[i] == categoryNames[j])
			{
				categoryNames[j] = "";
				break;
			}
		}
		text >> idc; // 6
		categoryIds[j] = idc; // 6
		for (int i = 0; i < j; i++)
		{
			if (categoryIds[i] == categoryIds[j])
			{
				categoryIds[j] = 0;
				break;
			}
		}
		text >> place; // 7
		text >> bname; // 8
		text >> idb; // 9
	}
}
//-------------------------------------------------------------------------------------

//--------------------------------- Display Category ----------------------------------
void displayItemC(int i, string categoryNames[], int categoryIds[]) // for printing all category
{
	includeSum(sum); // icluding sum from file "countPro"
	for (int z = 0; z < sum; z++)
	{
		//tekrar[z] = 0;
		if (categoryNames[i] == categoryNames[z] && categoryIds[i] == categoryIds[z] && categoryNames[i] != "") // 
		{
			cout << "--------------------------\n";
			cout << " Category Name: " << removeWriteSpace(categoryNames[i]) << "\tCategory ID: " << categoryIds[i] << endl;
		}
	}

}
//-------------------------------------------------------------------------------------

//---------------------------------- Include Obj --------------------------------------
void includeObj(Product Pro[])
{
	int idp, price, stock, idc, idb;
	string pname, cname, place, bname;
	ifstream text("Super Market - Public/Products.txt");
	for (int i = 0; i < sum; i++) // include data from file to Objects
	{
		text >> idp;
		Pro[i].setIDP(idp); // 1
		text >> pname;
		Pro[i].setName(pname); // 2
		text >> price;
		Pro[i].setPrice(price); // 3
		text >> stock;
		Pro[i].setStock(stock); // 4
		text >> cname;
		Pro[i].Category::setName(cname); // 5
		text >> idc;
		Pro[i].Category::setIDC(idc); // 6
		text >> place;
		Pro[i].Category::setPlace(place); // 7
		text >> bname;
		Pro[i].Brand::setName(bname); // 8
		text >> idb;
		Pro[i].Brand::setIDB(idb); // 9
	}
}
//-------------------------------------------------------------------------------------

//---------------------------------- Clean All Data -----------------------------------
void cleaner()
{
	system("cls");
	ofstream cleanSum("Super Market - Public/countPro.txt", ios::trunc);
	cleanSum << 0;
	ofstream cleanProducts("Super Market - Public/Products.txt", ios::trunc);
	cout << " Products Cleared." << endl;
	//----------
	ofstream cleanDeleteHistory("Super Market - Public/Deleted-Products.txt", ios::trunc);
	cout << " Delete History Cleared." << endl;
	//----------
	ofstream cleanInvoice("Super Market - Public/invoice.txt", ios::trunc);
	cout << " Invoice Cleared." << endl;
	//----------
	ofstream cleanCountInvoice("Super Market - Public/count-Invoice.txt", ios::trunc);
	cleanCountInvoice << 0;
	//----------
	cout << "--------------------------\n";
}
//-------------------------------------------------------------------------------------

//------------------------------------- Delete ----------------------------------------
void Delete(Product Pro[], int i)
{
	Pro[i].setIDP(0); // 1
	Pro[i].setName("0"); // 2
	Pro[i].setPrice(0); // 3
	Pro[i].setStock(0); // 4
	Pro[i].Category::setName("0"); // 5
	Pro[i].Category::setIDC(0); // 6
	Pro[i].Category::setPlace("0"); // 7
	Pro[i].Brand::setName("0"); // 8
	Pro[i].Brand::setIDB(0); // 9
	cout << " Deleting Successfully Done.\n";
}
//-------------------------------------------------------------------------------------

//--------------------------------- Delete History ------------------------------------
void deleteHistory()
{
	int idp, price, stock, idc, idb, integer;
	string pname, cname, place, bname, text;

	int countDelete = 0;

	ifstream countPro3("Super Market - Public/Deleted-Products.txt");
	while (countPro3.peek() != EOF)
	{
		countPro3 >> integer >> text >> integer >> integer >> text >> integer >> text >> text >> integer;
		countDelete++;
	}
	countDelete--;
	if (countDelete <= 0)
	{
		cout << " No Delete History.\n";
	}
	else
	{
		Product* Pro = new Product[countDelete]; // create Objects[sum]



		ifstream countPro4("Super Market - Public/Deleted-Products.txt");
		for (int i = 0; i < countDelete; i++) // include data from file to Objects
		{
			countPro4 >> idp;
			Pro[i].setIDP(idp); // 1
			countPro4 >> pname;
			Pro[i].setName(pname); // 2
			countPro4 >> price;
			Pro[i].setPrice(price); // 3
			countPro4 >> stock;
			Pro[i].setStock(stock); // 4
			countPro4 >> cname;
			Pro[i].Category::setName(cname); // 5
			countPro4 >> idc;
			Pro[i].Category::setIDC(idc); // 6
			countPro4 >> place;
			Pro[i].Category::setPlace(place); // 7
			countPro4 >> bname;
			Pro[i].Brand::setName(bname); // 8
			countPro4 >> idb;
			Pro[i].Brand::setIDB(idb); // 9
		}

		for (int i = 0; i < countDelete; i++)
		{
			displayItem(Pro, i);
		}
		delete[] Pro; // delete all Objects
	}
}
//-------------------------------------------------------------------------------------

//------------------------------------- Captcha ---------------------------------------
bool captcha()
{
	int min = 0;
	int max = 20;
	int random1, random2, userInput, sum;
	srand(time(0)); // baraye sakht adad tasadofi ba tabe "rand" bar asas zaman system
	random1 = rand() % (max - min) + min; // adad random bein min va max
	random2 = rand() % (max - min) + min; // adad random bein min va max
	cout << random1 << " + " << random2 << " = \n";
	cout << " Enter Answer : ";
	cin >> userInput;
	sum = random1 + random2;
	if (sum == userInput)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//-------------------------------------------------------------------------------------

// ------------------------------------ Password --------------------------------------
int passwordCheck()
{
	int p = 0;
	//char adminPass[9] = "12345678"; // pass for access to Add menu
	system("cls");
	char pass[9];
	cout << " Enter Password ( 8 digits ):\n ";

	for (int i = 0; i < 9; i++) // get password from admin to check
	{
		
		pass[i] = _getch();
		cout << "*";
		if (i == 7)
		{
			system("cls");
			char pa;
			cout << "---------------------";
			cout << "\n e.Enter";
			cout << "\n c.Cancell\n";
			pa = _getch();
			if (pa == 'e')
			{

				break;
			}
			else if (pa == 'c')
			{

				return -1; // cancell

			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (adminPass[i] == pass[i])
		{
			p++;
			//cout << p << endl;
		}
	}
	if (p == 8)
	{
		return 1; // correct pass
	}
	if (p != 8)
	{
		return 0; // wrong pass
	}
}
//-------------------------------------------------------------------------------------
