#include <iostream>
//added iomanip for fancy shmancy output formatting in displayBook()
#include <iomanip>
#include <string>
#include <fstream>
#include "book.h"
#include <cstdlib>

/********************************************
 **					READ-ME
 **
 ** Please try to write your code as clean as possible.
 ** The code itself should describe its process and variable names should be descriptive enough to not need comments.
 ** Of course there will be exceptions but just try to write your code such that it doesn't need comments.
 *********************************************/

/*********************
**		Functional To-Do List
**
** - Rename variables. Some of them are unclear. [Mostly done]
** - Fix cin.ignore()
** - separate menus and clean up main() [done]
** - fix loop not finishing in inventoryMenu() and reportMenu()----> get rid of system("pause")s under every function call in switch [done]
** - fix inventoryMenu() exiting directly to main() after executing any function [done]
** - create interface and code cashier functionality
** - DEFINE REPORT FUNCTIONS [AT VERY BOTTOM] [done]
** - Need to include default options for all switch statements.
** - Create method to sort by quantity, retail, etc... Will probably need to use templates for that. [done]
** - Create a method that actually stores purchase information. To be used with cashier module.
**********************
**   Cosmetic To-Do List - gotta make dat shit pretty
**  [x] main menu
**  [x] inventory menu
**  [ ] cashier menu [DNE yet]
**  [x] report menu
**  [ ] addBook() [not really necessary]
**  [ ] editBook() [not really necessary]
**  [ ] deleteBook() [not really necessary]
**  [x] displayBook()
***********************/

using namespace std;

//GLOBALS

int sizeOfArray();
//menu prototypes
void inventoryMenu();
void cashierMenu();
void reportMenu();
//cashier protoype
void addToCart();
//inventory prototypes
void addBook();
void editBook();
void deleteBook();
void saveBook();
void loadBook();
//report prototypes
void inventoryReport();
void wholesaleReport();
void retailReport();
void quantityReport();
void costReport();
void ageReport();

string emptyStr; //used for menu navigation

int arraySize = sizeOfArray();
int cartSize = 0;
Book *tempBook = new Book;
Book *bookArray = new Book[arraySize];
Book *cart = new Book[cartSize];

template <class T>

void addToArray (T &arrayName, int &arraySize) {
		int newArraySize = arraySize + 1;
		Book *tempArray = new Book[newArraySize];

		for (int count = 0; count < arraySize; count++) {
			tempArray[count] = arrayName[count];
		}

		delete [] arrayName;

		arraySize = newArraySize;
		arrayName = tempArray;
}

//----------------------------------------
//-----------------MAIN-------------------
//----------------------------------------
int main() {
	loadBook();
	int x = 1;
	int mainChoice = 0;
	do{
		system("cls");
		std::cout << endl << endl << endl << endl << endl;
		std::cout << setw(50) << "Serendipity Booksellers" << endl;
		std::cout << setw(43) << "Main Menu" << endl;
		std::cout << endl;
		std::cout << setw(49) << "1. Inventory database" << endl;
		std::cout << setw(48) << "2. Cashier interface" << endl;
		std::cout << setw(49) << "3. Generate report(s)" << endl;
		std::cout << setw(46) << "4. Exit program..." << endl;
		std::cout << endl << endl;
		std::cout << setw(47) << "Enter your choice: ";
		cin >> mainChoice;
		system("cls");

		switch (mainChoice)
		{
			case 1:
				inventoryMenu();
				break;
			case 2:
				cashierMenu();
				break;
			case 3:
				reportMenu();
				break;
			case 4:
				return 0;
		}
	} while (x == 1);
}

// This function is meant to actually display the contents of the array we've loaded in loadBook.
void displayBook(int i) {
	if (i == -1) {
		std::cout << "Book was not found." << std::endl;
	}
	else {

		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "ISBN:" << setw(20) << right << bookArray[i].getISBN() << std::endl;
		std::cout << setw(25) << left << "Author:" << setw(20) << right << bookArray[i].getAuthor() << std::endl;
		std::cout << setw(25) << left << "Publisher:" << setw(20) << right << bookArray[i].getPublisher() << std::endl;
		std::cout << setw(25) << left << "Date Added (mmddyyyy):" << setw(20) << right << bookArray[i].getDateAdded() << std::endl;
		std::cout << setw(25) << left << "Retail Price:" << setw(20) << right << bookArray[i].getRetail() << std::endl;
		std::cout << setw(25) << left << "Wholesale Price:" << setw(20) << right << bookArray[i].getWholeSale() << std::endl;
		std::cout << setw(25) << left << "Quantity in inventory:" << setw(20) << right << bookArray[i].getQuantity() << std::endl;
		std::cout << setfill(' ');
	}
}

