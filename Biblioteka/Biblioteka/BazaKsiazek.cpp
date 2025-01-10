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

// Zaktualizowana funkcja wypo¿yczaj¹ca ksi¹¿kê
int BazaKsiazek::wypozyczKsiazke(const Ksiazka& ksiazka) {
    ifstream plik("baza_ksiazek.txt");
    vector<string> lines;
    string line;
    bool found = false;

    time_t now = time(0);
    tm ltm = {};
    localtime_s(&ltm, &now);
    ltm.tm_mday += 30;  // Dodajemy 30 dni do bie¿¹cej daty
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

        if (stoi(id) == ksiazka.getID() && stan == "dostepna") {
            line = id + "," + tytul + "," + autor + "," + rok + ",niedostepna," + dataZwrotu;
            found = true;
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Ksiazka o ID " << ksiazka.getID() << " jest niedostepna lub nie istnieje!" << endl;
        return -1;
    }

    ofstream outPlik("baza_ksiazek.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Ksiazka o ID " << ksiazka.getID() << " zostala wypozyczona. Data zwrotu: " << dataZwrotu << endl;
    return ksiazka.getID();
}

// Zaktualizowana funkcja zwracaj¹ca ksi¹¿kê
float BazaKsiazek::zwrocKsiazke(const Ksiazka& ksiazka) {
    float kaucja = 0.0f;  // Zmienna do przechowywania kaucji
    string dataZwrotuFile;
    time_t now = time(0);
    tm localTime = {};
    localtime_s(&localTime, &now);
    string currentDate = to_string(1900 + localTime.tm_year) + "-" + to_string(1 + localTime.tm_mon) + "-" + to_string(localTime.tm_mday);

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

        if (stoi(id) == ksiazka.getID() && stan == "niedostepna") {
            found = true;

            // Calculate late fee if applicable
            if (dataZwrotuFile < currentDate) {
                tm dataZwrotu = {};
                istringstream ss(dataZwrotuFile);
                ss >> get_time(&dataZwrotu, "%Y-%m-%d");
                if (ss.fail()) {
                    cerr << "Blad konwersji daty!" << endl;
                    return -1.0f;
                }

                time_t tDataZwrotu = mktime(&dataZwrotu);
                double secondsLate = difftime(now, tDataZwrotu);
                int lateDays = secondsLate / (60 * 60 * 24);
                if (lateDays > 0) {
                    kaucja = lateDays * 2.0f;  // Kaucja = late days * 2zl
                }
            }

            // Update the line to set the book to "dostepna" and clear the return date
            line = id + "," + tytul + "," + autor + "," + rok + ",dostepna,";
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Blad zwrotu! Egzemplarz o ID " << ksiazka.getID() << " nie byl wypozyczony." << endl;
        return -1.0f;
    }

    // Save updated lines to the file
    ofstream outPlik("baza_ksiazek.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    // Output the result of the return
    if (kaucja > 0.0f) {
        cout << "Ksiazka zwrocona po terminie. Naliczenie kaucji: " << kaucja << " zl." << endl;
    }
    else {
        cout << "Ksiazka o ID " << ksiazka.getID() << " zostala zwrocona w terminie." << endl;
    }

    return kaucja;  // Zwracamy wartoœæ kaucji
}



