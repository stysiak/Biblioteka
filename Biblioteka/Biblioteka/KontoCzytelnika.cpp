#include "KontoCzytelnika.h"

KontoCzytelnika::KontoCzytelnika() :  pesel(""), imie(""), nazwisko("") {}

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