// This function is strictly to return the position of the book within the array loaded with loadBook().

int searchBook(std::string searchCriteria) {
	for (int i = 0; i < arraySize; i++) {
		if (searchCriteria == bookArray[i].getTitle() || searchCriteria == bookArray[i].getISBN()) {
			return i;
		}
	}
	return -1;
}


void addToCart(int position) {
	if (position != -1) {
		addToArray(cart, cartSize);
		cart[cartSize-1] = bookArray[position];
	} else {
		cout << "Unable to add to cart." << endl;
	}
}


void inventoryMenu()
{
	int inventoryExit = 0;
	do {
		system("CLS");
		std::cout << endl << endl << endl << endl << endl;
		std::cout << setw(50) << "Serendipity Booksellers" << endl;
		std::cout << setw(47) << "Inventory Database" << endl;
		std::cout << endl;
		std::cout << setw(46) << "1. Look up a book" << endl;
		std::cout << setw(42) << "2. Add a book" << endl;
		std::cout << setw(43) << "3. Edit a book" << endl;
		std::cout << setw(45) << "4. Delete a book" << endl;
		std::cout << setw(51) << "5. Return to main menu" << endl;
		std::cout << endl << endl;
		std::cout << setw(47) << "Enter your choice: ";
		int inventoryChoice;
		cin >> inventoryChoice;
		cin.ignore();
		system("CLS");

		switch (inventoryChoice) {
			case 1:{   // look up a book
				std::string query;
				std::cout << "Enter the title or ISBN of the book: ";
				std::getline(std::cin, query);
				displayBook(searchBook(query));
				cout << endl << "Press enter to return to the inventory menu";
				getline(cin, emptyStr);
				break;
			}
			case 2:{  // Add a book
				addBook();
				cout << endl << "Press enter to return to the inventory menu";
				getline(cin, emptyStr);
				break;
			}
				
			case 3: { // Edit a book
				editBook();
				cout << endl << "Press enter to return to the inventory menu";
				getline(cin, emptyStr);
				break;
			}
			case 4: { //Delete a book
				deleteBook();
				break;
			}
			case 5: { //Exit back to the main menu
				inventoryExit = 1;
				break;
			}
			default: {
				break;
			}
		}
	} while (inventoryExit == 0);
}

void cashierMenu()
{

}

void reportMenu()
{
	int reportExit = 0;
	do {
		std::cout << endl << endl << endl << endl << endl;
		std::cout << setw(50) << "Serendipity Booksellers" << endl;
		std::cout << setw(47) << "Report Generator" << endl;
		std::cout << endl;
		std::cout << setw(47) << "Select the report" << endl;
		std::cout << setw(49) << "you want to generate" << endl;
		std::cout << endl;
		std::cout << setw(47) << "1. Inventory Listing" << endl;
		std::cout << setw(55) << "2. Inventory Wholesale Value" << endl;
		std::cout << setw(52) << "3. Inventory Retail Value" << endl;
		std::cout << setw(49) << "4. Listing by Quantity" << endl;
		std::cout << setw(45) << "5. Listing by Cost" << endl;
		std::cout << setw(44) << "6. Listing by Age" << endl;
		std::cout << setw(49) << "7. Return to Main Menu" << endl;
		std::cout << endl << endl;
		std::cout << setw(47) << "Enter your choice: ";
		int reportChoice = 0;
		cin >> reportChoice;
		cin.ignore();
		switch (reportChoice)
		{
			case 1:
				inventoryReport();
				break;
			case 2:
				wholesaleReport();
				break;
			case 3:
				retailReport();
				break;
			case 4:
				quantityReport();
				break;
			case 5:
				costReport();
				break;
			case 6:
				ageReport();
				break;
			case 7:
				reportExit = 1;
				break;
		}
	} while (reportExit == 0);
}

// This needs to be at the beginning of main. No exceptions. This loads the information from our database file into an array.

