#include "BazaCzytelnikow.h"
#include "header.h"

using namespace std;

BazaCzytelnikow::BazaCzytelnikow() {}

int BazaCzytelnikow::tworzenieKonta(const KontoCzytelnika& czytelnik) {
    string peselStr = czytelnik.getPesel();
    if (peselStr.length() != 11) {
        cerr << "Nieprawidlowy PESEL: " << peselStr << ". PESEL powinien miec 11 cyfr." << endl;
        return -1;
    }

    ifstream plik("baza_czytelnikow.txt");
    string linia;

    if (plik.is_open()) {
        while (getline(plik, linia)) {
            string fileID;
            stringstream ss(linia);
            getline(ss, fileID, ',');  // Wczytaj PESEL do fileID

            if (fileID == peselStr) {
                cerr << "Czytelnik o Peselu " << peselStr << " juz istnieje." << endl;
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

    int id = czytelnicy.size() + 1;  // Generowanie ID na podstawie wielkoœci mapy
    czytelnicy[id] = make_shared<KontoCzytelnika>(czytelnik);

    ofstream outPlik("baza_czytelnikow.txt", ios::app);
    if (outPlik.is_open()) {
        outPlik << peselStr << ", " << czytelnik.getImie() << ", " << czytelnik.getNazwisko() << endl;
        outPlik.close();
    }
    else {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }
    return 1;
}

int BazaCzytelnikow::usuniecieKonta(const KontoCzytelnika& czytelnik) {
    string kID = czytelnik.getPesel();
    ifstream input_file("baza_czytelnikow.txt");

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
        getline(ss, id, ',');  // Odczytaj PESEL z pliku

        if (id != kID) {
            lines.push_back(line);  // Zapisz wszystkie linie z wyj¹tkiem tej z usuwanym PESEL
        }
        else {
            found = true;
        }
    }

    input_file.close();

    if (!found) {
        cout << "Nie znaleziono czytelnika o Peselu " << kID << endl;
        return -1;
    }

    ofstream output_file("baza_czytelnikow.txt");
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

void BazaCzytelnikow::wyswietlListeCzytelnikow() const {
    ifstream plik("baza_czytelnikow.txt");

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_czytelnikow.txt" << endl;
        return;
    }

    string linia;
    cout << "\n--- Lista czytelnikow ---" << endl;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string pesel, imie, nazwisko;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');

        cout << "Pesel: " << pesel
            << ", Imie: " << imie
            << ", Nazwiwsko: " << nazwisko << endl;
    }

    plik.close();
}

//bool BazaCzytelnikow::sprawdzenieKonta(const KontoCzytelnika& czytelnik) {
//    ifstream plik("baza_czytelnikow.txt");
//    string linia;
//
//    while (getline(plik, linia)) {
//        stringstream ss(linia);
//        string imie, nazwisko, pesel;
//
//        getline(ss, pesel, ',');
//        getline(ss, imie, ',');
//        getline(ss, nazwisko, ',');
//
//        if (pesel == czytelnik.getPesel()) {
//            return true;
//        }
//    }
//
//    return false;
//}

