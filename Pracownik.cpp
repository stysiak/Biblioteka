#include "Pracownik.h"

Pracownik::Pracownik() : pesel(""), imie(""), nazwisko(""), login(""), haslo(""), funkcja("") {} // konstruktor z warto�ciami domy�lnymi

Pracownik::Pracownik(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : pesel(pesel), imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), funkcja(funkcja) {
}

Pracownik::Pracownik(const string& pesel)
    : pesel(pesel) {
}

// Funkcje zwracaj�ce dan� warto��
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

// Funkcja sprawdzaj�ca, czytelnik mo�e wypo�yczy� ksi��k�
void Pracownik::wypozyczKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    if (!bazaCzytelnikow.czyMoznaWypozyczyc(czytelnik)) {
        return; // wyj�cie z funkcji, je�li wypo�yczenie jest niemo�liwe
    }
    if (wypozyczenie.wypozyczKsiazke(egzemplarzID) != -1) { // pr�ba wypo�yczenia; je�li si� powiedzie, dodaj do wypo�ycze� czytelnika
        bazaCzytelnikow.podepnijWypozyczenie(czytelnik, egzemplarzID);
    }
}

// Funkcja sprawdzaj�c�, czy zwrot jest mo�liwy
void Pracownik::zwrocKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    float kaucja = zwrot.zwrocKsiazke(egzemplarzID); // obliczenie warto�ci kaucji

    if (kaucja != -1) {
        bazaCzytelnikow.usunWypozyczenie(czytelnik, egzemplarzID); // usuni�cie informacji o wypo�yczeniu z bazy czytelnika

        if (kaucja > 0) { // je�li warto�� kaucji jest dodatnia, nalicz j� czytelnikowi
            bazaCzytelnikow.naliczKaucje(const_cast<KontoCzytelnika&>(czytelnik), kaucja);
        }
    }
    else {
        cout << "Blad podczas zwrotu ksi��ki. Egzemplarz o ID " << egzemplarzID << " nie istnieje lub nie by� wypozyczony." << endl;
    }
}

// Funkcja aktualizuj�ca stan konta czytelnika
void Pracownik::przyjmijKaucje(BazaCzytelnikow& bazaCzytelnikow, KontoCzytelnika& czytelnik) {
    bazaCzytelnikow.usunKaucje(czytelnik);
}