void loadBook() {
	std::ifstream bookDatabase;
	bookDatabase.open("books.txt", std::ios::in);

	if (!bookDatabase.is_open()) {
		std::cout << "File could not be opened" << std::endl;
	}
	else {
		std::cout << "File was successfully opened." << std::endl;
	}

	std::string tempInput;

	bookDatabase.close();

	bookDatabase.open("books.txt", std::ios::in);

	int i = 0;
	double temp1;
	int temp2;
	std::string garbage;

	while (i < arraySize) {
		std::getline(bookDatabase, tempInput);
		tempBook->setTitle(tempInput);

		std::getline(bookDatabase, tempInput);
		tempBook->setISBN(tempInput);

		std::getline(bookDatabase, tempInput);
		tempBook->setAuthor(tempInput);

		std::getline(bookDatabase, tempInput);
		tempBook->setPublisher(tempInput);

		std::getline(bookDatabase, tempInput);
		tempBook->setDateAdded(tempInput);

		bookDatabase >> temp1;
		tempBook->setRetail(temp1);

		bookDatabase >> temp1;
		tempBook->setWholeSale(temp1);

		bookDatabase >> temp2;
		tempBook->setQuantity(temp2);

		std::getline(bookDatabase, garbage); // this is purely to move onto the next line

		bookArray[i] = *tempBook;
		i++;
	}

	bookDatabase.close();
}

// This function is what will determine the initial size of our array.

int sizeOfArray() {
	std::ifstream inputFile;

	inputFile.open("books.txt", std::ios::in);

	std::string temp;
	int counter = 0;
	while (std::getline(inputFile, temp)) {
		counter++;
	}
	inputFile.close();
	return counter / 8;
}

// This function will take the contents of the current defined array and rewrite our database file with the contents of the array.
// WIll need to include this at the end of anything that modifies the array.

void saveBook()
{
	ofstream output;
	output.open("books.txt");
	for (int count = 0; count < arraySize; count++)
	{
		output << bookArray[count].getTitle() << endl;
		output << bookArray[count].getISBN() << endl;
		output << bookArray[count].getAuthor() << endl;
		output << bookArray[count].getPublisher() << endl;
		output << bookArray[count].getDateAdded() << endl;
		output << bookArray[count].getRetail() << endl;
		output << bookArray[count].getWholeSale() << endl;
		output << bookArray[count].getQuantity() << endl;
	}
	output.close();
}

// This function creates a new array of a new size and copies the content of our current array over. 

void addBook()
{
	addToArray(bookArray, arraySize);

	string temptitle, tempisbn, tempauthor, temppublisher, tempdate;
	double tempretail, tempwholesale;
	int tempquantity;

	std::cout << "Title: ";
	std::getline(std::cin, temptitle);
	bookArray[arraySize-1].setTitle(temptitle);
	std::cout << endl << "ISBN: ";
	std::getline(std::cin, tempisbn);
	bookArray[arraySize-1].setISBN(tempisbn);
	std::cout << endl << "Author: ";
	std::getline(std::cin, tempauthor);
	bookArray[arraySize-1].setAuthor(tempauthor);
	std::cout << endl << "Publisher: ";
	std::getline(std::cin, temppublisher);
	bookArray[arraySize-1].setPublisher(temppublisher);
	std::cout << endl << "Date added: ";
	std::getline(std::cin, tempdate);
	bookArray[arraySize-1].setDateAdded(tempdate);
	std::cout << endl << "Retail Price: ";
	std::cin >> tempretail;
	std::cin.ignore();
	bookArray[arraySize-1].setRetail(tempretail);
	std::cout << endl << "Wholesale Price: ";
	std::cin >> tempwholesale;
	bookArray[arraySize-1].setWholeSale(tempwholesale);
	std::cout << endl << "Quantity: ";
	std::cin >> tempquantity;
	bookArray[arraySize-1].setQuantity(tempquantity);


	saveBook();
	cout << endl << endl;
	cout << "----------------" << bookArray[arraySize - 1].getTitle() << " ADDED----------------" << endl;
	displayBook(arraySize - 1);
}

void deleteBook()
{
	int deleteRepeat = 0;
	int deleteSelect = 0;
	do {
		//grabbed prompt for search from main()
		string deleteQuery;
		std::cout << "Please enter title or ISBN to delete: " << std::endl;
		//		cin.ignore();
		std::getline(cin, deleteQuery);
		//function calls
		int deleteLocation;
		//should display all info of match, better for user interactivity, I guess
		//DEBUG std::cout << "this is a debug statement" << std::endl;
		deleteLocation = searchBook(deleteQuery);
		if (deleteLocation != -1)
		{
			int newQuant; //For case 2
			cout << "Please select:" << endl;
			cout << "1) Remove all copies of " << bookArray[deleteLocation].getTitle() << endl;
			cout << "2) Return to previous screen" << endl; // change line
			cin >> deleteSelect;
			cin.ignore();
			switch (deleteSelect)
			{
			case 1:
				cout << "Removing all copies..." << endl;
				bookArray[deleteLocation].setQuantity(0);
				cout << "All copies removed." << endl;
				break;
			case 2:
				cout << "Cancelling..." << endl;
				break;
			}
			cout << "Would you like to delete another entry? 1 = Y, 0 = N" << endl;
			cin >> deleteRepeat;
			cin.ignore();
			saveBook();
		}
		else {
			cout << "This is not working" << endl; //debug
		}

	} while (deleteRepeat != 0);
}

