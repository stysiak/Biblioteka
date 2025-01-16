#include "BazaKsiazek.h"

BazaKsiazek::BazaKsiazek() {}

//funkcja dodaj¹ca now¹ ksi¹¿kê do bazy, sprawdzaj¹c czy ksi¹¿ka o danym ID ju¿ istnieje
int BazaKsiazek::aktualizujStanDodaj(const Ksiazka& ksiazka) {
    ifstream plik("baza_ksiazek.txt");
    string linia;

    if (plik.is_open()) {
        while (getline(plik, linia)) {
            int fileID;
            stringstream ss(linia);
            ss >> fileID;

            if (fileID == ksiazka.getID()) { //porównanie ID
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

    // Tworzenie lokalnej kopii ksi¹¿ki z automatycznie ustawionym stanem "dostêpna"
    Ksiazka nowaKsiazka(ksiazka.getID(), ksiazka.getTytul(), ksiazka.getNazwiskoAutora(), ksiazka.getRokWydania(), "dostepna");

    // Dodanie ksi¹¿ki do mapy
    ksiazki[nowaKsiazka.getID()] = make_shared<Ksiazka>(nowaKsiazka);

    ofstream outPlik("baza_ksiazek.txt", ios::app);
    if (outPlik.is_open()) {
        outPlik << nowaKsiazka.getID() << "," << nowaKsiazka.getTytul() << "," << nowaKsiazka.getNazwiskoAutora() << "," << nowaKsiazka.getRokWydania() << "," << nowaKsiazka.getStan() << endl;
        outPlik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }
    return nowaKsiazka.getID();
}



//funkcja usuwaj¹ca ksi¹¿kê z bazy na podstawie ID
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
            lines.push_back(line); //dodanie wiersza do wektora, jeœli nie dotyczy usuwanej ksi¹¿ki
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

    ksiazki.erase(kID); //usuniêcie ksi¹¿ki z mapy
    return kID;
}

//funkcja wyœwietlaj¹ca listê wszystkich ksi¹¿ek w bazie
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