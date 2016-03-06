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
