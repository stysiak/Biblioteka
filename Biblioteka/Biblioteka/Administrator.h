#pragma once
#include "Pracownik.h"
#include "BazaKsiazek.h"

class Administrator : public Pracownik {
public:
    Administrator();
    Administrator(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja);
    void dodajKsiazke(BazaKsiazek& baza, const string& tytul, const string& autor, int rok);
    void usunKsiazke(BazaKsiazek& baza, int kID);
};