/**********
** Check input for editBook()
***********/

void editBook()
{
	int repeat = 0;
	do {
		//grabbed prompt for search from main()
		string editQuery;
		std::cout << "Please enter title or ISBN to edit: " << std::endl;
		//		cin.ignore();
		std::getline(cin, editQuery);
		//function calls
		int editLocation;
		//should display all info of match, better for user interactivity, I guess
		//DEBUG std::cout << "this is a debug statement" << std::endl;
		editLocation = searchBook(editQuery);

		if (editLocation != -1)
		{
			int editSelect;
			std::cout << "Please select attribute to edit: " << endl;
			cout << "1) Title" << endl;
			cout << "2) ISBN" << endl;
			cout << "3) Author" << endl;
			cout << "4) Publisher" << endl;
			cout << "5) Date added" << endl;
			cout << "6) Retail Price" << endl;
			cout << "7) Wholesale price" << endl;
			cout << "8) Quantity in inventory" << endl;
			cout << "9) Multiple or all attributes" << endl;
			cout << "0) Cancel..." << endl;
			cin >> editSelect;
			cin.ignore();
			//declaring temp vars for editing input
			string newTitle, newISBN, newAuthor, newPublisher, newDateAdded;
			double newRetail, newWholeSale;
			int newQuantity;
			switch (editSelect)
			{
			case 1:
				cout << "Please enter new title: ";
				getline(cin, newTitle);
				bookArray[editLocation].setTitle(newTitle);
				break;
			case 2:
				cout << "Please enter new ISBN: ";
				getline(cin, newISBN);
				bookArray[editLocation].setISBN(newISBN);
				break;
			case 3:
				cout << "Please enter new author: ";
				getline(cin, newAuthor);
				bookArray[editLocation].setAuthor(newAuthor);
				break;
			case 4:
				cout << "Please enter new publisher: ";
				getline(cin, newPublisher);
				bookArray[editLocation].setPublisher(newPublisher);
				break;
			case 5:
				cout << "Please enter new date added (mmddyyyy): ";
				getline(std::cin, newDateAdded);
				bookArray[editLocation].setDateAdded(newDateAdded);
				break;
			case 6:
				cout << "Please enter new retail price (in <dollars>.<cents> format): ";
				cin >> newRetail;
				bookArray[editLocation].setRetail(newRetail);
				break;
			case 7:
				cout << "Please enter new wholesale price (in <dollars>.<cents> format): ";
				cin >> newWholeSale;
				bookArray[editLocation].setWholeSale(newWholeSale);
				break;
			case 8:
				cout << "Please enter updated amount in inventory: ";
				cin >> newQuantity;
				bookArray[editLocation].setQuantity(newQuantity);
				break;
			case 9:
				//feedback to differentiate from case 1
				cout << "Now editing all attributes..." << endl;

				cout << "Please enter new title: ";
				getline(cin, newTitle);
				cout << "Please enter new ISBN: ";
				getline(cin, newISBN);
				cout << "Please enter new author: ";
				getline(cin, newAuthor);
				cout << "Please enter new publisher: ";
				getline(cin, newPublisher);
				cout << "Please enter new date added (mmddyyyy): ";
				getline(cin, newDateAdded);
				cout << "Please enter new retail price (in <dollars>.<cents> format): ";
				cin >> newRetail;
				cin.ignore();
				cout << "Please enter new wholesale price (in <dollars>.<cents> format): ";
				cin >> newWholeSale;
				cout << "Please enter new quantity in inventory: ";
				cin >> newQuantity;
				bookArray[editLocation].setTitle(newTitle);
				bookArray[editLocation].setISBN(newISBN);
				bookArray[editLocation].setAuthor(newAuthor);
				bookArray[editLocation].setPublisher(newPublisher);
				bookArray[editLocation].setDateAdded(newDateAdded);
				bookArray[editLocation].setRetail(newRetail);
				bookArray[editLocation].setWholeSale(newWholeSale);
				bookArray[editLocation].setQuantity(newQuantity);
			case 0:
				cout << "Cancelling..." << endl;
				break;
			}
			//calls output info to update books.txt
			saveBook();
			//prompts for value to decide whether to exit do-while loop
			cout << "Enter 1 to edit another entry, or enter 0 to exit editing module." << endl;
			cin >> repeat;
		}
		else {
			std::cout << "I didn't even try." << std::endl; //debug
		}
	} while (repeat != 0);
}


