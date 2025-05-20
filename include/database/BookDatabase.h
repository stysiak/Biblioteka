#pragma once
#include "../../header.h"
#include "../models/Book.h"

class BookDatabase {
private:
    unordered_map<int, shared_ptr<Book>> ksiazki;

public:
    static string fileName;

    BookDatabase();
    void wyswietlListeKsiazek() const;

    bool wypozyczKsiazke(int id, const string &dataZwrotu);

    bool zwrocKsiazke(int id);

    int updateStateAdd(const Book & book);

    int updateStateRemove(const Book & book);
};
