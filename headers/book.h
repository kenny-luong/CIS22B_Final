#include <iostream>
#include <string>

class Book {
	private:
	protected:
		std::string title;
		std::string isbn;
		std::string author;
		std::string publisher;
		std::string dateAdded;
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
		Book (std::string, // title
			  std::string, // isbn
			  std::string, // author
			  std::string, // publisher
			  std::string, // dateAdded
			  double, // retail
			  double, // wholesale
			  int); // quantity
		void setTitle(std::string);
		void setISBN(std::string);
		void setAuthor(std::string);
		void setPublisher(std::string);
		void setDateAdded(std::string);
		void setRetail(double);
		void setWholeSale(double);
		void setQuantity(int);
		std::string getTitle();
		std::string getISBN();
		std::string getAuthor();
		std::string getPublisher();
		std::string getDateAdded();
		double getRetail();
		double getWholeSale();
		int getQuantity();
};