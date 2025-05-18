#pragma once
#include "../../header.h"
#include "../models/Book.h"

class BookDatabase {
private:
    unordered_map<int, shared_ptr<Book>> ksiazki;

public:
    static string fileName;

    BookDatabase();
    int aktualizujStanDodaj(const Book& ksiazka);
    int aktualizujStanUsun(const Book& ksiazka);
    void wyswietlListeKsiazek() const;
};
