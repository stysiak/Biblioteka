#include "BazaPracownikow.h"

//konstruktor domyœlny; wczytuje dane pracowników z pliku i inicjalizuje listê pracowników
BazaPracownikow::BazaPracownikow() {
    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return;
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja, pesel;
        float pensja;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        ss >> pensja;
        ss.ignore(1, ',');
        getline(ss, funkcja, ',');

        if (funkcja != "admin" && funkcja != "pracownik") {
            cerr << "Niepoprawna funkcja: " << funkcja << ". Pomijanie wpisu." << endl;
            continue;
        }
        //dodanie pracownika do listy
        Pracownik p(imie, nazwisko, login, haslo, pesel, pensja, funkcja);
        listaPracownikow.push_back(p);
    }
    plik.close();
}
//funckja s³u¿¹ca do logowania pracownika na podstawie wpisanego loginu i has³a
pair<string, string> BazaPracownikow::logowanie() {
    string wpisanyLogin, wpisaneHaslo;
    cout << "Podaj login: ";
    cin >> wpisanyLogin;
    cout << "Podaj haslo: ";
    cin >> wpisaneHaslo;

    ifstream plik("baza_pracownikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return { "", "" };
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko, login, haslo, funkcja, pesel;
        float pensja;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        ss >> pensja;
        ss.ignore(1, ',');
        getline(ss, funkcja, ',');
        //sprawdzenie poprawnoœci loginu i has³a
        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
            return { login, funkcja };
        }
    }
    return { "", "" };
}

//funkcja dodaj¹ca nowego pracownika do bazy i zapisuj¹ca jego dane w pliku
int BazaPracownikow::dodajPracownika(const Pracownik& pracownik) {
    string peselStr = pracownik.getPesel();
    if (peselStr.length() != 11) {
        cerr << "Nieprawidlowy PESEL: " << peselStr << ". PESEL powinien miec 11 cyfr." << endl;
        return -1;
    }
    //sprawdzenie funkcji pracownika
    if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
        cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Pracownik nie zostal dodany." << endl;
        return -1;
    }
    //dodanie pracownika
    listaPracownikow.push_back(pracownik);

    ofstream plik("baza_pracownikow.txt", ios::app);
    if (plik.is_open()) {
        plik << pracownik.getPesel() << "," << pracownik.getImie() << "," << pracownik.getNazwisko() << ","
            << pracownik.getLogin() << "," << pracownik.getHaslo() << ","
            << pracownik.getPensja() << "," << pracownik.getFunkcja() << "\n";
        plik.close();
        return 1;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }

}

//funkcja usuwaj¹ca pracownika z bazy na podstawie jego numeru PESEL
int BazaPracownikow::usunPracownika(const Pracownik& pracownik) {
    string pesel = pracownik.getPesel();
    ifstream input_file("baza_pracownikow.txt");

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
        cout << "Nie znaleziono pracownika o Peselu " << pesel << endl;
        return -1;
    }

    ofstream output_file("baza_pracownikow.txt");
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
//funkcja wyœwietlaj¹ca listê wszystkich pracowników w bazie
void BazaPracownikow::wyswietlListePracownikow() const {
    ifstream plik("baza_pracownikow.txt");

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_pracownikow.txt" << endl;
        return;
    }

    string linia;
    cout << "\n--- Lista pracownikow ---" << endl;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string pesel, imie, nazwisko, login, haslo, pensja, funkcja;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, login, ',');
        getline(ss, haslo, ',');
        getline(ss, pensja, ',');
        getline(ss, funkcja, ',');

        cout << "Pesel: " << pesel
            << ", Imie: " << imie
            << ", Nazwiwsko: " << nazwisko
            << ", Login: " << login
            << ", Haslo: " << haslo
            << ", Pensja: " << pensja
            << ", Funkcja: " << funkcja << endl;
    }

    plik.close();
}


