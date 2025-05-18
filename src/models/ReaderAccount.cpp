#include "../../include/models/ReaderAccount.h"

ReaderAccount::ReaderAccount(const string& pesel, const string& imie, const string& nazwisko, const float& kaucja, const int& iloscKsiazek = 0)
    : pesel(pesel), imie(imie), nazwisko(nazwisko), kaucja(kaucja), iloscKsiazek(iloscKsiazek) {
}

ReaderAccount::ReaderAccount(const string& pesel, const string& imie, const string& nazwisko)
    : pesel(pesel), imie(imie), nazwisko(nazwisko) {
}

ReaderAccount::ReaderAccount(const string& pesel)
    : pesel(pesel) {
}

string ReaderAccount::getPesel() const {
    return pesel;
}

string ReaderAccount::getImie() const {
    return imie;
}

string ReaderAccount::getNazwisko() const {
    return nazwisko;
}

float ReaderAccount::getKaucja() const {
    return kaucja;
}

int ReaderAccount::getIloscKsiazek() const {
    return iloscKsiazek;
}


