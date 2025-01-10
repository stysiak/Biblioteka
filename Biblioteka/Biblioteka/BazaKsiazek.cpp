#include "BazaKsiazek.h"

using namespace std;

BazaKsiazek::BazaKsiazek() {}

int BazaKsiazek::aktualizujStanDodaj(const Ksiazka& ksiazka) {
    ifstream plik("baza_ksiazek.txt");
    string linia;

    if (plik.is_open()) {
        while (getline(plik, linia)) {
            int fileID;
            stringstream ss(linia);
            ss >> fileID;

            if (fileID == ksiazka.getID()) {
                cerr << "Ksiazka o ID " << ksiazka.getID() << " juz istnieje." << endl;
                plik.close();
                return -1;
            }
        }
        plik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    ksiazki[ksiazka.getID()] = make_shared<Ksiazka>(ksiazka);

    ofstream outPlik("baza_ksiazek.txt", ios::app);
    if (outPlik.is_open()) {
        outPlik << ksiazka.getID() << "," << ksiazka.getTytul() << "," << ksiazka.getNazwiskoAutora() << "," << ksiazka.getRokWydania() << "," << ksiazka.getStan() << endl;
        outPlik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }
    return ksiazka.getID();
}

int BazaKsiazek::aktualizujStanUsun(const Ksiazka& ksiazka) {
    int kID = ksiazka.getID();
    ifstream input_file("baza_ksiazek.txt");

    if (!input_file.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(input_file, line)) {
        stringstream ss(line);
        int id;
        ss >> id;

        if (id != kID) {
            lines.push_back(line);
        }
        else {
            found = true;
        }
    }

    input_file.close();

    if (!found) {
        cout << "Nie znaleziono ksiazki o ID " << kID << endl;
        return -1;
    }

    ofstream output_file("baza_ksiazek.txt");
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        output_file << l << endl;
    }
    output_file.close();

    ksiazki.erase(kID);
    return kID;
}

void BazaKsiazek::wyswietlListeKsiazek() const {
    ifstream plik("baza_ksiazek.txt");

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_ksiazek.txt" << endl;
        return;
    }

    string linia;
    cout << "\n--- Lista ksiazek ---" << endl;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string id, tytul, autor, rok, stan, dataZwrotuFile;

        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');
        getline(ss, stan, ',');
        getline(ss, dataZwrotuFile, ',');

        cout << "ID: " << id
            << ", Tytul: " << tytul
            << ", Autor: " << autor
            << ", Rok: " << rok
            << ", Stan: " << stan;

        if (stan == "niedostepna") {
            cout << ", Data zwrotu: " << dataZwrotuFile;
        }

        cout << endl;
    }

    plik.close();
}

int BazaKsiazek::wypozyczKsiazke(int egzemplarzID) {
    ifstream plik("baza_ksiazek.txt");
    vector<string> lines;
    string line;
    bool found = false;

    time_t now = time(0);
    tm ltm = {};
    localtime_s(&ltm, &now);
    ltm.tm_mday += 30;
    mktime(&ltm);
    ostringstream oss;
    oss << put_time(&ltm, "%Y-%m-%d");
    string dataZwrotu = oss.str();

    while (getline(plik, line)) {
        stringstream ss(line);
        string id, tytul, autor, rok, stan, dataZwrotuFile;
        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');
        getline(ss, stan, ',');
        getline(ss, dataZwrotuFile, ',');

        if (stoi(id) == egzemplarzID && stan == "dostepna") {
            line = id + "," + tytul + "," + autor + "," + rok + ",niedostepna," + dataZwrotu;
            found = true;
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Egzemplarz jest niedostepny lub nie istnieje!" << endl;
        return -1;
    }

    ofstream outPlik("baza_ksiazek.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Ksiazka o ID " << egzemplarzID << " zostala wypozyczona. Data zwrotu: " << dataZwrotu << endl;
    return egzemplarzID;
}

int BazaKsiazek::zwrocKsiazke(int egzemplarzID) {
    ifstream plik("baza_ksiazek.txt");
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(plik, line)) {
        stringstream ss(line);
        string id, tytul, autor, rok, stan, dataZwrotuFile;
        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');
        getline(ss, stan, ',');
        getline(ss, dataZwrotuFile, ',');

        if (stoi(id) == egzemplarzID && stan == "niedostepna") {
            line = id + "," + tytul + "," + autor + "," + rok + ",dostepna,";
            found = true;
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Blad zwrotu! Egzemplarz nie byl wypozyczony." << endl;
        return -1;
    }

    ofstream outPlik("baza_ksiazek.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Ksiazka o ID " << egzemplarzID << " zostala zwrocona." << endl;
    return egzemplarzID;
}

