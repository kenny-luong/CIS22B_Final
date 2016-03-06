#include <iostream>
#include <string>
#include <fstream>
#include "book.h"

/*********************
**		To-Do List
**
** - Rename variables. Some of them are unclear.
** -
**********************/

using namespace std;

//GLOBALS

int sizeOfArray();
void addBook();
void editBook();

int arraySize = sizeOfArray();
Book *tempBook = new Book;

Book *bookArray = new Book[arraySize];

void loadBook();

//note:changed displayBook() return type to be able to determine whether editBook() can continue
//displayBook() now returns the location/not-found flag, for purpose see editBook()
//-William

int displayBook(int i) {
    if (i == -1) {
    	std::cout << "Book was not found." << std::endl;
    } else {
	    std::cout << bookArray[i].getTitle() << std::endl;
	    std::cout << bookArray[i].getISBN() << std::endl;
	    std::cout << bookArray[i].getAuthor() << std::endl;
	    std::cout << bookArray[i].getPublisher() << std::endl;
	    std::cout << bookArray[i].getDateAdded() << std::endl;
	    std::cout << bookArray[i].getRetail() << std::endl;
	    std::cout << bookArray[i].getWholeSale() << std::endl;
	    std::cout << bookArray[i].getQuantity() << std::endl;
    }
	//added return
	return i;
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
    std::string input;
    std::cout << "Search by ISBN or title: " << std::endl;
    std::getline(cin, input);

    displayBook(searchBook(input));
	//tests add module
	addBook();
	//tests edit module
	editBook();
	system("pause");
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
void output()
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
	output();

}
// outputs data from existing bookArray to books.txt

//place function call at the end of addBook() to ensure up-to-date info

//and wherever else a full array-to-file dump is necessary



void editBook()
{
	int repeat = 0;
	do {
		//grabbed prompt for search from main()
		string editQuery;
		std::cout << "Please enter title or ISBN to edit: " << std::endl;
		cin.ignore();
		std::getline(cin, editQuery);
		//function calls
		int location;
		//should display all info of match, better for user interactivity, I guess
		location = displayBook(searchBook(editQuery));

		if (location != -1)
		{
			int selection;
			std::cout << "Please select attribute to edit: ";
			cout << "1) Title" << endl;
			cout << "2) ISBN" << endl;
			cout << "3) Author" << endl;
			cout << "4) Publisher" << endl;
			cout << "5) Date added" << endl;
			cout << "6) Retail Price" << endl;
			cout << "7) Wholesale price" << endl;
			cout << "8) Quantity in inventory" << endl;
			cout << "9) Multiple or all attributes" << endl;
			cin >> selection;
			cin.ignore();
			//declaring temp vars for editing input
			string newTitle, newISBN, newAuthor, newPublisher, newDateAdded;
			double newRetail, newWholeSale;
			int newQuantity;
			switch (selection)
			{
			case 1:
				cout << "Please enter new title: ";
				getline(cin, newTitle);
				bookArray[location].setTitle(newTitle);
				break;
			case 2:
				cout << "Please enter new ISBN: ";
				getline(cin, newISBN);
				bookArray[location].setISBN(newISBN);
				break;
			case 3:
				cout << "Please enter new author: ";
				getline(cin, newAuthor);
				bookArray[location].setAuthor(newAuthor);
				break;
			case 4:
				cout << "Please enter new publisher: ";
				getline(cin, newPublisher);
				bookArray[location].setPublisher(newPublisher);
				break;
			case 5:
				cout << "Please enter new date added: ";
				getline(std::cin, newDateAdded);
				bookArray[location].setDateAdded(newDateAdded);
				break;
			case 6:
				cout << "Please enter new retail price (in <dollars>.<cents> format): ";
				cin >> newRetail;
				bookArray[location].setRetail(newRetail);
				break;
			case 7:
				cout << "Please enter new wholesale price (in <dollars>.<cents> format): ";
				cin >> newWholeSale;
				bookArray[location].setWholeSale(newWholeSale);
				break;
			case 8:
				cout << "Please enter updated amount in inventory: ";
				cin >> newQuantity;
				bookArray[location].setQuantity(newQuantity);
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
				bookArray[location].setTitle(newTitle);
				bookArray[location].setISBN(newISBN);
				bookArray[location].setAuthor(newAuthor);
				bookArray[location].setPublisher(newPublisher);
				bookArray[location].setDateAdded(newDateAdded);
				bookArray[location].setRetail(newRetail);
				bookArray[location].setWholeSale(newWholeSale);
				bookArray[location].setQuantity(newQuantity);
			}
			//calls output info to update books.txt
			output();
			//prompts for value to decide whether to exit do-while loop
			cout << "Enter 1 to edit another entry, or enter 0 to exit editing module." << endl;
			cin >> repeat;
		}
	}while (repeat != 0);
}
