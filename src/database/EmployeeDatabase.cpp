#include "../../include/database/EmployeeDatabase.h"

string EmployeeDatabase::fileName = "../../data/employees_database.json";

bool EmployeeDatabase::walidujPesel(const string& pesel) {
    if (pesel.length() != 11) {
        cerr << "Nieprawidlowy PESEL: " << pesel << ". PESEL powinien miec 11 cyfr." << endl;
        return false;
    }

    if (!std::all_of(pesel.begin(), pesel.end(), ::isdigit)) {
        cerr << "PESEL musi zawierac tylko cyfry!" << endl;
        return false;
    }

    return true;
}

// Konstruktor domyślny; wczytuje dane pracowników z pliku JSON i inicjalizuje listę pracowników
EmployeeDatabase::EmployeeDatabase() {
    ifstream plik(fileName);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.json :(" << endl;
        return;
    }

    try {
        json j;
        plik >> j;

        for (const auto& pracownik : j) {
            string pesel = pracownik["pesel"];
            string imie = pracownik["imie"];
            string nazwisko = pracownik["nazwisko"];
            string login = pracownik["login"];
            string haslo = pracownik["haslo"];
            string funkcja = pracownik["rola"];

            // Sprawdzamy funkcję pracownika
            if (funkcja != "admin" && funkcja != "pracownik") {
                cerr << "Niepoprawna funkcja: " << funkcja << ". Pomijanie wpisu." << endl;
                continue;
            }

            // Dodanie pracownika do listy
            Employee p(imie, nazwisko, login, haslo, pesel, funkcja);
            listaPracownikow.push_back(p);
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
    }

    plik.close();
}

pair<string, string> EmployeeDatabase::logowanie() {
    string wpisanyLogin, wpisaneHaslo;
    cout << "Podaj login: ";
    cin >> wpisanyLogin;
    cout << "Podaj haslo: ";
    cin >> wpisaneHaslo;

    ifstream plik(fileName);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.json :-" << endl;
        return { "", "" };
    }

    try {
        json j;
        plik >> j;

        for (const auto& pracownik : j) {
            string login = pracownik["login"];
            string haslo = pracownik["haslo"];
            string funkcja = pracownik["rola"];

            // Sprawdzenie poprawności loginu i hasła
            if (login == wpisanyLogin && haslo == wpisaneHaslo) {
                cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
                return { login, funkcja };
            }
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
    }

    plik.close();

    // Jeśli nie znaleziono dopasowania
    return { "", "" };
}

// Funkcja dodająca nowego pracownika do bazy i zapisująca jego dane w pliku JSON
int EmployeeDatabase::dodajPracownika(const Employee& pracownik) {
    string peselStr = pracownik.getPesel();

    if (!walidujPesel(peselStr)) {
        return -1;
    }

    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.json ;O" << endl;
        return -1;
    }

    json pracownicy;
    try {
        plikOdczyt >> pracownicy;
        plikOdczyt.close();

        // Sprawdzamy, czy pracownik o tym samym PESEL już istnieje w bazie
        for (const auto& p : pracownicy) {
            if (p["pesel"] == peselStr) {
                cerr << "Employee o takim PESEL juz istnieje!" << endl;
                return -1;
            }
        }

        // Sprawdzenie funkcji pracownika
        if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
            cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Employee nie zostal dodany." << endl;
            return -1;
        }

        // Dodanie pracownika do listy
        listaPracownikow.push_back(pracownik);

        // Tworzymy nowy obiekt JSON dla pracownika
        json nowyPracownik;
        nowyPracownik["pesel"] = pracownik.getPesel();
        nowyPracownik["imie"] = pracownik.getImie();
        nowyPracownik["nazwisko"] = pracownik.getNazwisko();
        nowyPracownik["login"] = pracownik.getLogin();
        nowyPracownik["haslo"] = pracownik.getHaslo();
        nowyPracownik["rola"] = pracownik.getFunkcja();

        // Dodajemy nowego pracownika do tablicy JSON
        pracownicy.push_back(nowyPracownik);

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << pracownicy << endl;
            plikZapis.close();
            return 1;
        }
        else {
            cerr << "Nie mozna otworzyc pliku do zapisu!\n";
            return -1;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
        return -1;
    }
}

// Funkcja usuwająca pracownika z bazy na podstawie jego numeru PESEL
int EmployeeDatabase::usunPracownika(const Employee& pracownik) {
    string pesel = pracownik.getPesel();

    if (!walidujPesel(pesel)) {
        return -1;
    }

    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    json pracownicy;
    bool found = false;

    try {
        plikOdczyt >> pracownicy;
        plikOdczyt.close();

        // Tworzymy nową tablicę bez pracownika o podanym PESEL
        json nowaPracownicy = json::array();

        for (const auto& p : pracownicy) {
            if (p["pesel"] != pesel) {
                nowaPracownicy.push_back(p);
            } else {
                found = true;
            }
        }

        if (!found) {
            cout << "Nie znaleziono pracownika o PESEL " << pesel << endl;
            return -1;
        }

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << nowaPracownicy << endl;
            plikZapis.close();
            return 1;
        }
        else {
            cerr << "Blad otwarcia pliku do zapisu!" << endl;
            return -1;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
        return -1;
    }
}

// Funkcja wyświetlająca listę wszystkich pracowników w bazie
void EmployeeDatabase::wyswietlListePracownikow() const {
    ifstream plik(fileName);

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.json ;E" << endl;
        return;
    }

    try {
        json j;
        plik >> j;

        cout << "\n--- Lista pracownikow ---" << endl;

        for (const auto& pracownik : j) {
            cout << "Pesel: " << pracownik["pesel"]
                 << ", Imie: " << pracownik["imie"]
                 << ", Nazwiwsko: " << pracownik["nazwisko"]
                 << ", Login: " << pracownik["login"]
                 << ", Haslo: " << pracownik["haslo"]
                 << ", Funkcja: " << pracownik["rola"] << endl;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
    }

    plik.close();
}