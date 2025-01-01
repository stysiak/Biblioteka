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

void BazaPracownikow::logowanie() {
    string wpisanyLogin, wpisaneHaslo;
    cout << "Podaj login: ";
    cin >> wpisanyLogin;
    cout << "Podaj haslo: ";
    cin >> wpisaneHaslo;

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

        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
            if (funkcja == "admin") {
                Administrator admin(imie, nazwisko, login, haslo, pensja, funkcja);
                int wybor;
                do {
                    cout << "\n--- Menu Administratora ---\n";
                    cout << "1. Dodaj ksiazke\n";
                    cout << "2. Usun ksiazke\n";
                    cout << "Wybor: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        string tytul, autor;
                        int rok;
                        cout << "Podaj tytul ksiazki: ";
                        cin.ignore();
                        getline(cin, tytul);
                        cout << "Podaj autora ksiazki: ";
                        getline(cin, autor);
                        cout << "Podaj rok wydania: ";
                        cin >> rok;
                        admin.dodajKsiazke(*BazaKsiazek::getInstance(), tytul, autor, rok);
                        break;
                    }
                    case 2:
                        /*int kID;
                        cout << "Podaj ID ksiazki do usuniecia: ";
                        cin >> kID;
                        admin.usunKsiazke(*BazaKsiazek::getInstance(), kID);*/
                        break;
                    default:
                        cout << "Niepoprawny wybor!\n";
                    }
                } while (true);
            }
            else if (funkcja == "pracownik") {
                Pracownik pracownik(imie, nazwisko, login, haslo, pensja, funkcja);
                int wybor;
                do {
                    cout << "\n--- Menu Pracownika ---\n";
                    cout << "1. Sprawdz konto czytelnika\n";
                    cout << "2. Przyjmij kaucje\n";
                    cout << "Wybor: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1:
                        cout << "Sprawdzanie konta czytelnika...\n";
                        //pracownik.sprawdzenieKonta();  
                        break;
                    case 2:
                        cout << "Przyjmowanie kaucji...\n";
                        //pracownik.przyjmijKaucje(); 
                        break;
                    default:
                        cout << "Niepoprawny wybor!\n";
                    }
                } while (true);
            }
            return;
        }
    }

    cout << "Blad logowania! Zle dane logowania" << endl;
}

void BazaPracownikow::dodajPracownika(const Pracownik& pracownik) {
    if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
        cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Pracownik nie zostal dodany." << endl;
        return;
    }

    listaPracownikow.push_back(pracownik);
    ofstream plik("baza_pracownikow.txt", ios::app);
    if (plik.is_open()) {
        plik << pracownik.getImie() << " " << pracownik.getNazwisko() << " "
            << pracownik.getLogin() << " " << pracownik.getHaslo() << " "
            << pracownik.getPensja() << " " << pracownik.getFunkcja() << endl;
        plik.close();
        cout << "Pracownik " << pracownik.getLogin() << " zostal dodany do bazy." << endl;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }
}
