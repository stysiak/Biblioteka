#pragma once
#include "../models/Employee.h"
#include "../database/BookDatabase.h"
#include "../database/EmployeeDatabase.h"

class Administrator : public Employee {
public:
    Administrator();
    Administrator(const string& pesel, const string& imie, const string& nazwisko,
                 const string& login, const string& haslo, const string& funkcja);

    virtual ~Administrator() = default;

    void dodajKsiazke(BookDatabase& baza, const Book& ksiazka) noexcept;
    void usunKsiazke(BookDatabase& baza, const Book& ksiazka) noexcept;
    void dodajPracownika(EmployeeDatabase& baza, const Employee& pracownik) noexcept;
    void usunPracownika(EmployeeDatabase& baza, const Employee& pracownik) noexcept;
    void wyswietlListePracownikow(const EmployeeDatabase& baza) const noexcept;
};
