#define _CRT_SECURE_NO_WARNINGS
#include "book.h"

Book::Book(string theTitle,
	string theISBN,
	string theAuthor,
	string thePublisher,
	string theDateAdded,
	double theRetail,
	double theWholeSale,
	int theQuantity) {
	title = theTitle;
	isbn = theISBN;
	author = theAuthor;
	publisher = thePublisher;
	dateAdded = theDateAdded;
	retail = theRetail;
	wholesale = theWholeSale;
	quantity = theQuantity;
}

void Book::setTitle(string theTitle) {
	title = theTitle;
}

void Book::setISBN(string theISBN) {
	isbn = theISBN;
}

void Book::setAuthor(string theAuthor) {
	author = theAuthor;
}

void Book::setPublisher(string thePublisher) {
	publisher = thePublisher;
}

void Book::setDateAdded(string theDateAdded) {
	dateAdded = theDateAdded;
}

void Book::setRetail(double theRetail) {
	retail = theRetail;
}

void Book::setWholeSale(double theWholeSale) {
	wholesale = theWholeSale;
}

void Book::setQuantity(int theQuantity) {
	quantity = theQuantity;
}

string Book::getTitle() {
	return title;
}

string Book::getISBN() {
	return isbn;
}

string Book::getAuthor() {
	return author;
}

string Book::getPublisher() {
	return publisher;
}

string Book::getDateAdded() {
	return dateAdded;
}

double Book::getRetail() {
	return retail;
}

double Book::getWholeSale() {
	return wholesale;
}

int Book::getQuantity() {
	return quantity;
}

bool isOlder(const Book& b1, const Book& b2) {
	if (stoi(b1.dateAdded.substr(4, 4)) < stoi(b2.dateAdded.substr(4, 4)))
	{
		return true;
	}
	else if (stoi(b1.dateAdded.substr(4, 4)) == stoi(b2.dateAdded.substr(4, 4))) {
		if (stoi(b1.dateAdded.substr(0, 2)) < stoi(b2.dateAdded.substr(0, 2))) {
			return true;
		}
		else if (stoi(b1.dateAdded.substr(0, 2)) == stoi(b2.dateAdded.substr(0, 2))) {
			if (stoi(b1.dateAdded.substr(2, 2)) < stoi(b2.dateAdded.substr(2, 2))) {
				return true;
			}
		}
	}
	return false;
}

ostream& operator<<(ostream& os, const Book& b) {
	os << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << b.title << endl;
	os << setw(25) << left << "ISBN:" << setw(40) << right << b.isbn << endl;
	os << setw(25) << left << "Author:" << setw(40) << right << b.author << endl;
	os << setw(25) << left << "Publisher:" << setw(40) << right << b.publisher << endl;
	os << setw(25) << left << "Date Added (mmddyyyy):" << setw(40) << right << b.dateAdded << endl;
	os << setw(25) << left << "Retail Price:" << setw(40) << right << b.retail << endl;
	os << setw(25) << left << "Wholesale Price:" << setw(40) << right << b.wholesale << endl;
	os << setw(25) << left << "Quantity in inventory:" << setw(40) << right << b.quantity << endl;
	os << setfill(' ');

	return os;
}
