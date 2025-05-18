#include "../../include/core/Administrator.h"

Administrator::Administrator() : Pracownik("", "", "", "", "", "") {
}

Administrator::Administrator(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : Pracownik(pesel, imie, nazwisko, login, haslo, funkcja) {
}

void Administrator::dodajKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) noexcept {
    int id = baza.aktualizujStanDodaj(ksiazka);
    if (id != -1) {
        cout << "Ksiazka '" << ksiazka.getTytul() << "' zostala dodana z ID: " << ksiazka.getID() << endl;
    }
}

void Administrator::usunKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) noexcept {
    int id = baza.aktualizujStanUsun(ksiazka);
    if (id != -1) {
        cout << "Ksiazka o ID " << ksiazka.getID() << " zostala usunieta." << endl;
    }
}

void Administrator::dodajPracownika(BazaPracownikow& baza, const Pracownik& pracownik) noexcept {
    int id = baza.dodajPracownika(pracownik);
    if (id != -1) {
        cout << "Pracownik o Peselu " << pracownik.getPesel() << " zostal dodany do bazy." << endl;
    }
}

void Administrator::usunPracownika(BazaPracownikow& baza, const Pracownik& pracownik) noexcept {
    int id = baza.usunPracownika(pracownik);
    if (id != -1) {
        cout << "Pracownik o Peselu " << pracownik.getPesel() << " zostal usuniety z bazy." << endl;
    }
}

void Administrator::wyswietlListePracownikow(const BazaPracownikow& baza) const noexcept {
    baza.wyswietlListePracownikow();
}

