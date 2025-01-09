#pragma once
#include "header.h"
#include "Egzemplarz.h"
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

    //void dodajEgzemplarzDoKsiazki(int kID);
    //void usunEgzemplarzKsiazki(int eID);
    bool aktualizujStanPoWypozyczeniu(Egzemplarz e);
    void wyswietlListeKsiazek() const;
    int wypozyczKsiazke(int egzemplarzID);
    int zwrocKsiazke(int egzemplarzID);

};
