#include "../../include/database/BookDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

string BookDatabase::fileName = "../../data/books_database.json";

BookDatabase::BookDatabase() {
    cout << "Proba otwarcia pliku: " << fileName << endl;
    ifstream plik(fileName);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.json :(" << endl;
        return;
    }
    json j;
    plik >> j;
    plik.close();

    cout << "Wczytano dane JSON. Liczba ksiazek: " << j.size() << endl;

    for (const auto& ksiazka : j) {
        int id = ksiazka["id"];
        string tytul = ksiazka["tytul"];
        string autor = ksiazka["autor"];
        int rok = ksiazka["rok"];
        string status = ksiazka["status"];
        string dataZwrotu = "";

        // Jeśli książka ma datę zwrotu (jest wypożyczona)
        if (ksiazka.contains("dataZwrotu") && !ksiazka["dataZwrotu"].is_null()) {
            dataZwrotu = ksiazka["dataZwrotu"];
        }

        cout << "Wczytano ksiazke: " << id << " - " << tytul << " (" << status << ")" << endl;

        // Dodanie książki do mapy
        Book nowaKsiazka(id, tytul, autor, rok, status);
        ksiazki[id] = make_shared<Book>(nowaKsiazka);
    }
}

// Funkcja dodająca nową książkę do bazy danych
int BookDatabase::aktualizujStanDodaj(const Book& ksiazka) {
    int kID = ksiazka.getID();

    // Otwieramy plik JSON
    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.json do odczytu!" << endl;
        return -2;
    }

    try {
        json ksiazkiJson;
        plikOdczyt >> ksiazkiJson;
        plikOdczyt.close();

        // Sprawdzamy, czy książka o podanym ID już istnieje
        for (const auto& k : ksiazkiJson) {
            if (k["id"] == kID) {
                cerr << "Book o ID " << kID << " juz istnieje." << endl;
                return -1;
            }
        }

        // Tworzenie lokalnej kopii książki z automatycznie ustawionym stanem "dostępna"
        Book nowaKsiazka(kID, ksiazka.getTytul(), ksiazka.getNazwiskoAutora(), ksiazka.getRokWydania(), "dostepna");

        // Dodanie książki do mapy
        ksiazki[kID] = make_shared<Book>(nowaKsiazka);

        // Tworzymy nowy obiekt JSON dla książki
        json nowaKsiazkaJson;
        nowaKsiazkaJson["id"] = nowaKsiazka.getID();
        nowaKsiazkaJson["tytul"] = nowaKsiazka.getTytul();
        nowaKsiazkaJson["autor"] = nowaKsiazka.getNazwiskoAutora();
        nowaKsiazkaJson["rok"] = nowaKsiazka.getRokWydania();
        nowaKsiazkaJson["status"] = nowaKsiazka.getStan();

        // Dodajemy nową książkę do tablicy JSON
        ksiazkiJson.push_back(nowaKsiazkaJson);

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << ksiazkiJson << endl;
            plikZapis.close();
            return kID;
        }
        else {
            cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return -3;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
        return -4;
    }
}

