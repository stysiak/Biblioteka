#include "../../include/models/Employee.h"

Employee::Employee() : pesel(""), imie(""), nazwisko(""), login(""), haslo(""), funkcja("") {} // konstruktor z warto�ciami domy�lnymi

Employee::Employee(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : pesel(pesel), imie(imie), nazwisko(nazwisko), login(login), haslo(haslo), funkcja(funkcja) {
}

Employee::Employee(const string& pesel)
    : pesel(pesel) {
}

// Funkcje zwracaj�ce dan� warto��
string Employee::getPesel() const {
    return pesel;
}

string Employee::getLogin() const {
    return login;
}

string Employee::getHaslo() const {
    return haslo;
}

string Employee::getImie() const {
    return imie;
}

string Employee::getNazwisko() const {
    return nazwisko;
}

string Employee::getFunkcja() const {
    return funkcja;
}

void Employee::dodajCzytelnika(ReaderDatabase& baza, const ReaderAccount& czytelnik) {
    baza.createAccount(czytelnik);
}

void Employee::usunCzytelnika(ReaderDatabase& baza, const ReaderAccount& czytelnik) {
    baza.deleteAccount(czytelnik);
}

void Employee::wyswietlListeKsiazek(BookDatabase& baza) {
    baza.wyswietlListeKsiazek();
}

void Employee::wyswietlListeCzytelnikow(ReaderDatabase& baza) {
    baza.showReaderList();
}

void Employee::sprawdzenieKonta(ReaderDatabase& baza, const ReaderAccount& czytelnik) {
    baza.checkAccount(czytelnik);
}

// Funkcja sprawdzaj�ca, czytelnik mo�e wypo�yczy� ksi��k�
void Employee::wypozyczKsiazke(BookDatabase&, ReaderDatabase& bazaCzytelnikow,
    int egzemplarzID, const ReaderAccount& czytelnik) {

    if (!bazaCzytelnikow.canBorrow(czytelnik)) {
        return; // wyj�cie z funkcji, je�li wypo�yczenie jest niemo�liwe
    }
    if (wypozyczenie.wypozyczKsiazke(egzemplarzID) != -1) { // pr�ba wypo�yczenia; je�li si� powiedzie, dodaj do wypo�ycze� czytelnika
        bazaCzytelnikow.addBorrow(czytelnik, egzemplarzID);
    }
}

// Funkcja sprawdzaj�c�, czy zwrot jest mo�liwy
void Employee::zwrocKsiazke(BookDatabase&, ReaderDatabase& bazaCzytelnikow, int egzemplarzID, const ReaderAccount& czytelnik) {
    float kaucja = zwrot.zwrocKsiazke(egzemplarzID); // obliczenie warto�ci kaucji

    if (kaucja != -1) {
        bazaCzytelnikow.removeBorrow(czytelnik, egzemplarzID); // usuni�cie informacji o wypo�yczeniu z bazy czytelnika

        if (kaucja > 0) { // je�li warto�� kaucji jest dodatnia, nalicz j� czytelnikowi
            bazaCzytelnikow.setDeposit(const_cast<ReaderAccount&>(czytelnik), kaucja);
        }
    }
    else {
        cout << "Blad podczas zwrotu ksi��ki. Egzemplarz o ID " << egzemplarzID << " nie istnieje lub nie by� wypozyczony." << endl;
    }
}

// Funkcja aktualizuj�ca stan konta czytelnika
void Employee::przyjmijKaucje(ReaderDatabase& bazaCzytelnikow, ReaderAccount& czytelnik) {
    bazaCzytelnikow.removeDeposit(czytelnik);
}
