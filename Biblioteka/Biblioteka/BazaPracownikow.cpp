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

        Pracownik p(imie, nazwisko, login, haslo, pesel, pensja, funkcja);
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

        if (login == wpisanyLogin && haslo == wpisaneHaslo) {
            cout << "Logowanie pomyslne. Witaj " << login << " (" << funkcja << ")!" << endl;
            return { login, funkcja };
        }
    }

    cout << "Blad logowania! Zle dane logowania" << endl;
    return { "", "" };
}

void BazaPracownikow::dodajPracownika(const Pracownik& pracownik) {
    if (pracownik.getFunkcja() != "admin" && pracownik.getFunkcja() != "pracownik") {
        cerr << "Niepoprawna funkcja: " << pracownik.getFunkcja() << ". Pracownik nie zostal dodany." << endl;
        return;
    }

    listaPracownikow.push_back(pracownik);

    ofstream plik("baza_pracownikow.txt", ios::app);
    if (plik.is_open()) {
        plik << pracownik.getPesel() << "," << pracownik.getImie() << "," << pracownik.getNazwisko() << ","
            << pracownik.getLogin() << "," << pracownik.getHaslo() << ","
            << pracownik.getPensja() << "," << pracownik.getFunkcja() << "\n";
        plik.close();
        cout << "Pracownik " << pracownik.getLogin() << " zostal dodany do bazy." << endl;
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!\n";
    }
}

void BazaPracownikow::usunPracownika(const Pracownik& pracownik) {
    string pesel = pracownik.getPesel();
    ifstream input_file("baza_pracownikow.txt");

    if (!input_file.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    // Odczytujemy plik i zapisujemy wszystkie linie oprócz tej z usuwanym PESEL
    while (getline(input_file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');  // Odczytaj PESEL z pliku

        if (id != pesel) {
            lines.push_back(line);  // Jeœli PESEL siê nie zgadza, zapisujemy liniê
        }
        else {
            found = true;  // ZnaleŸliœmy pracownika do usuniêcia
        }
    }

    input_file.close();

    if (!found) {
        cout << "Nie znaleziono pracownika o Peselu " << pesel << endl;
        return;
    }

    // Teraz zapisujemy zaktualizowane dane do pliku, nadpisuj¹c go
    ofstream output_file("baza_pracownikow.txt");
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return;
    }

    for (const auto& l : lines) {
        output_file << l << endl;  // Zapisujemy ka¿d¹ liniê do pliku
    }

    output_file.close();
    cout << "Pracownik o numerze PESEL " << pesel << " zostal usuniety." << endl;
}


