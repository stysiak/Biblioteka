#include "BazaPracownikow.h"
#include <fstream>
#include <sstream>

BazaPracownikow::BazaPracownikow() {
    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo;
        float pensja;

        ss >> imie >> nazwisko >> login >> haslo >> pensja;

        Pracownik p(imie, nazwisko, login, haslo, pensja);
        listaPracownikow.push_back(p);
    }
    plik.close();
}

bool BazaPracownikow::logowanie() {
    string wpisanyLogin, wpisaneHaslo;
    cout << "Podaj login: ";
    cin >> wpisanyLogin;
    cout << "Podaj haslo: ";
    cin >> wpisaneHaslo;

    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return false;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string login, haslo;
        ss >> login >> haslo;

        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << "!" << endl;
            return true;
        }
    }

    cout << "Blad logowania! Zle dane logowania" << endl;
    return false;
}

void BazaPracownikow::dodajPracownika(const Pracownik& pracownik) {
    listaPracownikow.push_back(pracownik);
    ofstream plik("baza_pracownikow.txt", ios::app);
    if (plik.is_open()) {
        plik << pracownik.getImie() << " " << pracownik.getNazwisko() << " "
            << pracownik.getLogin() << " " << pracownik.getHaslo() << " "
            << pracownik.getPensja() << endl;
        plik.close();
        cout << "Pracownik " << pracownik.getLogin() << " zostal dodany do bazy." << endl;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }
}
