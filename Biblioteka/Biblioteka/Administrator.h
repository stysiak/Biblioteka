#pragma once
#include "Pracownik.h"
#include "BazaKsiazek.h"
#include "BazaPracownikow.h"

class Administrator : public Pracownik {
public:
    Administrator();
    Administrator(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja);
    void dodajKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka); 
    void usunKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka);
    void dodajPracownika(BazaPracownikow& baza, const Pracownik& pracownik);
    void usunPracownika(BazaPracownikow& baza, const Pracownik& pracownik);
    void wyswietlListePracownikow(BazaPracownikow& baza);
};
