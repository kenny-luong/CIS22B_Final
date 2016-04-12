#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "book.h"
#include <cstdlib>
#include <ctime>
#include "employee.h"
#include "admin.h"
#include <cmath>
#include <conio.h>
#include <stdio.h>

// New line to code

/**********************
**      Error List
**
** 1. Missing books.txt
** 2. Missing admin.txt
** 3. Missing employee.txt
***********************/

using namespace std;

//menu prototypes
void inventoryMenu(int);
void cashierMenu();
void reportMenu();
//cashier protoype
void addToCart(int);
//inventory prototypes
void addBook();
void editBook();
void deleteBook();
void saveBook();
bool loadBook();
void displayBook(int);
//report prototypes
void inventoryReport();
void wholesaleReport();
void retailReport();
void quantityReport();
void costReport();
void ageReport();
//login prototype
int login();
int sizeOfAdmin();
int sizeOfEmployee();
void loadAdmin();
void loadEmployee();
//misc
int sizeOfArray();
int searchBook(string);
string currentDateTime();
string toLower(string);



//GLOBALS

string emptyStr; //used for menu navigation
int validLogin;
int arraySize = sizeOfArray();
int adminSize = sizeOfAdmin();
int employeeSize = sizeOfEmployee();
int cartSize = 0;
int currentEmployee;
Book *tempBook = new Book;
Book *bookArray = new Book[arraySize];
Book *cart = new Book[cartSize];
Admin *tempAdmin = new Admin;
Admin *admin = new Admin[adminSize];
Employee *employee = new Employee[employeeSize];
Employee  *tempEmployee = new Employee;


template <class T>

void addToArray(T &arrayName, int &arraySize) {
	int newArraySize = arraySize + 1;
	Book *tempArray = new Book[newArraySize];

	for (int count = 0; count < arraySize; count++) {
		tempArray[count] = arrayName[count];
	}

	delete[] arrayName;

	arraySize = newArraySize;
	arrayName = tempArray;
}

