#include "../../include/database/BookDatabase.h"

string BookDatabase::fileName = "../../data/books_database.txt";

BookDatabase::BookDatabase() {}


int BookDatabase::aktualizujStanDodaj(const Book& ksiazka) {
    ifstream plik(fileName);
    string linia;

    if (plik.is_open()) {
        while (getline(plik, linia)) {
            int fileID;
            stringstream ss(linia);
            ss >> fileID;

            if (fileID == ksiazka.getID()) { //por�wnanie ID
                cerr << "Book o ID " << ksiazka.getID() << " juz istnieje." << endl;
                plik.close();
                return -1;
            }
        }
        plik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -2;
    }

    // Tworzenie lokalnej kopii ksi��ki z automatycznie ustawionym stanem "dost�pna"
    Book nowaKsiazka(ksiazka.getID(), ksiazka.getTytul(), ksiazka.getNazwiskoAutora(), ksiazka.getRokWydania(), "dostepna");

    // Dodanie ksi��ki do mapy
    ksiazki[nowaKsiazka.getID()] = make_shared<Book>(nowaKsiazka);

    ofstream outPlik(fileName, ios::app);
    if (outPlik.is_open()) {
        outPlik << nowaKsiazka.getID() << "," << nowaKsiazka.getTytul() << "," << nowaKsiazka.getNazwiskoAutora() << "," << nowaKsiazka.getRokWydania() << "," << nowaKsiazka.getStan() << endl;
        outPlik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -3;
    }
    return nowaKsiazka.getID();
}



//funkcja usuwaj�ca ksi��k� z bazy na podstawie ID
int BookDatabase::aktualizujStanUsun(const Book& ksiazka) {
    int kID = ksiazka.getID();
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
        int id;
        ss >> id;

        if (id != kID) {
            lines.push_back(line); //dodanie wiersza do wektora, je�li nie dotyczy usuwanej ksi��ki
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

    ofstream output_file(fileName);
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        output_file << l << endl;
    }
    output_file.close();

    ksiazki.erase(kID); //usuni�cie ksi��ki z mapy
    return kID;
}

//funkcja wy�wietlaj�ca list� wszystkich ksi��ek w bazie
void BookDatabase::wyswietlListeKsiazek() const {
    ifstream plik(fileName);

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.txt" << endl;
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