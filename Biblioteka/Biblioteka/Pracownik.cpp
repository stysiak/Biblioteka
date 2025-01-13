#include "Pracownik.h"

Pracownik::Pracownik() : pesel(""), imie(""), nazwisko(""), login(""), haslo(""), funkcja("") {} // konstruktor z wartoœciami domyœlnymi

Pracownik::Pracownik(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : pesel(pesel), imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), funkcja(funkcja) {
}

Pracownik::Pracownik(const string& pesel)
    : pesel(pesel) {
}

// Funkcje zwracaj¹ce dan¹ wartoœæ
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

// Funkcja sprawdzaj¹ca, czytelnik mo¿e wypo¿yczyæ ksi¹¿kê
void Pracownik::wypozyczKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    if (!bazaCzytelnikow.czyMoznaWypozyczyc(czytelnik)) {
        return; // wyjœcie z funkcji, jeœli wypo¿yczenie jest niemo¿liwe
    }
    if (wypozyczenie.wypozyczKsiazke(egzemplarzID) != -1) { // próba wypo¿yczenia; jeœli siê powiedzie, dodaj do wypo¿yczeñ czytelnika
        bazaCzytelnikow.podepnijWypozyczenie(czytelnik, egzemplarzID);
    }
}

// Funkcja sprawdzaj¹c¹, czy zwrot jest mo¿liwy
void Pracownik::zwrocKsiazke(BazaKsiazek& bazaKsiazek, BazaCzytelnikow& bazaCzytelnikow, int egzemplarzID, const KontoCzytelnika& czytelnik) {
    float kaucja = zwrot.zwrocKsiazke(egzemplarzID); // obliczenie wartoœci kaucji

    if (kaucja != -1) {
        bazaCzytelnikow.usunWypozyczenie(czytelnik, egzemplarzID); // usuniêcie informacji o wypo¿yczeniu z bazy czytelnika

        if (kaucja > 0) { // jeœli wartoœæ kaucji jest dodatnia, nalicz j¹ czytelnikowi
            bazaCzytelnikow.naliczKaucje(const_cast<KontoCzytelnika&>(czytelnik), kaucja);
        }
    }
    else {
        cout << "Blad podczas zwrotu ksi¹¿ki. Egzemplarz o ID " << egzemplarzID << " nie istnieje lub nie by³ wypozyczony." << endl;
    }
}

// Funkcja aktualizuj¹ca stan konta czytelnika
void Pracownik::przyjmijKaucje(BazaCzytelnikow& bazaCzytelnikow, KontoCzytelnika& czytelnik) {
    bazaCzytelnikow.usunKaucje(czytelnik);
}
