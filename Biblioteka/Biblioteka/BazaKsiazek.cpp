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
    int id;
    ksiazki[id] = make_shared<Ksiazka>(ksiazka);

    ofstream outPlik("baza_ksiazek.txt", ios::app);
    if (outPlik.is_open()) {
        outPlik << ksiazka.getID() << ", " << ksiazka.getTytul() << ", " << ksiazka.getNazwiskoAutora() << ", " << ksiazka.getRokWydania() << endl;
        outPlik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }
    return id;
}

//void BazaKsiazek::dodajEgzemplarzDoKsiazki(int kID) {
//    if (ksiazki.count(kID) > 0) {
//        int eID = ++egzID;
//        ksiazki.at(kID)->dodajEgzemplarz(eID);
//    }
//    else {
//        cout << "Podano bledne ID ksiazki" << endl;
//    }
//}

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

    return kID;
}




void BazaKsiazek::usunEgzemplarzKsiazki(int eID) {

}

bool BazaKsiazek::aktualizujStanPoWypozyczeniu(Egzemplarz e) {
    return true;
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
        string id, tytul, autor, rok;

        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');

        cout << "ID: " << id
            << ", Tytul: " << tytul
            << ", Autor: " << autor
            << ", Rok: " << rok << endl;
    }

    plik.close();
}

