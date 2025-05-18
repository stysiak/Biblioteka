#pragma once
#include "../../header.h"
#include "../models/Ksiazka.h"

class BazaKsiazek {
private:
    unordered_map<int, shared_ptr<Ksiazka>> ksiazki;

public:
    BazaKsiazek();
    int aktualizujStanDodaj(const Ksiazka& ksiazka);
    int aktualizujStanUsun(const Ksiazka& ksiazka);
    void wyswietlListeKsiazek() const;
};
