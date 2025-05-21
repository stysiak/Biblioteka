#pragma once
#include "../../header.h"
#include "ReaderAccount.h"
#include "../database/BookDatabase.h"
#include "../database/ReaderDatabase.h"
#include "../utils/Borrowing.h"
#include "../utils/Return.h"

class Employee {
private:
    string pesel;
    string firstName;
    string lastName;
    string login;
    string password;
    string role;
    Borrowing borrow;
    Return ret;

public:
    Employee();
    Employee(const string& pesel, const string& firstName, const string& lastName, const string& login, const string& password, const string& role);
    Employee(const string& pesel);
    string getPesel() const;
    string getLogin() const;
    string getPassword() const;
    string getFirstName() const;
    string getLastName() const;
    string getRole() const;
    void addReader(ReaderDatabase& database, const ReaderAccount& reader);
    void removeReader(ReaderDatabase& database, const ReaderAccount& reader);
    void checkAccount(ReaderDatabase& database, const ReaderAccount& reader);
    void acceptDeposit(ReaderDatabase& readerDatabase, ReaderAccount& reader);
    void showBookList(BookDatabase& database);
    void showReaderList(ReaderDatabase& database);
    void borrowBook(BookDatabase& bookDatabase, ReaderDatabase& readerDatabase, int bookID, const ReaderAccount& reader);
    void returnBook(BookDatabase& bookDatabase, ReaderDatabase& readerDatabase, int bookID, const ReaderAccount& reader);
};