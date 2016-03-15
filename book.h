#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Book {
private:
protected:
	string title;
	string isbn;
	string author;
	string publisher;
	string dateAdded;
	double retail;
	double wholesale;
	int quantity;
public:
	Book() {
		title = "MISSING";
		isbn = "MISSING";
		author = "MISSING";
		publisher = "MISSING";
		dateAdded = "MISSING";
		retail = -1.0;
		wholesale = -1.0;
		quantity = -1;
	}
	Book(string, // title
		string, // isbn
		string, // author
		string, // publisher
		string, // dateAdded
		double, // retail
		double, // wholesale
		int); // quantity
	void setTitle(string);
	void setISBN(string);
	void setAuthor(string);
	void setPublisher(string);
	void setDateAdded(string);
	void setRetail(double);
	void setWholeSale(double);
	void setQuantity(int);
	string getTitle();
	string getISBN();
	string getAuthor();
	string getPublisher();
	string getDateAdded();
	double getRetail();
	double getWholeSale();
	int getQuantity();
	friend bool isOlder(const Book&, const Book&);
	friend ostream& operator<<(ostream&, const Book&);
};

#endif
