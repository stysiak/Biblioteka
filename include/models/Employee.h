#pragma once
#include "../../header.h"
#include "ReaderAccount.h"
#include "../database/BookDatabase.h"
#include "../database/ReaderDatabase.h"
#include "../utils/Borrowing.h"
#include "../utils/Return.h"

class Employee {
private:
    string pesel;
    string imie;
    string nazwisko;
    string login;
    string haslo;
    string funkcja;
    Borrowing wypozyczenie;
    Return zwrot;

public:
    Employee();
    Employee(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja);
    Employee(const string& pesel);
    string getPesel() const;
    string getLogin() const;
    string getHaslo() const;
    string getImie() const;
    string getNazwisko() const;
    string getFunkcja() const;
    void dodajCzytelnika(ReaderDatabase& baza, const ReaderAccount& czytelnik);
    void usunCzytelnika(ReaderDatabase& baza, const ReaderAccount& czytelnik);
    void sprawdzenieKonta(ReaderDatabase& baza, const ReaderAccount& czytelnik);
    void przyjmijKaucje(ReaderDatabase& bazaCzytelnikow, ReaderAccount& czytelnik);
    void wyswietlListeKsiazek(BookDatabase& baza);
    void wyswietlListeCzytelnikow(ReaderDatabase& baza);
    void wypozyczKsiazke(BookDatabase& bazaKsiazek, ReaderDatabase& bazaCzytelnikow, int egzemplarzID, const ReaderAccount& czytelnik);
    void zwrocKsiazke(BookDatabase& bazaKsiazek, ReaderDatabase& bazaCzytelnikow, int egzemplarzID, const ReaderAccount& czytelnik);
};
