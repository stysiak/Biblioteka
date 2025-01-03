#include "Pracownik.h"
#include "BazaKsiazek.h"

Pracownik::Pracownik() : imie(""), nazwisko(""), login(""), haslo(""), pensja(0.0), funkcja("") {}

Pracownik::Pracownik(const string& imie, const string& nazwisko, const string& login, const string& haslo, float pensja, const string& funkcja)
    : imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), pensja(pensja), funkcja(funkcja) {
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

void Pracownik::wyswietlListeKsiazek() const {
    BazaKsiazek bazaKsiazek;
    bazaKsiazek.wyswietlListeKsiazek();
}

void sprawdzenieKonta(KontoCzytelnika) {

}

//void przyjmijKaucje(KontoCzytelnika, Egzemplarz) {
//
//}



