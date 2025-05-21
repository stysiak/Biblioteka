#include "../../include/models/Employee.h"

Employee::Employee() : pesel(""), firstName(""), lastName(""), login(""), password(""), role("") {}

Employee::Employee(const string& pesel, const string& firstName, const string& lastName, const string& login, const string& password, const string& role)
    : pesel(pesel), firstName(firstName), lastName(lastName), login(login), password(password), role(role) {
}

Employee::Employee(const string& pesel)
    : pesel(pesel) {
}

string Employee::getPesel() const {
    return pesel;
}

string Employee::getLogin() const {
    return login;
}

string Employee::getPassword() const {
    return password;
}

string Employee::getFirstName() const {
    return firstName;
}

string Employee::getLastName() const {
    return lastName;
}

string Employee::getRole() const {
    return role;
}

void Employee::addReader(ReaderDatabase& database, const ReaderAccount& reader) {
    database.createAccount(reader);
}

void Employee::removeReader(ReaderDatabase& database, const ReaderAccount& reader) {
    database.deleteAccount(reader);
}

void Employee::showBookList(BookDatabase& database) {
    database.showBookList();
}

void Employee::showReaderList(ReaderDatabase& database) {
    database.showReaderList();
}

void Employee::checkAccount(ReaderDatabase& database, const ReaderAccount& reader) {
    database.checkAccount(reader);
}

void Employee::borrowBook(BookDatabase&, ReaderDatabase& readerDatabase,
    int bookID, const ReaderAccount& reader) {

    if (!readerDatabase.canBorrow(reader)) {
        return;
    }
    if (borrow.borrowBook(bookID) != -1) {
        readerDatabase.addBorrow(reader, bookID);
    }
}

void Employee::returnBook(BookDatabase&, ReaderDatabase& readerDatabase, int bookID, const ReaderAccount& reader) {
    float deposit = ret.returnBook(bookID);

    if (deposit != -1) {
        readerDatabase.removeBorrow(reader, bookID);

        if (deposit > 0) {
            readerDatabase.setDeposit(const_cast<ReaderAccount&>(reader), deposit);
        }
    }
    else {
        cout << "Error while returning the book. Book with ID " << bookID << " does not exist or was not borrowed." << endl;
    }
}

void Employee::acceptDeposit(ReaderDatabase& readerDatabase, ReaderAccount& reader) {
    readerDatabase.removeDeposit(reader);
}