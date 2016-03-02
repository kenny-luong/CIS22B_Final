#include "book.h" // update file path as needed

/*********************************
**			To-Do List
**
**	- Update directory #include for header file.
**
**
*********************************/

Book::Book(std::string theTitle,
		   std::string theISBN,
		   std::string theAuthor,
		   std::string thePublisher,
		   std::string theDateAdded,
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

void Book::setTitle(std::string theTitle) {
	title = theTitle;
}

void Book::setISBN(std::string theISBN) {
	isbn = theISBN;
}

void Book::setAuthor(std::string theAuthor) {
	author = theAuthor;
}

void Book::setPublisher(std::string thePublisher) {
	publisher = thePublisher;
}

void Book::setDateAdded(std::string theDateAdded) {
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

std::string Book::getTitle() {
	return title;
}

std::string Book::getISBN() {
	return isbn;
}

std::string Book::getAuthor() {
	return author;
}

std::string Book::getPublisher() {
	return publisher;
}

std::string Book::getDateAdded() {
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