#include "BazaKsiazek.h"

using namespace std;

BazaKsiazek* BazaKsiazek::instance = nullptr;

BazaKsiazek::BazaKsiazek() {
    
}

int BazaKsiazek::aktualizujStanDodaj(const string& tytul, const string& autor, int rok) {
    int id = ++ID;
    ksiazki[id] = make_shared<Ksiazka>(id, tytul, autor, rok);

    ofstream plik("baza_ksiazek.txt", ios::app); 
    if (plik.is_open()) {
        plik << id << ", " << tytul << ", " << autor << ", " << rok << endl;
        plik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku!" << endl;
    }
    return id;
}


void BazaKsiazek::dodajEgzemplarzDoKsiazki(int kID) {
    if (ksiazki.count(kID) > 0) {
        int eID = ++egzID;
        ksiazki.at(kID)->dodajEgzemplarz(eID);
    }
    else {
        cout << "Podano bledne ID ksiazki" << endl;
    }
}

void BazaKsiazek::aktualizujStanUsun(int kID) {
    if (ksiazki.count(kID) > 0) {
        ksiazki.erase(kID);
        cout << "Usunieto ksiazke" << endl;
    }
}


void BazaKsiazek::usunEgzemplarzKsiazki(int eID) {

}

bool BazaKsiazek::aktualizujStanPoWypozyczeniu(Egzemplarz e) {
    return true;
}

BazaKsiazek* BazaKsiazek::getInstance() {
    if (!instance) {
        instance = new BazaKsiazek();  
    }
    return instance;
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

