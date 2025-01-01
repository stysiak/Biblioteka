#include "Administrator.h"
#include <iostream>
using namespace std;

Administrator::Administrator() : Pracownik() {}

Administrator::Administrator(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja)
    : Pracownik(imie, nazwisko, login, haslo, pensja, funkcja) {
}

void Administrator::dodajKsiazke(BazaKsiazek& baza, const string& tytul, const string& autor, int rok) {
    int id = baza.aktualizujStanDodaj(tytul, autor, rok);
    cout << "Ksiazka '" << tytul << "' zostala dodana z ID: " << id << endl;
}

void Administrator::usunKsiazke(BazaKsiazek& baza, int kID) {
    baza.aktualizujStanUsun(kID);
    cout << "Ksiazka o ID " << kID << " zostala usunieta." << endl;
}
