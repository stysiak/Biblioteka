#include "KontoCzytelnika.h"

KontoCzytelnika::KontoCzytelnika(const string& pesel, const string& imie, const string& nazwisko, const float& kaucja, const int& iloscKsiazek = 0, const string& przekroczonoLimit = "nie")
    : pesel(pesel), imie(imie), nazwisko(nazwisko), kaucja(kaucja), iloscKsiazek(iloscKsiazek), przekroczonoLimit(przekroczonoLimit) {
}

KontoCzytelnika::KontoCzytelnika(const string& pesel, const string& imie, const string& nazwisko)
    : pesel(pesel), imie(imie), nazwisko(nazwisko) {
}

KontoCzytelnika::KontoCzytelnika(const string& pesel)
    : pesel(pesel) {
}

string KontoCzytelnika::getPesel() const {
    return pesel;
}

string KontoCzytelnika::getImie() const {
    return imie;
}

string KontoCzytelnika::getNazwisko() const {
    return nazwisko;
}

float KontoCzytelnika::getKaucja() const {
    return kaucja;
}

int KontoCzytelnika::getIloscKsiazek() const {
    return iloscKsiazek;
}

string KontoCzytelnika::getPrzekroczonoLimit() const {
    return przekroczonoLimit;
}

