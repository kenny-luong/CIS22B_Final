#include "book.h" // update file path as needed

/*********************************
**			To-Do List
**
**	- Update directory #include for header file.
**
**
*********************************/

Book::Book(string theTitle,
		   string theISBN,
		   string theAuthor,
		   string thePublisher,
		   string theDateAdded,
		   double theRetail,
		   double, theWholeSale,
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