/****************************************
*****************************************
**********  REPORT FUNCTIONS  ***********
*****************************************
****************************************/

void bookSort(string sortBy) {
	int start, maxIndex;
	Book tempBook;
	if (sortBy == "quantity") {
		int maxVal;
		for (start = 0; start < (arraySize - 1); start++) {
			maxIndex = start;
			maxVal = bookArray[start].getQuantity();
			for (int index = start + 1; index < arraySize; index++) {
				if (bookArray[index].getQuantity() > maxVal) {
					maxVal = bookArray[index].getQuantity();
					maxIndex = index;
				}
			}
			tempBook = bookArray[maxIndex];
			bookArray[maxIndex]= bookArray[start];
			bookArray[start] = tempBook;
		}
	}
	else if (sortBy == "wholesale") {
		double maxVal;
		for (start = 0; start < (arraySize - 1); start++) {
			maxIndex = start;
			maxVal = bookArray[start].getWholeSale();
			for (int index = start + 1; index < arraySize; index++) {
				if (bookArray[index].getWholeSale() > maxVal) {
					maxVal = bookArray[index].getWholeSale();
					maxIndex = index;
				}
			}
			tempBook = bookArray[maxIndex];
			bookArray[maxIndex] = bookArray[start];
			bookArray[start] = tempBook;
		}
	}
	else if (sortBy == "age") {
		string oldestDate;
		for (start = 0; start < (arraySize - 1); start++) {
			maxIndex = start;
			oldestDate = bookArray[start].getDateAdded();
			for (int index = start + 1; index < arraySize; index++) {
				if (bookArray[index].isOlder(oldestDate)) {
					oldestDate = bookArray[index].getDateAdded();
					maxIndex = index;
				}
			}
			tempBook = bookArray[maxIndex];
			bookArray[maxIndex] = bookArray[start];
			bookArray[start] = tempBook;
		}
	}
}

void inventoryReport()
{
	system("cls");
	for (int i = 0; i < arraySize; i++) {
		displayBook(i);
		cout << "==================================================" << endl;
	}
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void wholesaleReport()
{
	system("cls");
	double totalWholesale=0;
	for (int i = 0; i < arraySize; i++) {
		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "Wholesale Price:" << setw(20) << right << bookArray[i].getWholeSale() << std::endl;
		totalWholesale += bookArray[i].getWholeSale()*bookArray[i].getQuantity();
		cout << "==================================================" << endl;
	}
	cout << "==================================================" << endl;
	cout << setw(25) << left << "Total Wholesale Value:" << setw(20) << right << totalWholesale << std::endl;
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void retailReport()
{
	system("cls");
	double totalRetail = 0;
	for (int i = 0; i < arraySize; i++) {
		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "Retail Price:" << setw(20) << right << bookArray[i].getRetail() << std::endl;
		totalRetail += bookArray[i].getRetail()*bookArray[i].getQuantity();
		cout << "==================================================" << endl;
	}
	cout << "==================================================" << endl;
	cout << setw(25) << left << "Total Retail Value:" << setw(20) << right << totalRetail << std::endl;
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void quantityReport()
{
	system("cls");
	bookSort("quantity");
	for (int i = 0; i < arraySize; i++) {
		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "Quantity:" << setw(20) << right << bookArray[i].getQuantity() << std::endl;
		cout << "==================================================" << endl;
	}
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void costReport()
{
	system("cls");
	bookSort("wholesale");
	for (int i = 0; i < arraySize; i++) {
		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "Wholesale Price:" << setw(20) << right << bookArray[i].getWholeSale() << std::endl;
		cout << "==================================================" << endl;
	}
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void ageReport()
{
	system("cls");
	bookSort("age");
	for (int i = 0; i < arraySize; i++) {
		std::cout << setfill('.') << setw(10) << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
		std::cout << setw(25) << left << "Date Added (mmddyyyy):" << setw(20) << right << bookArray[i].getDateAdded() << std::endl;
		cout << "==================================================" << endl;
	}
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}

