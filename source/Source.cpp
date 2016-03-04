#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void mainModule();				//Main Module

void cashierMod();				//Cashier Module
void addSale();					//Add to Sale
void deleteSale();				//Delete from Sale
void processSale();				//Process Sale

void inventory();				//Add/Delete/Edit/Search Module
void addBook();					//Add Book to Inventory
void deleteBook();				//Delete Book from Inventory
void editBook();				//Edit Book Information

void searchBook();				//Search for Book
void searchTitle();				//Search by Title
void searchAuthor();			//Search by Author
void searchIsbn();				//Search by ISBN
void searchWholesale();			//Search by Wholesale
void searchRetailPrice();		//Search by Retail Price
void searchPublisher();			//Search by Publisher
void searchDateAdded();			//Search by Date Added

void reports();					//Reports
void inventoryList();			//Inventory Report
void wholeSaleList();			//Wholesale Report
void retailPriceList();			//Retail Price Report
void listByQuantity();			//List by Quantity
void listByCost();				//List by Cost
void listByAge();				//List by Age

void update();					//Update Inventory List

int main()
{
	fstream inventory;					//Define Inventory
	inventory.open("inventory.txt");	//Open Inventory List

	mainmodule();						//Calls Main Module

	inventory.close();					//Close Inventory List

	system("pause");
	return 0;
}

void mainmodule()
{
	int option;

	cout << "1. Cashier Module" << endl;
	cout << "2. Inventory" << endl;
	cout << "3. Reports" << endl;
	cout << "4. Exit" << endl;
	cout << "Select an option: ";
	cin >> option;

	while (option > 4 || option < 1)
	{
		cout << "User input is invalid. Please input a valid option: ";
		cin >> option;
	}

	switch (option)
	{
	case 1:
		cashierMod();
	case 2:
		inventory();
	case 3:
		reports();
	case 4:
		cout << "Program will now terminate...";
		system("pause");
		exit(1);
	default:
		exit(1);
	}
}

void cashierMod()
{
	int option;

	cout << "1. Add to Sale" << endl;
	cout << "2. Delete from Sale" << endl;
	cout << "3. Process Transaction" << endl;
	cout << "4. Exit" << endl;
	cout << "Select an option: " << endl;
	cin >> option;

	while (option > 4 || option < 1)
	{
		cout << "User input is invalid. Please input a valid option: ";
		cin >> option;
	}

	switch (option)
	{
	case 1:
		addSale();
		break;
	case 2:
		deleteSale();
		break;
	case 3:
		processSale();
		break;
	case 4:
		cout << "Returning to Main Module...";
		system("pause");
		break;
	default:
		break;
	}
}