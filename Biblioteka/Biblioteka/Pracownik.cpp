#include "Pracownik.h"

Pracownik::Pracownik() : imie(""), nazwisko(""), pensja(0.0), login(""), haslo("") {}

Pracownik::Pracownik(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja)
    : imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), pensja(pensja) {
}

void Pracownik::ustawDane(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja) {
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->login = login;
    this->haslo = haslo;
    this->pensja = pensja;
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
