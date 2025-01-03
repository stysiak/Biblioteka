#include "BazaPracownikow.h"
#include "BazaKsiazek.h"

BazaPracownikow::BazaPracownikow() {
    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja;
        float pensja;

        ss >> imie >> nazwisko >> login >> haslo >> pensja >> funkcja;
        if (funkcja != "admin" && funkcja != "pracownik") {
            cerr << "Niepoprawna funkcja: " << funkcja << ". Pomijanie wpisu." << endl;
            continue;
        }

        Pracownik p(imie, nazwisko, login, haslo, pensja, funkcja);
        listaPracownikow.push_back(p);
    }
    plik.close();
}

pair<string, string> BazaPracownikow::logowanie() {
    string wpisanyLogin, wpisaneHaslo;
    cout << "Podaj login: ";
    cin >> wpisanyLogin;
    cout << "Podaj haslo: ";
    cin >> wpisaneHaslo;

    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return { "", "" }; // Zwracamy pust¹ parê w przypadku b³êdu
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja;
        float pensja;

        ss >> imie >> nazwisko >> login >> haslo >> pensja >> funkcja;

        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
            return { login, funkcja };  // Zwracamy login i funkcjê u¿ytkownika
        }
    }

    cout << "Blad logowania! Zle dane logowania" << endl;
    return { "", "" }; // Zwracamy pust¹ parê w przypadku b³êdu logowania
}

void BazaPracownikow::dodajPracownika(const Pracownik& pracownik) {
    if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
        cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Pracownik nie zostal dodany." << endl;
        return;
    }

    listaPracownikow.push_back(pracownik);  // Dodanie pracownika do wektora

    // Zapis do pliku
    ofstream plik("baza_pracownikow.txt", ios::app);  // Otwieranie pliku w trybie do dopisywania
    if (plik.is_open()) {
        plik << pracownik.getImie() << " " << pracownik.getNazwisko() << " "
            << pracownik.getLogin() << " " << pracownik.getHaslo() << " "
            << pracownik.getPensja() << " " << pracownik.getFunkcja() << "\n";  // Dodanie \n na koñcu
        plik.close();
        cout << "Pracownik " << pracownik.getLogin() << " zostal dodany do bazy." << endl;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }
}

