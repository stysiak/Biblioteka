#pragma once
#include "header.h"
#include "Pracownik.h"
#include <vector>
#include <string>
#include <iostream>

class BazaPracownikow {
private:
    vector<Pracownik> listaPracownikow;

public:
    BazaPracownikow();
    bool logowanie();
    void dodajPracownika(const Pracownik& pracownik);
};