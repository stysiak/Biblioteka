#pragma once
#include "../../header.h"
#include "../models/Book.h"

class BookDatabase {
private:
    unordered_map<int, shared_ptr<Book>> books;

public:
    static string fileName;

    BookDatabase();
    void showBookList() const;

    bool borrowBook(int id, const string& returnDate);

    bool returnBook(int id);

    int updateStateAdd(const Book& book);

    int updateStateRemove(const Book& book);
};