//----------------------------------------
//-----------------MAIN-------------------
//----------------------------------------
int main() {

	if (!loadBook()) {
		return 0;
	}

	loadAdmin();
	loadEmployee();
	cout << admin[0].getUsername() << endl << admin[0].getPassword() << endl << admin[0].getAdminCode() << endl;
	bool isValid = false, loginScreen = true;

	do {
		isValid = false;
		do {
			validLogin = login();
			switch (validLogin) {
			case 1:
				isValid = true;
				break;
			case 2:
				isValid = true;
				break;
			case 3: {
						cout << endl << endl << setw(50) << "Invalid login details." << endl;
						system("PAUSE");
						break;
			}
			}
		} while (isValid == false);

		int x = 1;
		int mainChoice = 0;
		do{
			system("cls");
			cout << "Current user: ";
			(validLogin == 1) ? cout << admin[currentEmployee].getUsername() : cout << employee[currentEmployee].getUsername();
			cout << endl << endl << endl << endl << endl;
			cout << setw(50) << "Serendipity Booksellers" << endl;
			cout << setw(43) << "Main Menu" << endl << endl;
			cout << setw(49) << "1. Inventory Database" << endl;
			cout << setw(48) << "2. Cashier Interface" << endl;
			cout << setw(38) << "3. Reports" << endl;
			cout << setw(37) << "4. Logout" << endl;
			cout << setw(43) << "5. Exit Program" << endl;
			cout << endl << endl;
			cout << setw(47) << "Enter your choice: ";

			if (cin >> mainChoice) {
				system("cls");
				switch (mainChoice)
				{
				case 1:
					inventoryMenu(validLogin);
					break;
				case 2:
					cashierMenu();
					break;
				case 3:
					reportMenu();
					break;
				case 4:
					x = 2;
					break;
				case 5:
					return 0;
				default: {
							 cout << "Invalid option." << endl;
							 break;
				}
				}
			}
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Not a valid input." << endl;
			}
		} while (x == 1);
	} while (loginScreen == true);

}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************
**          Main Menu Functions
********************************************/
void inventoryMenu(int validLogin)
{
	int inventoryExit = 0;
	do {
		system("CLS");
		cout << endl << endl << endl << endl << endl;
		cout << setw(50) << "Serendipity Booksellers" << endl;
		cout << setw(47) << "Inventory Database" << endl;
		cout << endl;
		cout << setw(46) << "1. Look up a book" << endl;
		cout << setw(42) << "2. Add a book" << endl;
		cout << setw(43) << "3. Edit a book" << endl;
		cout << setw(45) << "4. Delete a book" << endl;
		cout << setw(51) << "5. Return to main menu" << endl;
		cout << endl << endl;
		cout << setw(47) << "Enter your choice: ";
		int inventoryChoice;
		if (cin >> inventoryChoice) {
			cin.ignore();
			system("CLS");
			switch (inventoryChoice) {
			case 1:{   // look up a book
					   string query;
					   cout << "Enter the title or ISBN of the book: ";
					   getline(cin, query);
					   displayBook(searchBook(query));
					   cout << endl << "Press enter to return to the inventory menu";
					   getline(cin, emptyStr);
					   break;
			}
			case 2:{  // Add a book
					   if (validLogin == 1) {
						   addBook();
						   cout << endl << "Press enter to return to the inventory menu";
						   getline(cin, emptyStr);
					   }
					   else {
						   cout << "Only administrators can access this." << endl;
						   system("PAUSE");
					   }
					   break;
			}

			case 3: { // Edit a book
						if (validLogin == 1) {
							editBook();
							cout << endl << "Press enter to return to the inventory menu";
							getline(cin, emptyStr);
						}
						else {
							cout << "Only administrators can access this." << endl;
							system("PAUSE");
						}
						break;
			}
			case 4: { //Delete a book
						if (validLogin == 1) {
							deleteBook();
						}
						else {
							cout << "Only administrators can access this." << endl;
							system("PAUSE");
						}

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
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (inventoryExit == 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void cashierMenu()
{
	int cashierExit = 0;
	fstream log;
	try {
		log.open("log.txt", ios::app);
		if (!log.is_open()) {
			throw 1;
		}
	}
	catch (int x) {
		cout << "Error: " << x << ". File could not be opened." << endl;
		cashierExit = 1;
	}

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
		if (cin >> cashierChoice) {
			system("CLS");
			cin.ignore();

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
							   }
							   else if (quantity <= 0) {
								   cout << "Book was not added to cart." << endl;
								   cout << "Quantity must be minimum of 1." << endl;
							   }
							   else {
								   addToCart(position);
								   bookQuantity[counter] = quantity;
								   counter++;
							   }

							   bool validResponse = false;
							   while (validResponse == false) {
								   cout << "Would you like to add another book? (Y/N): ";
								   cin >> repeat;
								   switch (repeat) {
								   case 'Y':
								   case 'y':
								   	   cin.clear();
									   cin.ignore(1000, '\n');
									   validResponse = true;
									   break;
								   case 'N':
								   case 'n': {
								   		cin.clear();
							   			cin.ignore(1000, '\n');
										validResponse = true;
										addAnother = false;
										break;
								   }
								   default: {
												cout << "That was not a valid input." << endl;
												cin.clear();
												cin.ignore(1000, '\n');
												break;
								   }
								   }
							   }
						   }
						   else {
							   cout << "Sorry. We could not find that book in our inventory." << endl;
						   }
					   } while (addAnother == true);
					   break;
			}
			case 2: { // process transaction
						if (cartSize != 0) {
							bool validPayment = false;
							double subtotal = 0, total, taxes, payment, change;
							do {
								system("CLS");
								total = 0;
								subtotal = 0;
								cout << "Current Date: " << currentDateTime() << endl << endl;
								cout << left << setw(8) << "Count: " << setw(15) << "ISBN: "
									<< setw(25) << "Title: " << setw(13) << right
									<< "Retail Price: " << setw(13) << "Total: " << endl;
								log << "User: ";
								(validLogin == 1) ? log << admin[currentEmployee].getUsername() << endl : log << employee[currentEmployee].getUsername() << endl;
								log << "Current Date: " << currentDateTime() << endl << endl;
								log << left << setw(8) << "Count: " << setw(15) << "ISBN: "
									<< setw(25) << "Title: " << setw(13) << right
									<< "Retail Price: " << setw(13) << "Total: " << endl;


								for (int i = 0; i < cartSize; i++)
								{
									cout << right << setw(5) << bookQuantity[i] << "   " << setw(15) << left << cart[i].getISBN()
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




								cout << endl << "Enter the amount of payment: ";
								if (cin >> payment) {
									cin.ignore();
									if (payment < ((round(total*100.0)) / 100 - 0.01)) {
										cout << "Payment is not enough." << endl;
										system("PAUSE");
									}
									else {
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
								}
								else {
									cin.clear();
									cin.ignore(1000, '\n');
								}
								log << setw(30) << "Payment: " << setw(8) << setprecision(2) << payment << endl;

								change = payment - total;

								cout << setw(66) << "Change: " << setw(8) << change << endl;
								log << setw(66) << "Change: " << setw(8) << change << endl << endl;
							} while (validPayment == false);

							counter = 0;
							subtotal = 0;
							saveBook();
							delete[] cart;

							cartSize = 0;
							cart = new Book[cartSize];

							cout << endl << "Press enter to return to the Cashier menu";
							getline(cin, emptyStr);
							break;
						}
						else {
							cout << "You have no items in the cart." << endl;
							cout << "Please add an item in your cart to checkout." << endl;
							system("PAUSE");
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
			}
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (cashierExit == 0);

	log.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void reportMenu()
{
	int reportExit = 0;
	do {
		system("CLS");
		cout << endl << endl << endl << endl << endl;
		cout << setw(50) << "Serendipity Booksellers" << endl;
		cout << setw(47) << "Report Generator" << endl;
		cout << endl;
		cout << setw(47) << "Select the report" << endl;
		cout << setw(49) << "you want to generate" << endl;
		cout << endl;
		cout << setw(47) << "1. Inventory Listing" << endl;
		cout << setw(55) << "2. Inventory Wholesale Value" << endl;
		cout << setw(52) << "3. Inventory Retail Value" << endl;
		cout << setw(49) << "4. Listing by Quantity" << endl;
		cout << setw(45) << "5. Listing by Cost" << endl;
		cout << setw(44) << "6. Listing by Age" << endl;
		cout << setw(49) << "7. Return to Main Menu" << endl;
		cout << endl << endl;
		cout << setw(47) << "Enter your choice: ";
		int reportChoice = 0;
		if (cin >> reportChoice) {
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
						 cout << "Not a valid option." << endl;
						 break;
			}
			}
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (reportExit == 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************
**      Cash Register Functions
*********************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
void addToCart(int position) {
	if (position != -1) {
		addToArray(cart, cartSize);
		cart[cartSize - 1] = bookArray[position];
	}
	else {
		cout << "Unable to add to cart." << endl;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/********************************
**      Inventory Functions
*********************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
void addBook()
{
	addToArray(bookArray, arraySize);

	string temptitle, tempisbn, tempauthor, temppublisher, tempdate;
	double tempretail, tempwholesale;
	int tempquantity;
	bool validISBN = false,
		//validDate = false,
		validQuantity = false,
		validWholeSale = false,
		validRetail = false;

	cout << "Title: ";
	getline(cin, temptitle);


	do {
		cout << endl << "ISBN: ";
		getline(cin, tempisbn);
		if (tempisbn.length() == 11 || tempisbn.length() == 13) {

			validISBN = true;
		}
		else {
			cout << "Invalid ISBN. ISBN must be 11 or 13 digits." << endl;
		}
	} while (validISBN == false);

	cout << endl << "Author: ";
	getline(cin, tempauthor);

	cout << endl << "Publisher: ";
	getline(cin, temppublisher);


	cout << endl << "Date added (mmddyyyy): ";
	getline(cin, tempdate);


	do {
		cout << endl << "Retail Price: ";
		cin >> tempretail;
		if (cin.good()) {
			if (tempretail > 0) {
				cin.ignore();
				validRetail = true;
			}
			else if (tempretail < 0) {
				cout << "Minimum value of 0.00." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else {
			cout << "Not a valid retail price." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (validRetail == false);


	do {
		cout << endl << "Wholesale Price: ";
		cin >> tempwholesale;
		if (cin.good()) {
			if (tempwholesale > 0) {
				cin.ignore();
				validWholeSale = true;
			}
			else if (tempwholesale < 0) {
				cout << "Minimum value of 0.00." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else {
			cout << "Not a valid wholesale price." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (validWholeSale == false);

	do {
		cout << endl << "Quantity: ";
		cin >> tempquantity;
		if (cin.good()) {
			if (tempquantity > 0) {
				cin.ignore();
				validQuantity = true;
			}
			else if (tempquantity < 0){
				cout << "Minimum value of 0." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else {
			cout << "Not a valid quantity." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}

	} while (validQuantity == false);

	string adminCode;
	bool isValid = false;
	do {
		cout << "Enter Admin Code to verify (enter 'x' to exit): ";
		cin >> adminCode;
		if (adminCode == admin[currentEmployee].getAdminCode()) {
			isValid = true;
			bookArray[arraySize - 1].setTitle(temptitle);
			bookArray[arraySize - 1].setISBN(tempisbn);
			bookArray[arraySize - 1].setAuthor(tempauthor);
			bookArray[arraySize - 1].setPublisher(temppublisher);
			bookArray[arraySize - 1].setDateAdded(tempdate);
			bookArray[arraySize - 1].setRetail(tempretail);
			bookArray[arraySize - 1].setWholeSale(tempwholesale);
			bookArray[arraySize - 1].setQuantity(tempquantity);
			saveBook();
			cout << endl << endl;
			cout << "----------------" << bookArray[arraySize - 1].getTitle() << " ADDED----------------" << endl;
			displayBook(arraySize - 1);
			system("PAUSE");
		}
		else if (adminCode == "x" || adminCode == "X") {
			isValid = true;
			break;
		}
	} while (isValid == false);


}
///////////////////////////////////////////////////////////////////////////////////////////////////
void editBook()
{
	bool repeat = true;
	do {
		system("CLS");
		string editQuery;
		cout << "Please enter title or ISBN to edit: " << endl;

		getline(cin, editQuery);

		int editLocation;

		editLocation = searchBook(editQuery);

		if (editLocation != -1)
		{
			bool screenRepeat = true;
			int editSelect;
			do {
				system("CLS");
				cout << "Please select attribute to edit: " << endl;
				cout << "1) Title" << endl;
				cout << "2) ISBN" << endl;
				cout << "3) Author" << endl;
				cout << "4) Publisher" << endl;
				cout << "5) Date added" << endl;
				cout << "6) Retail Price" << endl;
				cout << "7) Wholesale price" << endl;
				cout << "8) Quantity in inventory" << endl;
				cout << "9) All attributes" << endl;
				cout << "0) Cancel..." << endl << endl;
				cout << "Enter your choice: ";
				if (cin >> editSelect) {
					cin.ignore();
					string newTitle, newISBN, newAuthor, newPublisher, newDateAdded;
					double newRetail, newWholeSale;
					int newQuantity;
					switch (editSelect)
					{
					case 1: {
								cout << "Please enter new title: ";
								getline(cin, newTitle);
								string adminCode;
								bool isValid = false;
								do {
									cout << "Enter Admin Code to verify (enter 'x' to exit): ";
									cin >> adminCode;
									if (adminCode == admin[currentEmployee].getAdminCode()) {
										isValid = true;
										bookArray[editLocation].setTitle(newTitle);
										saveBook();
									}
									else if (adminCode == "x" || adminCode == "X") {
										isValid = true;
									}
								} while (isValid == false);
					}
						break;
					case 2: {
								bool validISBN = false;
								do {
									cout << endl << "ISBN: ";
									getline(cin, newISBN);
									if (newISBN.length() == 11 || newISBN.length() == 13) {
										validISBN = true;
										string adminCode;
										bool isValid = false;
										do {
											cout << "Enter Admin Code to verify (enter 'x' to exit): ";
											cin >> adminCode;
											if (adminCode == admin[currentEmployee].getAdminCode()) {
												isValid = true;
												bookArray[editLocation].setISBN(newISBN);
												saveBook();
											}
											else if (adminCode == "x" || adminCode == "X") {
												isValid = true;
											}
										} while (isValid == false);

									}
									else {
										cout << "Invalid ISBN. ISBN must be 11 or 13 digits." << endl;
									}
								} while (validISBN == false);
								break;
					}
					case 3: {
								cout << "Please enter new author: ";
								getline(cin, newAuthor);
								string adminCode;
								bool isValid = false;
								do {
									cout << "Enter Admin Code to verify (enter 'x' to exit): ";
									cin >> adminCode;
									if (adminCode == admin[currentEmployee].getAdminCode()) {
										isValid = true;
										bookArray[editLocation].setAuthor(newAuthor);
										saveBook();
									}
									else if (adminCode == "x" || adminCode == "X") {
										isValid = true;
									}
								} while (isValid == false);
					}
						break;
					case 4: {
								cout << "Please enter new publisher: ";
								getline(cin, newPublisher);
								string adminCode;
								bool isValid = false;
								do {
									cout << "Enter Admin Code to verify (enter 'x' to exit): ";
									cin >> adminCode;
									if (adminCode == admin[currentEmployee].getAdminCode()) {
										isValid = true;
										bookArray[editLocation].setPublisher(newPublisher);
										saveBook();
									}
									else if (adminCode == "x" || adminCode == "X") {
										isValid = true;
									}
								} while (isValid == false);
					}
						break;
					case 5: {
								cout << "Please enter new date added (mmddyyyy): ";
								getline(cin, newDateAdded);
								string adminCode;
								bool isValid = false;
								do {
									cout << "Enter Admin Code to verify (enter 'x' to exit): ";
									cin >> adminCode;
									if (adminCode == admin[currentEmployee].getAdminCode()) {
										isValid = true;
										bookArray[editLocation].setDateAdded(newDateAdded);
										saveBook();
									}
									else if (adminCode == "x" || adminCode == "X") {
										isValid = true;
									}
								} while (isValid == false);
					}
						break;
					case 6: {
								bool validRetail = false;
								do {
									cout << endl << "Please enter a retail price: ";
									cin >> newRetail;
									if (cin.good()) {
										if (newRetail > 0) {
											cin.ignore();
											validRetail = true;
											string adminCode;
											bool isValid = false;
											do {
												cout << "Enter Admin Code to verify (enter 'x' to exit): ";
												cin >> adminCode;
												if (adminCode == admin[currentEmployee].getAdminCode()) {
													isValid = true;
													bookArray[editLocation].setRetail(newRetail);
													saveBook();
												}
												else if (adminCode == "x" || adminCode == "X") {
													isValid = true;
												}
											} while (isValid == false);
										}
										else if (newRetail < 0) {
											cout << "Minimum value of 0.00." << endl;
											cin.clear();
											cin.ignore(1000, '\n');
										}
									}
									else {
										cin.clear();
										cin.ignore(1000, '\n');
										cout << "Not a valid retail price." << endl;
										newRetail = 0;
									}
								} while (validRetail == false);
								break;
					}

					case 7: {
								bool validWholeSale = false;
								do {
									cout << "Please enter new wholesale price: ";
									cin >> newWholeSale;
									if (cin.good()) {
										if (newWholeSale > 0) {
											cin.ignore();
											validWholeSale = true;
											string adminCode;
											bool isValid = false;
											do {
												cout << "Enter Admin Code to verify (enter 'x' to exit): ";
												cin >> adminCode;
												if (adminCode == admin[currentEmployee].getAdminCode()) {
													isValid = true;
													bookArray[editLocation].setWholeSale(newWholeSale);
													saveBook();
												}
												else if (adminCode == "x" || adminCode == "X") {
													isValid = true;
												}
											} while (isValid == false);
										}
										else if (newWholeSale < 0) {
											cout << "Minimum value of 0.00." << endl;
											cin.clear();
											cin.ignore(1000, '\n');
										}
									}
									else {
										cout << "Not a valid wholesale price." << endl;
										cin.clear();
										cin.ignore(1000, '\n');
									}
								} while (validWholeSale == false);
								break;
					}

					case 8: {
								bool validQuantity = false;
								do {
									cout << "Please enter a new quantity: ";
									cin >> newQuantity;
									if (cin.good() && newQuantity >= 0) {
										cin.ignore();
										validQuantity = true;
										string adminCode;
										bool isValid = false;
										do {
											cout << "Enter Admin Code to verify (enter 'x' to exit): ";
											cin >> adminCode;
											if (adminCode == admin[currentEmployee].getAdminCode()) {
												isValid = true;
												bookArray[editLocation].setQuantity(newQuantity);
												saveBook();
											}
											else if (adminCode == "x" || adminCode == "X") {
												isValid = true;
											}
										} while (isValid == false);
									}
									else if (newQuantity < 0) {
										cout << "Not a valid quantity." << endl;
										cout << "Quantity must be minimum of 0." << endl;
									}
									else {
										cout << "Not a valid quantity." << endl;
										cin.clear();
										cin.ignore(1000, '\n');
									}
								} while (validQuantity == false);
					}
						break;
					case 9: {
								bool validISBN = false, validWholeSale = false, validQuantity = false, validRetail = false;
								cout << "Now editing all attributes..." << endl;

								cout << "Please enter new title: ";
								getline(cin, newTitle);
								do {
									cout << "Please enter new ISBN: ";
									getline(cin, newISBN);
									if (newISBN.length() == 11 || newISBN.length() == 13) {
										validISBN = true;
									}
									else {
										cout << "Not a valid ISBN. ISBN must be 11 or 13 digits." << endl;
									}
								} while (validISBN == false);
								cout << "Please enter new author: ";
								getline(cin, newAuthor);
								cout << "Please enter new publisher: ";
								getline(cin, newPublisher);
								cout << "Please enter new date added (mmddyyyy): ";
								getline(cin, newDateAdded);
								do {
									cout << "Please enter new retail price: ";
									cin >> newRetail;
									if (cin.good()) {
										if (newRetail > 0) {
											cin.ignore();
											validRetail = true;
										}
										else if (newRetail < 0) {
											cout << "Minimum value of 0.00." << endl;
											cin.clear();
											cin.ignore();
										}
									}
									else {
										cin.clear();
										cin.ignore(1000, '\n');
										cout << "Not a valid retail price." << endl;
										cin.clear();
										cin.ignore(1000, '\n');
									}
								} while (validRetail == false);

								do {
									cout << "Please enter new wholesale price: ";
									cin >> newWholeSale;
									if (cin.good()) {
										if (newWholeSale > 0) {
											cin.ignore();
											validWholeSale = true;
										}
										else if (newWholeSale < 0) {
											cout << "Minimum value of 0.00." << endl;
											cin.clear();
											cin.ignore();
										}
									}
									else {
										cout << "Not a vaid wholesale price." << endl;
										cin.clear();
										cin.ignore(1000, '\n');
									}
								} while (validWholeSale == false);

								do {
									cout << "Please enter new quantity in inventory: ";
									cin >> newQuantity;
									if (cin.good()) {
										if (newQuantity > 0) {
											cin.ignore();
											validQuantity = true;
										}
										else if (newQuantity < 0) {
											cout << "Minimum value of 0." << endl;
											cin.clear();
											cin.ignore();
										}
									}
									else {
										cout << "Not a valid quantity." << endl;
										cin.clear();
										cin.ignore(1000, '\n');
									}
								} while (validQuantity == false);

								string adminCode;
								bool isValid = false;

								do {
									cout << "Enter Admin Code to verify (Enter 'x' to exit): ";
									cin >> adminCode;
									if (adminCode == admin[currentEmployee].getAdminCode()) {
										isValid = true;
										bookArray[editLocation].setTitle(newTitle);
										bookArray[editLocation].setISBN(newISBN);
										bookArray[editLocation].setAuthor(newAuthor);
										bookArray[editLocation].setPublisher(newPublisher);
										bookArray[editLocation].setDateAdded(newDateAdded);
										bookArray[editLocation].setRetail(newRetail);
										bookArray[editLocation].setWholeSale(newWholeSale);
										bookArray[editLocation].setQuantity(newQuantity);
										saveBook();
									}
								} while (isValid == false);

								break;
					}

					case 0:
						cout << "Cancelling..." << endl;
						screenRepeat = false;
						break;
					}


					char editAgain;
					cout << "\nWould you like to edit another entry? (Y/N): ";
					cin >> editAgain;
					cin.ignore();
					switch (editAgain) {
					case 'Y':
					case 'y':
						break;
					case 'N':
					case 'n':
						screenRepeat = false;
						repeat = false;
						break;
					default:
						break;
					}
				}
				else {
					cin.clear();
					cin.ignore(1000, '\n');
					system("CLS");
				}
			} while (screenRepeat == true);
		}
		else {
			cout << "Book was not found." << endl;
			system("pause");
		}
	} while (repeat == true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void deleteBook()
{
	char repeat;
	bool deleteRepeat = true;
	int deleteSelect = 0;
	do {
		system("CLS");
		string deleteQuery;
		cout << "Please enter title or ISBN to delete (enter '!' to exit): " << endl;
		getline(cin, deleteQuery);
		if (deleteQuery.at(0) == '!') {
			deleteRepeat = false;
			break;
		}
		int deleteLocation;

		deleteLocation = searchBook(deleteQuery);
		if (deleteLocation != -1)
		{
			cout << "Please select:" << endl;
			cout << "1) Remove all copies of " << bookArray[deleteLocation].getTitle() << endl;
			cout << "2) Return to previous screen" << endl;
			if (cin >> deleteSelect) {
				cin.ignore();
				switch (deleteSelect)
				{
				case 1: {
							string adminCode;
							bool isValid = false;
							do {
								cout << "Enter Admin Code to verify (enter 'x' to exit): ";
								cin >> adminCode;
								if (adminCode == admin[currentEmployee].getAdminCode()) {
									isValid = true;
									cout << "Removing all copies..." << endl;
									bookArray[deleteLocation].setQuantity(0);
									cout << "All copies removed." << endl;
									saveBook();
								}
								else if (adminCode == "x" || adminCode == "X") {
									isValid = true;
								}
							} while (isValid == false);
				}
					break;
				case 2:
					cout << "Cancelling..." << endl;
					break;
				}
				cout << "Would you like to delete another entry? (Y/N): " << endl;
				if (cin >> repeat) {
					cin.ignore();
					switch (repeat) {
					case 'Y':
					case 'y':
						break;
					case 'N':
					case 'n':
						deleteRepeat = false;
						break;
					default:
						break;
					}
				}
			}
			else {
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else {
			cout << "Book could not be found." << endl;
			system("pause");
		}
	} while (deleteRepeat == true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void saveBook()
{
	ofstream output;
	try {
		output.open("books.txt");
		if (!output.is_open()) {
			throw 1;
		}
	}
	catch (int x) {
		cout << "Error: " << x << ". books.txt is missing." << endl;
		cout << "Restart program and locate books.txt and replace." << endl;
	}
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
///////////////////////////////////////////////////////////////////////////////////////////////////
bool loadBook() {
	ifstream bookDatabase;
	try {
		bookDatabase.open("books.txt", ios::in);
		if (!bookDatabase.is_open()) {
			throw 1;
		}
	}
	catch (int x) {
		cout << "Error: " << x << ". books.txt could not be located." << endl;
		cout << "Program terminating..." << endl;
		system("pause");
		return 0;
	}

	string tempInput;

	bookDatabase.close();

	bookDatabase.open("books.txt", ios::in);

	int i = 0;
	double temp1;
	int temp2;
	string garbage;

	while (i < arraySize) {
		getline(bookDatabase, tempInput);
		tempBook->setTitle(tempInput);

		getline(bookDatabase, tempInput);
		tempBook->setISBN(tempInput);

		getline(bookDatabase, tempInput);
		tempBook->setAuthor(tempInput);

		getline(bookDatabase, tempInput);
		tempBook->setPublisher(tempInput);

		getline(bookDatabase, tempInput);
		tempBook->setDateAdded(tempInput);

		bookDatabase >> temp1;
		tempBook->setRetail(temp1);

		bookDatabase >> temp1;
		tempBook->setWholeSale(temp1);

		bookDatabase >> temp2;
		tempBook->setQuantity(temp2);

		getline(bookDatabase, garbage); // this is purely to move onto the next line

		bookArray[i] = *tempBook;
		i++;
	}

	bookDatabase.close();
	return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void displayBook(int i) {
	if (i == -1) {
		cout << "Book was not found." << endl;
	}
	else {
		cout << bookArray[i];
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************
*****************************************
**********  REPORT FUNCTIONS  ***********
*****************************************
****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
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
			bookArray[maxIndex] = bookArray[start];
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
		//string oldestDate;
		Book oldestBook;
		for (start = 0; start < (arraySize - 1); start++) {
			maxIndex = start;
			oldestBook = bookArray[start];
			for (int index = start + 1; index < arraySize; index++) {
				if (isOlder(bookArray[index], oldestBook)) {
					oldestBook = bookArray[index];
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
		cout << "=================================================================" << endl;
	}
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
void wholesaleReport()
{
	system("cls");
	double totalWholesale = 0;
	for (int i = 0; i < arraySize; i++) {
		cout << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << bookArray[i].getTitle() << endl;
		cout << setw(25) << left << "Wholesale Price:" << setw(40) << right << bookArray[i].getWholeSale() << endl;
		cout << setw(25) << left << "Quantity: " << setw(40) << right << bookArray[i].getQuantity() << endl;
		totalWholesale += bookArray[i].getWholeSale()*bookArray[i].getQuantity();
		cout << "=================================================================" << endl;
	}
	cout << "=================================================================" << endl;
	cout << setw(25) << left << "Total Wholesale Value:" << setw(40) << right << totalWholesale << endl;
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
		cout << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << bookArray[i].getTitle() << endl;
		cout << setw(25) << left << "Retail Price:" << setw(40) << right << bookArray[i].getRetail() << endl;
		cout << setw(25) << left << "Quantity: " << setw(40) << right << bookArray[i].getQuantity() << endl;
		totalRetail += bookArray[i].getRetail()*bookArray[i].getQuantity();
		cout << "=================================================================" << endl;
	}
	cout << "=================================================================" << endl;
	cout << setw(25) << left << "Total Retail Value:" << setw(40) << right << totalRetail << endl;
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
		cout << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << bookArray[i].getTitle() << endl;
		cout << setw(25) << left << "Quantity:" << setw(40) << right << bookArray[i].getQuantity() << endl;
		cout << "=================================================================" << endl;
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
		cout << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << bookArray[i].getTitle() << endl;
		cout << setw(25) << left << "Wholesale Price:" << setw(40) << right << bookArray[i].getWholeSale() << endl;
		cout << "=================================================================" << endl;
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
		cout << setfill(' ') << setw(10) << setw(25) << left << "Title:" << setw(40) << right << bookArray[i].getTitle() << endl;
		cout << setw(25) << left << "Date Added (mmddyyyy):" << setw(40) << right << bookArray[i].getDateAdded() << endl;
		cout << "=================================================================" << endl;
	}
	cout << setfill(' ');
	cout << endl << "Press enter to return to the Reports menu";
	getline(cin, emptyStr);
	system("cls");
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************************
**                  Login Functions
*****************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
int login() {
	system("CLS");

	ifstream adminFile;
	ifstream employeeFile;
	try {
		adminFile.open("admin.txt", ios::in);
		if (!adminFile.is_open()) {
			throw 2;
		}
	}
	catch (int x) {
		cout << "Error: " << x << endl;
	}

	try {
		employeeFile.open("employee.txt", ios::in);
		if (!employeeFile.is_open()) {
			throw 3;
		}
	}
	catch (int y) {
		cout << "Error: " << y << endl;
	}


	string username, password, adminCode;
	cout << endl << endl << endl << endl << endl << endl << endl;
	char input = ' ';
	cout << setw(40) << "Username: ";
	cin >> username;
	cout << setw(40) << "Password: ";

	int count = 0;

	while ((input != 13)) {
		input = _getch();
		if ((input != 13)) {
			if (input != '\b') {
				cout << '*';
				password += input;
				count++;
			} else if (input == '\b' && count > 0) {
				cout << '\b' << ' ' << '\b';
				--count;
				password = password.substr(0, password.length() - 1);
			} else if (input == '\b' && count <= 0) {
				count = 0;
				cout << ' ' << '\b';
			}
		}
	}

	for (int i = 0; i < adminSize; i++) {
		if (username == admin[i].getUsername() && password == admin[i].getPassword()) {
			currentEmployee = i;
			return 1;
		}
	}

	for (int i = 0; i < employeeSize; i++) {
		if (username == employee[i].getUsername() && password == employee[i].getPassword()) {
			currentEmployee = i;
			return 2;
		}
	}
	return 3;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int sizeOfAdmin() {
	ifstream inputFile;
	string temp;
	int counter = 0;
	inputFile.open("admin.txt");


	while (inputFile >> temp) {
		counter++;
	}
	inputFile.close();

	return counter / 3;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int sizeOfEmployee() {
	ifstream inputFile;
	string temp;
	int counter = 0;
	try {
		inputFile.open("employee.txt");
		if (!inputFile.is_open()) {
			throw 3;
		}
	}
	catch (int z) {
		cout << "Error: " << z << endl;
	}

	while (inputFile >> temp) {
		counter++;
	}
	inputFile.close();

	return counter / 2;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void loadAdmin() {
	ifstream adminFile;
	try {
		adminFile.open("admin.txt", ios::in);
		if (!adminFile.is_open()) {
			throw 2;
		}
	}
	catch (int x) {
		cout << "Error: " << x << endl;
	}

	adminFile.close();

	adminFile.open("admin.txt", ios::in);
	string temp;
	int i = 0;
	while (i < adminSize) {
		adminFile >> temp;
		tempAdmin->setUsername(temp);

		adminFile >> temp;
		tempAdmin->setPassword(temp);

		adminFile >> temp;
		tempAdmin->setAdminCode(temp);

		admin[i] = *tempAdmin;
		i++;
	}

	adminFile.close();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
void loadEmployee() {
	ifstream employeeFile;
	try {
		employeeFile.open("employee.txt", ios::in);
		if (!employeeFile.is_open()) {
			throw 3;
		}
	}
	catch (int x) {
		cout << "Error: " << x << endl;
	}

	employeeFile.close();

	employeeFile.open("employee.txt", ios::in);
	string temp;
	int i = 0;
	while (i < employeeSize) {
		employeeFile >> temp;
		tempEmployee->setUsername(temp);
		employeeFile >> temp;
		tempEmployee->setPassword(temp);

		employee[i] = *tempEmployee;
		i++;
	}

	employeeFile.close();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************
**      Misc Functions
*******************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
int sizeOfArray() {
	ifstream inputFile;

	inputFile.open("books.txt", ios::in);

	string temp;
	int counter = 0;
	while (getline(inputFile, temp)) {
		counter++;
	}
	inputFile.close();
	return counter / 8;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
string toLower(string input) {
	int length = input.length();
	for (int i = 0; i < length; i++) {
		input[i] = tolower(input[i]);
	}

	return input;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int searchBook(string searchCriteria) {
	for (int i = 0; i < arraySize; i++) {
		if (toLower(searchCriteria) == toLower(bookArray[i].getTitle()) || searchCriteria == bookArray[i].getISBN()) {
			return i;
		}
	}
	return -1;
}

