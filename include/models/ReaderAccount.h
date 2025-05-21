#pragma once
#include "../../header.h"

class ReaderAccount {
private:
	string pesel;
	string firstName;
	string lastName;
	float deposit = 0.0;
	int booksCount = 0;
public:
	ReaderAccount(const string& pesel, const string& firstName, const string& lastName, const float& deposit, const int& booksCount);
	ReaderAccount(const string& pesel, const string& firstName, const string& lastName);
	ReaderAccount(const string& pesel);
	string getPesel() const;
	string getFirstName() const;
	string getLastName() const;
	float getDeposit() const;
	int getBooksCount() const;
};