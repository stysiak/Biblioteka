#include "../../include/database/EmployeeDatabase.h"

string EmployeeDatabase::fileName = "../../data/employees_database.txt";


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

// Konstruktor domy�lny; wczytuje dane pracownik�w z pliku i inicjalizuje list� pracownik�w
EmployeeDatabase::EmployeeDatabase() {
    ifstream plik(fileName);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.txt :(" << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja, pesel;

        // Odczytujemy dane z pliku
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        getline(ss, funkcja, ',');

        // Sprawdzamy funkcj� pracownika
        if (funkcja != "admin" && funkcja != "pracownik") {
            cerr << "Niepoprawna funkcja: " << funkcja << ". Pomijanie wpisu." << endl;
            continue;
        }

        // Dodanie pracownika do listy
        Employee p(imie, nazwisko, login, haslo, pesel, funkcja);
        listaPracownikow.push_back(p);
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
        cerr << "Nie mozna otworzyc pliku employees_database.txt :-" << endl;
        return { "", "" };
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja, pesel;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        getline(ss, funkcja, ',');

        // Sprawdzenie poprawno�ci loginu i has�a
        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
            return { login, funkcja };
        }
    }

    // Je�li nie znaleziono dopasowania
    return { "", "" };
}


// Funkcja dodaj�ca nowego pracownika do bazy i zapisuj�ca jego dane w pliku
int EmployeeDatabase::dodajPracownika(const Employee& pracownik) {
    string peselStr = pracownik.getPesel();

    if (!walidujPesel(peselStr)) {
        return -1;
    }

    // Sprawdzamy, czy pracownik o tym samym PESEL ju� istnieje w bazie
    ifstream plik(fileName);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.txt ;O" << endl;
        return -1;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string istniej�cyPesel;

        // Odczytujemy PESEL pracownika z pliku
        getline(ss, istniej�cyPesel, ',');

        // Sprawdzamy, czy PESEL ju� istnieje
        if (istniej�cyPesel == peselStr) {
            cerr << "Employee o takim PESEL juz istnieje!" << endl;
            plik.close();
            return -1;
        }
    }

    plik.close();

    // Sprawdzenie funkcji pracownika
    if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
        cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Employee nie zostal dodany." << endl;
        return -1;
    }

    // Dodanie pracownika
    listaPracownikow.push_back(pracownik);

    ofstream plikDoZapisu(fileName, ios::app);
    if (plikDoZapisu.is_open()) {
        plikDoZapisu << pracownik.getPesel() << "," << pracownik.getImie() << "," << pracownik.getNazwisko() << ","
            << pracownik.getLogin() << "," << pracownik.getHaslo() << "," << pracownik.getFunkcja() << "\n";
        plikDoZapisu.close();
        return 1;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }

    return -1;
}


//funkcja usuwaj�ca pracownika z bazy na podstawie jego numeru PESEL
int EmployeeDatabase::usunPracownika(const Employee& pracownik) {
    string pesel = pracownik.getPesel();

    if (!walidujPesel(pesel)) {
        return -1;
    }

    ifstream input_file(fileName);

    if (!input_file.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(input_file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id != pesel) {
            lines.push_back(line);
        }
        else {
            found = true;
        }
    }

    input_file.close();

    if (!found) {
        cout << "Nie znaleziono pracownika o PESEL " << pesel << endl;
        return -1;
    }

    ofstream output_file(fileName);
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        output_file << l << endl;
    }

    output_file.close();

    return 1;
}

// Funkcja wy�wietlaj�ca list� wszystkich pracownik�w w bazie
void EmployeeDatabase::wyswietlListePracownikow() const {
    ifstream plik(fileName);

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku employees_database.txt ;E" << endl;
        return;
    }

    string linia;
    cout << "\n--- Lista pracownikow ---" << endl;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string pesel, imie, nazwisko, login, haslo, funkcja;

        // Odczytujemy dane z pliku
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        getline(ss, funkcja, ',');

        cout << "Pesel: " << pesel
            << ", Imie: " << imie
            << ", Nazwiwsko: " << nazwisko
            << ", Login: " << login
            << ", Haslo: " << haslo
            << ", Funkcja: " << funkcja << endl;
    }

    plik.close();
}
