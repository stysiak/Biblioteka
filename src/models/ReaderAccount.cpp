#include "../../include/models/ReaderAccount.h"

ReaderAccount::ReaderAccount(const string& pesel, const string& firstName, const string& lastName, const float& deposit, const int& booksCount)
    : pesel(pesel), firstName(firstName), lastName(lastName), deposit(deposit), booksCount(booksCount) {
}

ReaderAccount::ReaderAccount(const string& pesel, const string& firstName, const string& lastName)
    : pesel(pesel), firstName(firstName), lastName(lastName) {
}

ReaderAccount::ReaderAccount(const string& pesel)
    : pesel(pesel) {
}

string ReaderAccount::getPesel() const {
    return pesel;
}

string ReaderAccount::getFirstName() const {
    return firstName;
}

string ReaderAccount::getLastName() const {
    return lastName;
}

float ReaderAccount::getDeposit() const {
    return deposit;
}

int ReaderAccount::getBooksCount() const {
    return booksCount;
}