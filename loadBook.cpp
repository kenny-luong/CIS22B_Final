void loadBook() {
	Book *tempBook;
	temp Book = new Book;
	
	std::ifstream bookDatabase;

	if (!bookDatabase.is_open()) {
		std::cout << “File could not be opened” << std::endl;
} else {
	std::cout << “File was successfully opened.” << std::endl;
}

std::string temp;

int lineCounter = 0;

while (std::getline(bookDatabase, temp)) {
	lineCounter++;
	}

	std::string tempInput;
	Book array[counter/8];
	
	bookDatabase.close();
	
	bookDatabase.open(“books.txt”, std::ios::in);

	int i = 0;

	while(!bookDatabase.eof()) {
		std::getline(bookDatabase, temp);
		tempBook->setTitle(temp);
		std::getline(bookDatabase, temp);
		tempBook->setISBN(temp);
		std::getline(bookDatabase, temp);
		tempBook->setAuthor(temp);
		std::getline(bookDatabase, temp);
		tempBook->setPublisher(temp);
		std::getline(bookDatabase, temp);
		tempBook->setDateAdded(temp);
		std::getline(bookDatabase, temp);
		tempBook->setRetail(temp);
		std::getline(bookDatabase, temp);
		tempBook->setWholeSale(temp);
		std::getline(bookDatabase, temp);
		tempBook->setQuantity(temp);
		array[i] = *tempBook;
		if (i < lineCounter) {
			i++;
		}
	}
};