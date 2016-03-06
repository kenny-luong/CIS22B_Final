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

//GLOBALS

int sizeOfArray();

int size = sizeOfArray();
Book *tempBook = new Book;

Book *array = new Book[size];

void loadBook();

void displayBook(int i) {
    if (i == -1) {
    	std::cout << "Book was not found." << std::endl;
    } else {
	    std::cout << array[i].getTitle() << std::endl;
	    std::cout << array[i].getISBN() << std::endl;
	    std::cout << array[i].getAuthor() << std::endl;
	    std::cout << array[i].getPublisher() << std::endl;
	    std::cout << array[i].getDateAdded() << std::endl;
	    std::cout << array[i].getRetail() << std::endl;
	    std::cout << array[i].getWholeSale() << std::endl;
	    std::cout << array[i].getQuantity() << std::endl;
    }
}

int searchBook(std::string searchCriteria) {
	for (int i = 0; i < size; i++) {
		if (searchCriteria == array[i].getTitle() || searchCriteria == array[i].getISBN()) {
            return i;
		}
	}
	return -1;
}

int main () {
    loadBook();
    std::string input;
    std::cout << "Search by ISBN or title: " << std::endl;
    std::getline(cin, input);

    displayBook(searchBook(input));
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

	while(i < size) {
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

		array[i] = *tempBook;
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
void addBook()
{
	int newsize = size + 1;
	Book *temparray = new Book[newsize];
    Book *garbage = new Book;
	for (int count = 0; count < size; count++)
	{
        if (!(count == size)) {
            temparray[count] = array[count];
        } else {
            temparray[count] = *garbage;
        }
	}

	delete[] array;


	//temporary variables for text entry
	//there's probably a cleaner way
	string temptitle, tempisbn, tempauthor, temppublisher, tempdate;
	double tempretail, tempwholesale;
	int tempquantity;

	//prompting and setting values to new entry
	cout << "Title: ";
	getline(cin, temptitle);
	temparray[size].setTitle(temptitle);
	cout << endl << "ISBN: ";
	getline(cin, tempisbn);
	temparray[size].setISBN(tempisbn);
	cout << endl << "Author: ";
	getline(cin, tempauthor);
	temparray[size].setAuthor(tempauthor);
	cout << endl << "Publisher: ";
	getline(cin, temppublisher);
	temparray[size].setPublisher(temppublisher);
	cout << endl << "Date added: ";
	getline(cin, tempdate);
	temparray[size].setDateAdded(tempdate);
	cout << endl << "Retail Price: ";
	cin >> tempretail;
	cin.ignore();
	temparray[size].setRetail(tempretail);
	cout << endl << "Wholesale Price: ";
	cin >> tempwholesale;
	temparray[size].setWholeSale(tempwholesale);
	cout << endl << "Quantity: ";
	cin >> tempquantity;
	temparray[size].setQuantity(tempquantity);

    array = temparray;
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
	size = newsize;


}
