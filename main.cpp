#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//added iomanip for fancy shmancy output formatting in displayBook()
#include <iomanip>
#include <string>
#include <fstream>
#include "book.h"
#include <cstdlib>
#include <ctime>

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
** - create interface and code cashier functionality
** - Need to include default options for all switch statements.
** - Check inputs to make sure all inputs are valid or are caught
** - Implement try-catch in all opening of files.
**********************
**   Cosmetic To-Do List - gotta make dat shit pretty
**  [ ] cashier menu
**  [ ] addBook() [not really necessary]
**  [ ] editBook() [not really necessary]
**  [ ] deleteBook() [not really necessary]
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

string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
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
	fstream log;
	log.open("log.txt", ios::app);

	int cashierExit = 0;
	int *bookQuantity = new int[cartSize];
	int quantity;
	int counter = 0;

	do {
		system("CLS");
		cout << endl << endl << endl << endl << endl;
		cout << setw(50) << "Serendipity Booksellers" << endl;
		cout << setw(45) << "Cashier Module" << endl;
		cout << endl;
		cout << setw(46) << "1. Add to Purchase" << endl;
		cout << setw(50) << "2. Process Transaction" << endl;
		cout << setw(50) << "3. Return to main menu" << endl;
		cout << endl << endl;
		cout << setw(47) << "Enter your choice: ";
		int cashierChoice;
		cin >> cashierChoice;
		cin.ignore();
		system("CLS");

		switch (cashierChoice) {
		case 1:{   // add to purchase
			bool addAnother = true;
			do {
				char repeat;
				string query;
				cout << "Enter the title or ISBN: ";
				getline(cin, query);

				int position = searchBook(query);
				if (position != -1) {
					cout << "Enter the quantity: ";

					cin >> quantity;
					cin.ignore();

					if (quantity > bookArray[position].getQuantity()) {
						cout << "We only currently have " << bookArray[position].getQuantity() << " in stock." << endl;
						cout << "Book was not added to cart." << endl;
					} else {
						addToCart(position);
						bookQuantity[counter] = quantity;
						counter++;
					}


					bool validResponse = false;
					while (validResponse == false) {
						cout << "Would you like to add another book? (Y/N): ";
						cin >> repeat;
						cin.ignore();
						switch(repeat) {
							case 'Y':
							case 'y':
								validResponse = true;

								break;
							case 'N':
							case 'n': {
								validResponse = true;
								addAnother = false;
								counter++;
								break;
							}
							default: {
								cout << "That was not a valid input." << endl;
									break;
							}
						}
					}
				} else {
                    cout << "Sorry. We could not find that book in our inventory." << endl;
				}
			} while (addAnother == true);
			break;
		}
		case 2: { // process transaction
					double subtotal = 0, total, taxes, payment, change;

                    cout << "Current Date: " << currentDateTime() << endl << endl;
                    cout << left << setw(8) << "Count: " << setw(15) << "ISBN: "
                        << setw(25) << "Title: " << setw(13) << right
                        << "Retail Price: " << setw(13) << "Total: " << endl;
                    log << "Current Date: " << currentDateTime() << endl << endl;
                    log << left << setw(8) << "Count: " << setw(15) << "ISBN: "
                        << setw(25) << "Title: " << setw(13) << right
                        << "Retail Price: " << setw(13) << "Total: " << endl;


                    for (int i = 0; i < cartSize; i++)
                    {
                        cout << right << setw(5) << bookQuantity[i] << "   " << setw(15) << left<< cart[i].getISBN()
                            << setw(25) << cart[i].getTitle() << setw(13) << right
                            << cart[i].getRetail() << setw(13) << bookQuantity[i] * cart[i].getRetail() << endl;

                        log << right << setw(5) << bookQuantity[i] << "   " << setw(15) << cart[i].getISBN()
                            << setw(25) << cart[i].getTitle() << setw(13) << right
                            << cart[i].getRetail() << setw(13) << bookQuantity[i] * cart[i].getRetail() << endl;

                        subtotal += (cart[i].getRetail() * bookQuantity[i]);
                    }

                    taxes = 0.0875 * subtotal;
                    total = taxes + subtotal;

                    cout << endl << setw(66) << "Subtotal: " << setw(8) << fixed << setprecision(2) << subtotal << endl;
                    log << endl << setw(66) << "Subtotal: " << setw(8) << fixed << setprecision(2) << subtotal << endl;
                    cout << setw(66) << "Taxes: " << setw(8) << setprecision(2) << taxes << endl;
                    log << setw(66) << "Taxes: " << setw(8) << setprecision(2) << taxes << endl;
                    cout << setw(66) << "Total: " << setw(8) << setprecision(2) << total << endl;
                    log << setw(66) << "Total: " << setw(8) << setprecision(2) << total << endl;

                    bool validPayment = false;

                    do {
                        cout << endl << "Enter the amount of payment: ";
                        cin >> payment;
                        cin.ignore();
                        if (payment < total) {
                            cout << "Payment is not enough." << endl;
                        } else {
                            validPayment = true;
                            for (int i = 0; i < cartSize; i++) {
                                int position = searchBook(cart[i].getTitle());
                                int newQuantity = bookArray[position].getQuantity() - bookQuantity[i];
                                bookArray[position].setQuantity(newQuantity);
                                if (bookArray[position].getQuantity() < 0) {
                                    bookArray[position].setQuantity(0);
                                }
                            }
                        }
                    } while (validPayment == false);


                    log << setw(30) << "Payment: " << setw(8) << setprecision(2) << payment << endl;

                    change = payment - total;

                    cout << setw(66) << "Change: " << setw(8) << change << endl;
                    log << setw(66) << "Change: " << setw(8) << change << endl << endl;

                    counter = 0;
                    subtotal = 0;

                    cout << endl << "Press enter to return to the Cashier menu";
                    getline(cin, emptyStr);

                    saveBook();
                    delete [] cart;
                    cartSize = 0;
                    cart = new Book[cartSize];
                    break;
		}
		case 3: { //Exit back to the main menu
					cashierExit = 1;
					break;
		}
		default: {
					break;
		}
		}
	} while (cashierExit == 0);

	log.close();
}
void reportMenu()
{
	int reportExit = 0;
	do {
		system("CLS");
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
			default: {
				system("CLS");
				cout << "Not a valid option." << endl;
				system("Pause");
				break;
			}
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
		std::cout << setw(25) << left << "Quantity: " << setw(20) << right << bookArray[i].getQuantity() << std::endl;
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
		std::cout << setw(25) << left << "Quantity: " << setw(20) << right << bookArray[i].getQuantity() << std::endl;
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