// Funkcja usuwająca książkę z bazy na podstawie ID
int BookDatabase::aktualizujStanUsun(const Book& ksiazka) {
    int kID = ksiazka.getID();

    // Otwieramy plik JSON
    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    try {
        json ksiazkiJson;
        plikOdczyt >> ksiazkiJson;
        plikOdczyt.close();

        bool found = false;
        json noweKsiazkiJson = json::array();

        // Tworzymy nową tablicę bez książki o podanym ID
        for (const auto& k : ksiazkiJson) {
            if (k["id"] != kID) {
                noweKsiazkiJson.push_back(k);
            } else {
                found = true;
            }
        }

        if (!found) {
            cout << "Nie znaleziono ksiazki o ID " << kID << endl;
            return -1;
        }

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << noweKsiazkiJson << endl;
            plikZapis.close();

            // Usunięcie książki z mapy
            ksiazki.erase(kID);
            return kID;
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

// Funkcja wyświetlająca listę wszystkich książek w bazie
void BookDatabase::wyswietlListeKsiazek() const {
    ifstream plik(fileName);

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.json" << endl;
        return;
    }

    try {
        json ksiazkiJson;
        plik >> ksiazkiJson;
        plik.close();

        cout << "\n--- Lista ksiazek ---" << endl;

        for (const auto& ksiazka : ksiazkiJson) {
            cout << "ID: " << ksiazka["id"]
                 << ", Tytul: " << ksiazka["tytul"]
                 << ", Autor: " << ksiazka["autor"]
                 << ", Rok: " << ksiazka["rok"]
                 << ", Stan: " << ksiazka["status"];

            // Jeśli książka ma datę zwrotu (jest wypożyczona)
            if (ksiazka.contains("dataZwrotu") && !ksiazka["dataZwrotu"].is_null()) {
                cout << ", Data zwrotu: " << ksiazka["dataZwrotu"];
            }

            cout << endl;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
    }
}

// Funkcja aktualizująca stan książki na "wypożyczona" i ustawiająca datę zwrotu
bool BookDatabase::wypozyczKsiazke(int id, const string& dataZwrotu) {
    // Otwieramy plik JSON
    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.json do odczytu!" << endl;
        return false;
    }

    try {
        json ksiazkiJson;
        plikOdczyt >> ksiazkiJson;
        plikOdczyt.close();

        bool found = false;

        // Aktualizujemy stan książki o podanym ID
        for (auto& ksiazka : ksiazkiJson) {
            if (ksiazka["id"] == id) {
                if (ksiazka["status"] == "niedostepna") {
                    cerr << "Ksiazka o ID " << id << " jest juz wypozyczona!" << endl;
                    return false;
                }

                ksiazka["status"] = "niedostepna";
                ksiazka["dataZwrotu"] = dataZwrotu;
                found = true;

                // Aktualizujemy również książkę w mapie
                if (ksiazki.find(id) != ksiazki.end()) {
                    ksiazki[id]->setStan("niedostepna");
                    ksiazki[id]->setDataZwrotu(dataZwrotu);
                }

                break;
            }
        }

        if (!found) {
            cerr << "Nie znaleziono ksiazki o ID " << id << endl;
            return false;
        }

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << ksiazkiJson << endl;
            plikZapis.close();
            return true;
        }
        else {
            cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return false;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
        return false;
    }
}

// Funkcja aktualizująca stan książki na "dostępna" i usuwająca datę zwrotu
bool BookDatabase::zwrocKsiazke(int id) {
    // Otwieramy plik JSON
    ifstream plikOdczyt(fileName);
    if (!plikOdczyt.is_open()) {
        cerr << "Nie mozna otworzyc pliku books_database.json do odczytu!" << endl;
        return false;
    }

    try {
        json ksiazkiJson;
        plikOdczyt >> ksiazkiJson;
        plikOdczyt.close();

        bool found = false;

        // Aktualizujemy stan książki o podanym ID
        for (auto& ksiazka : ksiazkiJson) {
            if (ksiazka["id"] == id) {
                if (ksiazka["status"] == "dostepna") {
                    cerr << "Ksiazka o ID " << id << " jest juz dostepna!" << endl;
                    return false;
                }

                ksiazka["status"] = "dostepna";
                if (ksiazka.contains("dataZwrotu")) {
                    ksiazka.erase("dataZwrotu");
                }
                found = true;

                // Aktualizujemy również książkę w mapie
                if (ksiazki.find(id) != ksiazki.end()) {
                    ksiazki[id]->setStan("dostepna");
                    ksiazki[id]->setDataZwrotu("");
                }

                break;
            }
        }

        if (!found) {
            cerr << "Nie znaleziono ksiazki o ID " << id << endl;
            return false;
        }

        // Zapisujemy zaktualizowaną tablicę do pliku
        ofstream plikZapis(fileName);
        if (plikZapis.is_open()) {
            plikZapis << setw(2) << ksiazkiJson << endl;
            plikZapis.close();
            return true;
        }
        else {
            cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return false;
        }
    }
    catch (json::exception& e) {
        cerr << "Blad parsowania pliku JSON: " << e.what() << endl;
        return false;
    }
}