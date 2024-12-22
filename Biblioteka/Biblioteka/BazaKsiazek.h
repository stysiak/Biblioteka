#pragma once
#include "header.h"
#include "Egzemplarz.h"
#include "Ksiazka.h"
#include <unordered_map>
#include <memory>
#include <string>
using namespace std;

class BazaKsiazek {
private:
    int ID = 0;
    int egzID = 100;
    unordered_map<int, shared_ptr<Ksiazka>> ksiazki;

public:
    BazaKsiazek();
    int aktualizujStanDodaj(const string& tytul, const string& autor, int rok);
    void dodajEgzemplarzDoKsiazki(int kID);
    void aktualizujStanUsun(int kID);
    void usunEgzemplarzKsiazki(int eID);
    bool aktualizujStanPoWypozyczeniu(Egzemplarz e);
};
