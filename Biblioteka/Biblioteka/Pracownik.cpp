#include "Pracownik.h"
#include "BazaKsiazek.h"
#include "BazaCzytelnikow.h"

Pracownik::Pracownik() : pesel(""), imie(""), nazwisko(""), login(""), haslo(""), pensja(0.0), funkcja("") {}

Pracownik::Pracownik(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja)
    : pesel(pesel), imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), pensja(pensja), funkcja(funkcja) {
}

Pracownik::Pracownik(const string& pesel)
    : pesel(pesel) {
}

string Pracownik::getPesel() const {
    return pesel;
}

string Pracownik::getLogin() const {
    return login;
}

string Pracownik::getHaslo() const {
    return haslo;
}

string Pracownik::getImie() const {
    return imie;
}

string Pracownik::getNazwisko() const {
    return nazwisko;
}

float Pracownik::getPensja() const {
    return pensja;
}

string Pracownik::getFunkcja() const {
    return funkcja;
}

void Pracownik::dodajCzytelnika(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik) {
    double id = baza.tworzenieKonta(czytelnik);
    if (id != -1) {
        cout << "Czytelnik o Peselu " << czytelnik.getPesel() << " zostal dodany do bazy." << endl;
    }
}

void Pracownik::usunCzytelnika(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik) {
    double id = baza.usuniecieKonta(czytelnik);
    if (id != -1) {
        cout << "Czytelnik o Peselu " << czytelnik.getPesel() << " zostal usuniety z bazy." << endl;
    }
}

void Pracownik::wyswietlListeKsiazek(BazaKsiazek& baza) {
    baza.wyswietlListeKsiazek();
}

void Pracownik::wyswietlListeCzytelnikow(BazaCzytelnikow& baza) {
    baza.wyswietlListeCzytelnikow();
}

void sprawdzenieKonta(KontoCzytelnika) {

}

void Pracownik::wypozyczKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    if (bazaKsiazek.wypozyczKsiazke(egzemplarzID) != -1) {
        bazaCzytelnikow.podepnijWypozyczenie(czytelnik, egzemplarzID);
    }
}

void Pracownik::zwrocKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    if (bazaKsiazek.zwrocKsiazke(egzemplarzID) != -1) {
        bazaCzytelnikow.usunWypozyczenie(czytelnik, egzemplarzID);
    }
}


//void przyjmijKaucje(KontoCzytelnika, Egzemplarz) {
//
//}



