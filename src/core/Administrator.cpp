#include "../../include/core/Administrator.h"

Administrator::Administrator() : Employee("", "", "", "", "", "") {
}

Administrator::Administrator(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : Employee(pesel, imie, nazwisko, login, haslo, funkcja) {
}

void Administrator::dodajKsiazke(BookDatabase& baza, const Book& ksiazka) noexcept {
    int id = baza.aktualizujStanDodaj(ksiazka);
    if (id != -1) {
        cout << "Book '" << ksiazka.getTytul() << "' zostala dodana z ID: " << ksiazka.getID() << endl;
    }
}

void Administrator::usunKsiazke(BookDatabase& baza, const Book& ksiazka) noexcept {
    int id = baza.aktualizujStanUsun(ksiazka);
    if (id != -1) {
        cout << "Book o ID " << ksiazka.getID() << " zostala usunieta." << endl;
    }
}

void Administrator::dodajPracownika(EmployeeDatabase& baza, const Employee& pracownik) noexcept {
    int id = baza.dodajPracownika(pracownik);
    if (id != -1) {
        cout << "Employee o Peselu " << pracownik.getPesel() << " zostal dodany do bazy." << endl;
    }
}

void Administrator::usunPracownika(EmployeeDatabase& baza, const Employee& pracownik) noexcept {
    int id = baza.usunPracownika(pracownik);
    if (id != -1) {
        cout << "Employee o Peselu " << pracownik.getPesel() << " zostal usuniety z bazy." << endl;
    }
}

void Administrator::wyswietlListePracownikow(const EmployeeDatabase& baza) const noexcept {
    baza.wyswietlListePracownikow();
}

