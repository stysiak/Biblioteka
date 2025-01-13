#include "Administrator.h"

Administrator::Administrator() : Pracownik() {}

Administrator::Administrator(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : Pracownik(pesel, imie, nazwisko, login, haslo, funkcja) {
}

//funkcja dodaj¹ca now¹ ksi¹¿kê do bazy
void Administrator::dodajKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) {
    int id = baza.aktualizujStanDodaj(ksiazka); 
    if (id != -1) {
        cout << "Ksiazka '" << ksiazka.getTytul() << "' zostala dodana z ID: " << ksiazka.getID() << endl;
    }
}

//funckja usuwaj¹ca istniej¹c¹ ksi¹¿kê z bazy
void Administrator::usunKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) {
    int id = baza.aktualizujStanUsun(ksiazka);
    if (id != -1) {
        cout << "Ksiazka o ID " << ksiazka.getID() << " zostala usunieta." << endl;
    }
}

//funkcja dodaj¹ca nowego pracownika
void Administrator::dodajPracownika(BazaPracownikow& baza, const Pracownik& pracownik) {
    int id = baza.dodajPracownika(pracownik);
    if (id != -1) {
        cout << "Pracownik o Peselu " << pracownik.getPesel() << " zostal dodany do bazy." << endl;
    }
}

//funkcja usuwaj¹ca istniej¹cego pracownika
void Administrator::usunPracownika(BazaPracownikow& baza, const Pracownik& pracownik) {
    int id = baza.usunPracownika(pracownik);
    if (id != -1) {
        cout << "Pracownik o Peselu " << pracownik.getPesel() << " zostal usuniety z bazy." << endl;
    }
}

void Administrator::wyswietlListePracownikow(BazaPracownikow& baza) {
    baza.wyswietlListePracownikow();
}
