#pragma once
#include "header.h"
#include "Pracownik.h"
#include "Administrator.h"
#include "BazaKsiazek.h"

class BazaPracownikow {
private:
    vector<Pracownik> listaPracownikow;

public:
    BazaPracownikow();
    pair<string, string> logowanie();
    bool walidujPesel(const string& pesel);
    int dodajPracownika(const Pracownik& pracownik);
    int usunPracownika(const Pracownik& pracownik);
    void wyswietlListePracownikow() const;
};