#include "Administrator.h"
#include <iostream>
using namespace std;

Administrator::Administrator() : Pracownik() {}

Administrator::Administrator(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja)
    : Pracownik(imie, nazwisko, login, haslo, pensja, funkcja) {
}

void Administrator::dodajKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) {
    int id = baza.aktualizujStanDodaj(ksiazka); 
    if (id != -1) {
        cout << "Ksiazka '" << ksiazka.getTytul() << "' zostala dodana z ID: " << ksiazka.getID() << endl;
    }
}

void Administrator::usunKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) {
    int id = baza.aktualizujStanUsun(ksiazka);
    if (id != -1) {
        cout << "Ksiazka o ID " << ksiazka.getID() << " zostala usunieta." << endl;
    }
    
}
