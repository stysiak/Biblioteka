#pragma once
#include "header.h"
#include "Pracownik.h"
#include "Administrator.h"

class BazaPracownikow {
private:
    vector<Pracownik> listaPracownikow;

public:
    BazaPracownikow();
    pair<string, string> logowanie();
    void dodajPracownika(const Pracownik& pracownik);

};