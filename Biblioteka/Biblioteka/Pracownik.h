#pragma once
#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Pracownik {
private:
    string pesel;
    string imie;
    string nazwisko;
    string login;
    string haslo;
    float pensja;
    string funkcja;

public:
    Pracownik();
    Pracownik(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja);
    Pracownik(const string& pesel);
    string getPesel() const;
    string getLogin() const;
    string getHaslo() const;
    string getImie() const;
    string getNazwisko() const;
    float getPensja() const;
    string getFunkcja() const;
    void dodajCzytelnika(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik);
    void usunCzytelnika(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik);
    //void sprawdzenieKonta(KontoCzytelnika);
    void przyjmijKaucje(BazaCzytelnikow& bazaCzytelnikow, KontoCzytelnika& czytelnik);
    void wyswietlListeKsiazek(BazaKsiazek& baza);
    void wyswietlListeCzytelnikow(BazaCzytelnikow& baza);
    void wypozyczKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik);
    void zwrocKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik);

};
