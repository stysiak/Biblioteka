#include "BazaKsiazek.h"
#include <iostream>

using namespace std;

BazaKsiazek::BazaKsiazek() {
}

int BazaKsiazek::aktualizujStanDodaj(const string& tytul, const string& autor, int rok) {
    int id = ++ID;
    ksiazki[id] = make_shared<Ksiazka>(id, tytul, autor, rok);
    return id;
}

void BazaKsiazek::dodajEgzemplarzDoKsiazki(int kID) {
    if (ksiazki.count(kID) > 0) {
        int eID = ++egzID;
        ksiazki.at(kID)->dodajEgzemplarz(eID);
    }
    else {
        cout << "Podano bledne ID ksiazki" << endl;
    }
}

void BazaKsiazek::aktualizujStanUsun(int kID) {
    if (ksiazki.count(kID) > 0) {
        ksiazki.erase(kID);
        cout << "Usunieto ksiazke" << endl;
    }
}

void BazaKsiazek::usunEgzemplarzKsiazki(int eID) {
}

bool BazaKsiazek::aktualizujStanPoWypozyczeniu(Egzemplarz e) {
    return true;
}
