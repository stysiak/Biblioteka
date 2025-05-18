#pragma once
#include "../../header.h"
#include "../models/Employee.h"
#include "../core/Administrator.h"
#include "BookDatabase.h"

class EmployeeDatabase {
private:
    vector<Employee> listaPracownikow;

public:
    EmployeeDatabase();
    pair<string, string> logowanie();

    static string nazwaPliku;

    static string fileName;

    bool walidujPesel(const string& pesel);
    int dodajPracownika(const Employee& pracownik);
    int usunPracownika(const Employee& pracownik);
    void wyswietlListePracownikow() const;
};