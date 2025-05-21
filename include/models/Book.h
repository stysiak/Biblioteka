#pragma once
#include "../../header.h"

class Book {
private:
    int ID;
    string title;
    string authorSurname;
    int yearOfPublication;
    string status;
    string returnDate;

public:
    Book();
    Book(int ID, const string& title, const string& authorSurname, int yearOfPublication, string status);
    Book(int ID);
    int getID() const;
    string getTitle() const;
    string getAuthorSurname() const;
    int getYearOfPublication() const;

    void setStatus(const string& newStatus);

    string getStatus() const;

    void setReturnDate(const string& date);
};