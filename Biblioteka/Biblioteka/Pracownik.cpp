#include "Pracownik.h"

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
    baza.tworzenieKonta(czytelnik);
 
}

void Pracownik::usunCzytelnika(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik) {
    baza.usuniecieKonta(czytelnik);
}

void Pracownik::wyswietlListeKsiazek(BazaKsiazek& baza) {
    baza.wyswietlListeKsiazek();
}

void Pracownik::wyswietlListeCzytelnikow(BazaCzytelnikow& baza) {
    baza.wyswietlListeCzytelnikow();
}

void Pracownik::sprawdzenieKonta(BazaCzytelnikow& baza, const KontoCzytelnika& czytelnik) {
    baza.sprawdzenieKonta(czytelnik);
}

void Pracownik::wypozyczKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    if (!bazaCzytelnikow.czyMoznaWypozyczyc(czytelnik)) {
        return; 
    }
    if (wypozyczenie.wypozyczKsiazke(egzemplarzID) != -1) {
        bazaCzytelnikow.podepnijWypozyczenie(czytelnik, egzemplarzID);
    }
}

void Pracownik::zwrocKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    float kaucja = bazaKsiazek.zwrocKsiazke(egzemplarzID);

    if (kaucja != -1) {
        bazaCzytelnikow.usunWypozyczenie(czytelnik, egzemplarzID);

        if (kaucja > 0) {
            bazaCzytelnikow.naliczKaucje(const_cast<KontoCzytelnika&>(czytelnik), kaucja);
        }
    }
    else {
        cout << "Blad podczas zwrotu ksi¹¿ki. Egzemplarz o ID " << egzemplarzID << " nie istnieje lub nie by³ wypozyczony." << endl;
    }
}


void Pracownik::przyjmijKaucje(BazaCzytelnikow& bazaCzytelnikow, KontoCzytelnika& czytelnik) {
    bazaCzytelnikow.usunKaucje(czytelnik);
}




