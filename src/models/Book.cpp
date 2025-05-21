#include "../../include/models/Book.h"

Book::Book() : ID(0), title(""), authorSurname(""), yearOfPublication(0), status("") {}

Book::Book(int ID)
 : ID(ID) {
}

Book::Book(int ID, const string& title, const string& authorSurname, int yearOfPublication, string status)
 : ID(ID), title(title), authorSurname(authorSurname), yearOfPublication(yearOfPublication), status(status) {
}

int Book::getID() const {
	return ID;
}

string Book::getTitle() const {
	return title;
}

string Book::getAuthorSurname() const {
	return authorSurname;
}

int Book::getYearOfPublication() const {
	return yearOfPublication;
}

void Book::setStatus(const string& newStatus) {
	if (newStatus == "available" || newStatus == "unavailable") {
		status = newStatus;
	} else {
		cerr << "Invalid book status: " << newStatus << endl;
	}
}

string Book::getStatus() const {
	return status;
}

void Book::setReturnDate(const string& date) {
	returnDate = date;
}