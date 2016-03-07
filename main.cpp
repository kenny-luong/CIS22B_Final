#include <iostream>
//added iomanip for fancy shmancy output formatting in displayBook()
#include <iomanip>
#include <string>
#include <fstream>
#include "book.h"
#include <cstdlib>

/*********************
**		To-Do List
**
** - Rename variables. Some of them are unclear.
** - Fix cin.ignore()
**********************/

using namespace std;

//GLOBALS

int sizeOfArray();
void addBook();
void editBook();
void deleteBook();
void saveBook();
void loadBook();
void loadBook();

int arraySize = sizeOfArray();
Book *tempBook = new Book;

Book *bookArray = new Book[arraySize];



//note:changed displayBook() return type to be able to determine whether editBook() can continue
//displayBook() now returns the location/not-found flag, for purpose see editBook()
//-William

void displayBook(int i) {
    if (i == -1) {
    	std::cout << "Book was not found." << std::endl;
    } else {
	    std::cout << setw(25) << left << "Title:" << setw(20) << right << bookArray[i].getTitle() << std::endl;
	    std::cout << setw(25) << left << "ISBN:" << setw(20) << right << bookArray[i].getISBN() << std::endl;
	    std::cout << setw(25) << left << "Author:" << setw(20) << right << bookArray[i].getAuthor() << std::endl;
	    std::cout << setw(25) << left << "Publisher:" << setw(20) << right << bookArray[i].getPublisher() << std::endl;
	    std::cout << setw(25) << left << "Date Added:" << setw(20) << right << bookArray[i].getDateAdded() << std::endl;
	    std::cout << setw(25) << left << "Retail Price:" << setw(20) << right << bookArray[i].getRetail() << std::endl;
	    std::cout << setw(25) << left << "Wholesale Price:" << setw(20) << right << bookArray[i].getWholeSale() << std::endl;
	    std::cout << setw(25) << left << "Quantity in inventory:" << setw(20) << right << bookArray[i].getQuantity() << std::endl;
    }
	//added return
}

int searchBook(std::string searchCriteria) {
	for (int i = 0; i < arraySize; i++) {
		if (searchCriteria == bookArray[i].getTitle() || searchCriteria == bookArray[i].getISBN()) {
            return i;
		}
	}
	return -1;
}

//----------------------------------------
//-----------------MAIN-------------------
//----------------------------------------
int main () {
	loadBook();
    std::cout << "Serendipity Booksellers\n";
    std::cout << "Inventory Database\n" << endl;
    std::cout << "1. Look up a book\n";
    std::cout << "2. Add a book\n";
    std::cout <<"3. Edit a book\n";
    std::cout <<"4. Delete a book\n";
    std::cout <<"5. Close\n" << endl;
    std::cout <<"Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();
	system("CLS");
    switch (choice) {
    	case 1: { // look up a book
    		
    		std::string query;
    		std::cout << "Enter the title or ISBN of the book: ";
    		std::getline(std::cin, query);
    		displayBook(searchBook(query));
    	}
    		break;
    	case 2: { // Add a book
    		addBook();
    	}
    		break;
    	case 3: { // Edit a book
    		editBook();
    	}
    		break;
    	case 4: {
    		deleteBook();
    	}
    		break;
    	case 5:
    		break;
    	default:
    		break;
    }
}

void loadBook() {
    std::ifstream bookDatabase;
    bookDatabase.open("books.txt", std::ios::in);

	if (!bookDatabase.is_open()) {
		std::cout << "File could not be opened" << std::endl;
	} else {
		std::cout << "File was successfully opened." << std::endl;
	}

	std::string tempInput;

	bookDatabase.close();

	bookDatabase.open("books.txt", std::ios::in);

	int i = 0;
	double temp1;
	int temp2;
	std::string garbage;

	while(i < arraySize) {
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

int sizeOfArray() {
    std::ifstream inputFile;

    inputFile.open("books.txt", std::ios::in);

    std::string temp;
    int counter = 0;
    while (std::getline(inputFile, temp)) {
        counter++;
    }
    inputFile.close();
    return counter/8;
}
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

void addBook()
{
	int newsize = arraySize + 1;
	Book *temparray = new Book[newsize];
    Book *garbage = new Book;
	for (int count = 0; count < arraySize; count++)
	{
        if (!(count == arraySize)) {
            temparray[count] = bookArray[count];
        } else {
            temparray[count] = *garbage;
        }
	}

	delete[] bookArray;


	//temporary variables for text entry
	//there's probably a cleaner way
	string temptitle, tempisbn, tempauthor, temppublisher, tempdate;
	double tempretail, tempwholesale;
	int tempquantity;

	//prompting and setting values to new entry
	std::cout << "Title: ";
	std::getline(std::cin, temptitle);
	temparray[arraySize].setTitle(temptitle);
	std::cout << endl << "ISBN: ";
	std::getline(std::cin, tempisbn);
	temparray[arraySize].setISBN(tempisbn);
	std::cout << endl << "Author: ";
	std::getline(std::cin, tempauthor);
	temparray[arraySize].setAuthor(tempauthor);
	std::cout << endl << "Publisher: ";
	std::getline(std::cin, temppublisher);
	temparray[arraySize].setPublisher(temppublisher);
	std::cout << endl << "Date added: ";
	std::getline(std::cin, tempdate);
	temparray[arraySize].setDateAdded(tempdate);
	std::cout << endl << "Retail Price: ";
	std::cin >> tempretail;
	std::cin.ignore();
	temparray[arraySize].setRetail(tempretail);
	std::cout << endl << "Wholesale Price: ";
	std::cin >> tempwholesale;
	temparray[arraySize].setWholeSale(tempwholesale);
	std::cout << endl << "Quantity: ";
	std::cin >> tempquantity;
	temparray[arraySize].setQuantity(tempquantity);

    bookArray = temparray;
	//debug to test added element

	/*cout << array[size].getTitle() << std::endl;
	cout << array[size].getISBN() << std::endl;
	cout << array[size].getAuthor() << std::endl;
	cout << array[size].getPublisher() << std::endl;
	cout << array[size].getDateAdded() << std::endl;
	cout << array[size].getRetail() << std::endl;
	cout << array[size].getWholeSale() << std::endl;
	cout << array[size].getQuantity() << std::endl;*/

	//-debug-*/

	//update global size value
	arraySize = newsize;
	saveBook();
	displayBook(arraySize-1);
}
// outputs data from existing bookArray to books.txt

//place function call at the end of addBook() to ensure up-to-date info

//and wherever else a full array-to-file dump is necessary

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
			cout << "2) Return to previous screen"; // change line
			cin >> deleteSelect;
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
		} else {
            cout << "This is not working" << endl;
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
				cout << "Please enter new date added: ";
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
				cout << "Please enter new date added: ";
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
		}else {
				std::cout << "I didn't even try." << std::endl;
			}
	}while (repeat != 0);
}
