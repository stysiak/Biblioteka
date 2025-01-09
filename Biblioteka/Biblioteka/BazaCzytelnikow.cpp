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
            getline(ss, fileID, ',');

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
        outPlik << peselStr << "," << czytelnik.getImie() << "," << czytelnik.getNazwisko() << "," << czytelnik.getKaucja() << "," << czytelnik.getIloscKsiazek() << "," << czytelnik.getPrzekroczonoLimit() << endl;
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
        getline(ss, id, ',');

        if (id != kID) {
            lines.push_back(line);
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
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, przekroczenieLimitu;
        vector<string> wypozyczoneKsiazki;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, przekroczenieLimitu, ',');

        string ksiazkaID;
        while (getline(ss, ksiazkaID, ',')) {
            wypozyczoneKsiazki.push_back(ksiazkaID);
        }

        cout << "Pesel: " << pesel
            << ", Imie: " << imie
            << ", Nazwisko: " << nazwisko
            << ", Kaucja: " << kaucja
            << ", Ilosc wypozyczonych ksiazek: " << iloscKsiazek
            << ", Przekroczenie limitu: " << przekroczenieLimitu;

        if (!wypozyczoneKsiazki.empty()) {
            cout << ", Wypozyczone ksiazki (ID): ";
            for (const auto& id : wypozyczoneKsiazki) {
                cout << id << ", ";
            }
        }
        cout << endl;
    }

    plik.close();
}


int BazaCzytelnikow::podepnijWypozyczenie(const KontoCzytelnika& czytelnik, int egzemplarzID) {
    ifstream plik("baza_czytelnikow.txt");
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, limit;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, limit);

        if (pesel == czytelnik.getPesel()) {
            int currentCount = stoi(iloscKsiazek);
            currentCount += 1;
            line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + to_string(currentCount) + "," + limit + "," + to_string(egzemplarzID);
            found = true;
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
        return -1;
    }

    ofstream outPlik("baza_czytelnikow.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Ksiazka o ID " << egzemplarzID << " zostala przypisana do czytelnika." << endl;
    return egzemplarzID;
}

int BazaCzytelnikow::usunWypozyczenie(const KontoCzytelnika& czytelnik, int egzemplarzID) {
    ifstream plik("baza_czytelnikow.txt");
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, limit;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, limit, ',');

        if (pesel == czytelnik.getPesel()) {
            int currentCount = stoi(iloscKsiazek);
            currentCount = max(0, currentCount - 1);

            stringstream idStream(line.substr(line.find(limit) + limit.length() + 1));
            vector<string> ids;
            string id;

            while (getline(idStream, id, ',')) {
                if (stoi(id) != egzemplarzID) {
                    ids.push_back(id);
                }
            }

            stringstream updatedLine;
            updatedLine << pesel << "," << imie << "," << nazwisko << "," << kaucja << ","
                << currentCount << "," << limit;

            for (const auto& remainingId : ids) {
                updatedLine << "," << remainingId;
            }

            line = updatedLine.str();
            found = true;
        }

        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
        return -1;
    }

    // Zapis zaktualizowanych wierszy do pliku
    ofstream outPlik("baza_czytelnikow.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Ksiazka o ID " << egzemplarzID << " zostala usunieta z konta czytelnika." << endl;
    return egzemplarzID;
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

