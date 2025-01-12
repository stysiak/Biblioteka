#pragma once
#include "header.h"
#include "Ksiazka.h"

class BazaKsiazek {
private:
    int ID;
    int egzID;
    unordered_map<int, shared_ptr<Ksiazka>> ksiazki;

public:
    BazaKsiazek();
    int aktualizujStanDodaj(const Ksiazka& ksiazka);
    int aktualizujStanUsun(const Ksiazka& ksiazka);
    void wyswietlListeKsiazek() const;
};
