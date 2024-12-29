#pragma once
#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Pracownik {
private:
    string imie;
    string nazwisko;
    float pensja;
    string login;
    string haslo;

public:
    Pracownik();
    Pracownik(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja);

    void ustawDane(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja);
    string getLogin() const;
    string getHaslo() const;
    string getImie() const;
    string getNazwisko() const;
    float getPensja() const;
    void sprawdzenieKonta(KontoCzytelnika);
    void przyjmijKaucje(KontoCzytelnika, Egzemplarz);
};
