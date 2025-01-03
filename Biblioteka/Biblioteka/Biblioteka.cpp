#include "header.h"
#include "BazaCzytelnikow.h"
#include "BazaKsiazek.h"
#include "Data.h"
#include "Egzemplarz.h"
#include "KontoCzytelnika.h"
#include "Ksiazka.h"
#include "Pracownik.h"
#include "Wypozyczenie.h"
#include "Zwrot.h"
#include "BazaPracownikow.h"

using namespace std;

int main() {
    BazaPracownikow bazaPracownikow;
    BazaCzytelnikow bazaCzytelnikow;
    BazaKsiazek bazaKsiazek;
    string login, funkcja;
    int wybor;

    system("cls"); //czyszczenie ekranu
    cout << "=====================================" << endl;
    cout << "  WITAMY W SYSTEMIE BIBLIOTECZNYM    " << endl;
    cout << "=====================================" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Wyjscie" << endl;
    cout << "=====================================" << endl;
    cout << "Wybierz opcje: ";
    cin >> wybor;

    switch (wybor) {
    case 1:
        tie(login, funkcja) = bazaPracownikow.logowanie();
        if (!login.empty() && !funkcja.empty()) {
            if (funkcja == "admin") {
                Administrator admin;
                cout << "Witaj " << login << " (admin)" << endl;
                do {
                    cout << "\n--- Menu Administratora ---\n";
                    cout << "1. Dodaj ksiazke\n";
                    cout << "2. Usun ksiazke\n";
                    cout << "3. Dodaj pracownika\n";
                    cout << "4. Usun pracownika\n";
                    cout << "5. Wyswietl ksiazki z bazy\n";
                    cout << "6. Zamknij program\n";
                    cout << "Wybor: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        //dodaj ksiazke
                        string tytul, autor;
                        int rok, ID;
                        cout << "Podaj tytul ksiazki: ";
                        cin.ignore();
                        getline(cin, tytul);
                        cout << "Podaj autora ksiazki: ";
                        getline(cin, autor);
                        cout << "Podaj rok wydania: ";
                        cin >> rok;
                        cout << "Nadaj ID ksiazki: ";
                        cin >> ID;
                        Ksiazka nowaKsiazka(ID, tytul, autor, rok);
                        admin.dodajKsiazke(bazaKsiazek, nowaKsiazka);
                        break;
                    }
                    case 2: {
                        //usun ksiazke
                        int kID;
                        cout << "Podaj ID ksiazki do usuniecia: ";
                        cin >> kID;
                        Ksiazka ksiazkaDoUsuniecia(kID);
                        admin.usunKsiazke(bazaKsiazek, ksiazkaDoUsuniecia);
                        break;
                    }
                    case 3: {
                        //dodaj pracownika
                        string imie, nazwisko, login, haslo, funkcja;
                        float pensja;
                        cout << "Podaj imie: ";
                        cin >> imie;
                        cout << "Podaj nazwisko: ";
                        cin >> nazwisko;
                        cout << "Podaj login: ";
                        cin >> login;
                        cout << "Podaj haslo: ";
                        cin >> haslo;
                        cout << "Podaj pensje: ";
                        cin >> pensja;
                        cout << "Podaj funkcje (admin/pracownik): ";
                        cin >> funkcja;
                        Pracownik nowyPracownik(imie, nazwisko, login, haslo, pensja, funkcja);
                        bazaPracownikow.dodajPracownika(nowyPracownik);
                        break;
                    }
                    case 4: {
                        // Usuwanie pracownika
                        string loginDoUsuniecia;
                        cout << "Podaj login pracownika do usuniecia: ";
                        cin >> loginDoUsuniecia;
                        // Metoda usunięcia pracownika
                        // bazaPracownikow.usunPracownika(loginDoUsuniecia);
                        break;
                    }
                    case 5: {
                        // Wyświetlanie książek
                        admin.wyswietlListeKsiazek();
                        break;
                    }
                    case 6:
                        cout << "Zamykanie programu..." << endl;
                        exit(0);
                        break;
                    default:
                        cout << "Niepoprawny wybor!" << endl;
                    }
                } while (true);
            }
            else if (funkcja == "pracownik") {
                // Tworzymy obiekt Pracownika
                Pracownik pracownik;
                cout << "Witaj " << login << " (pracownik)" << endl;
                do {
                    cout << "\n--- Menu Pracownika ---\n";
                    cout << "1. Sprawdz konto czytelnika\n";
                    cout << "2. Utworz konto czytelnika\n";
                    cout << "3. Usun konto czytelnika\n";
                    cout << "4. Zwrot ksiazki\n";
                    cout << "5. Wypozyczenie ksiazki\n";
                    cout << "6. Przyjmij kaucje\n";
                    cout << "7. Wyswietl ksiazki z bazy\n";
                    cout << "8. Zamknij program\n";
                    cout << "Wybor: ";
                    cin >> wybor;

                    switch (wybor) {
                    case 1: {
                        // Sprawdzenie konta czytelnika
                        // pracownik.sprawdzenieKonta();
                        break;
                    }
                    case 2: {
                        // Utwórz konto czytelnika
                        string pesel, imie, nazwisko;
                        
                        cout << "Podaj imie: ";
                        cin >> imie;
                        cout << "Podaj nazwisko: ";
                        cin >> nazwisko;
                        cout << "Podaj Pesel: ";
                        cin >> pesel;

                        KontoCzytelnika nowyCzytelnik(pesel, imie, nazwisko);
                        pracownik.dodajCzytelnika(bazaCzytelnikow, nowyCzytelnik);
                        break;
                    }
                    case 3: {
                        //usuniecie konta czytelnika
                        string pesel;
                        cout << "Podaj Pesel czytelnika do usuniecia: ";
                        cin >> pesel;
                        KontoCzytelnika czytelnikDoUsuniecia(pesel);
                        pracownik.usunCzytelnika(bazaCzytelnikow, czytelnikDoUsuniecia);
                        break;

                    }
                    case 4: {
                        // Zwrot książki
                        // pracownik.zwrotKsiazki();
                        break;
                    }
                    case 5: {
                        // Wypożyczenie książki
                        // pracownik.wypozyczKsiazke();
                        break;
                    }
                    case 6: {
                        // Przyjęcie kaucji
                        // pracownik.przyjmijKaucje();
                        break;
                    }
                    case 7: {
                        // Wyświetlanie książek
                        pracownik.wyswietlListeKsiazek();
                        break;
                    }
                    case 8:
                        cout << "Zamykanie programu..." << endl;
                        exit(0);
                        break;
                    default:
                        cout << "Niepoprawny wybor!" << endl;
                    }
                } while (true);
            }
        }
        else {
            cout << "Bledne dane logowania!" << endl;
        }
        break;
    case 2:
        cout << "Wyjscie z programu" << endl;
        break;
    default:
        cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
        system("pause");
        break;
    }

    return 0;
}
