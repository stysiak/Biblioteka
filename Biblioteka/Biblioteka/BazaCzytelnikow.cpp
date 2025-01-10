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
        outPlik << peselStr << "," << czytelnik.getImie() << "," << czytelnik.getNazwisko() << "," << czytelnik.getKaucja() << "," << czytelnik.getIloscKsiazek() << endl;
        outPlik.close();
        cout << "Konto czytelnika o Peselu " << peselStr << " zostalo pomyœlnie utworzone." << endl;
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

    cout << "Konto czytelnika o Peselu " << kID << " zosta³o pomyœlnie usuniête." << endl;
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
        string pesel, imie, nazwisko, kaucja, iloscKsiazek;
        vector<string> wypozyczoneKsiazki;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');

        string ksiazkaID;
        while (getline(ss, ksiazkaID, ',')) {
            wypozyczoneKsiazki.push_back(ksiazkaID);
        }

        cout << "Pesel: " << pesel
            << ", Imie: " << imie
            << ", Nazwisko: " << nazwisko
            << ", Kaucja: " << kaucja
            << ", Ilosc wypozyczonych ksiazek: " << iloscKsiazek;

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

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, egzemplarze;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, egzemplarze);

        if (pesel == czytelnik.getPesel()) {
            int currentCount;
            try {
                currentCount = stoi(iloscKsiazek);
            }
            catch (const invalid_argument& e) {
                cerr << "B³ad konwersji liczby ksiazek: " << iloscKsiazek << endl;
                return -1;
            }
            currentCount += 1;

            if (egzemplarze.empty()) {
                egzemplarze = to_string(egzemplarzID);
            }
            else {
                egzemplarze += "," + to_string(egzemplarzID);
            }

            line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + to_string(currentCount) + "," + egzemplarze;
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
    if (!outPlik.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }

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
    bool bookReturned = false;

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, egzemplarze;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, egzemplarze); 

        if (pesel == czytelnik.getPesel()) {
            int currentCount;
            try {
                currentCount = stoi(iloscKsiazek);
            }
            catch (const invalid_argument& e) {
                cerr << "Blad konwersji liczby ksiazek: " << iloscKsiazek << endl;
                return -1;
            }

            // Sprawdzenie, czy egzemplarzID znajduje siê w liœcie egzemplarzy
            size_t pos = egzemplarze.find(to_string(egzemplarzID));
            if (pos != string::npos) {
                size_t nextPos = egzemplarze.find(",", pos);
                if (nextPos != string::npos) {
                    // Jeœli to nie ostatni element, usuwamy go razem z przecinkiem
                    egzemplarze.erase(pos, nextPos - pos + 1);
                }
                else {
                    // Jeœli to ostatni element w liœcie, usuwamy tylko numer
                    egzemplarze.erase(pos);
                }

                currentCount -= 1;

                line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + to_string(currentCount) + "," + egzemplarze;
                found = true;
                bookReturned = true;
            }
            else {
                cerr << "Nie znaleziono egzemplarza o ID " << egzemplarzID << " w wypo¿yczeniach." << endl;
            }
        }

        lines.push_back(line);
    }

    plik.close();

    if (!found) {
        cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
        return -1;
    }

    if (bookReturned) {
        ofstream outPlik("baza_czytelnikow.txt");
        if (!outPlik.is_open()) {
            cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return -1;
        }

        for (const auto& l : lines) {
            outPlik << l << endl;
        }

        outPlik.close();

        cout << "Ksiazka o ID " << egzemplarzID << " zostala zwrocona." << endl;
        return egzemplarzID;
    }

    return -1;  // Jeœli nie uda³o siê zwróciæ ksi¹¿ki
}

bool BazaCzytelnikow::czyMoznaWypozyczyc(const KontoCzytelnika& czytelnik) {
    ifstream plik("baza_czytelnikow.txt");
    string linia;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek;

        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');

        if (pesel == czytelnik.getPesel()) {
            int currentCount = stoi(iloscKsiazek);

            if (currentCount >= 5) {
                cerr << "Czytelnik o PESEL " << pesel << " nie moze wypozyczyc wiecej ksiazek (limit 5)." << endl;
                return false;
            }

            return true;
        }
    }

    cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
    return false;
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

int BazaCzytelnikow::naliczKaucje(KontoCzytelnika& czytelnik, float kaucja) {
    ifstream plik("baza_czytelnikow.txt");
    vector<string> lines;
    string line;
    bool found = false;

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucjaStr, iloscKsiazek, egzemplarze;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucjaStr, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, egzemplarze);

        if (pesel == czytelnik.getPesel()) {
            kaucjaStr = to_string(kaucja);

            line = pesel + "," + imie + "," + nazwisko + "," + kaucjaStr + "," + iloscKsiazek + "," + egzemplarze;
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
    if (!outPlik.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        outPlik << l << endl;
    }

    outPlik.close();

    cout << "Naliczono kaucje w wysokosci " << kaucja << " zl dla czytelnika o PESEL " << czytelnik.getPesel() << "." << endl;

    return 1;
}



int BazaCzytelnikow::usunKaucje(KontoCzytelnika& czytelnik) {
    ifstream plik("baza_czytelnikow.txt");
    vector<string> lines;
    string line;
    bool found = false;

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }

    while (getline(plik, line)) {
        stringstream ss(line);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, egzemplarze;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');
        getline(ss, egzemplarze);

        if (pesel == czytelnik.getPesel()) {
            kaucja = "0.0";

            line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + iloscKsiazek + "," + egzemplarze;
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
    if (!outPlik.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        outPlik << l << endl;
    }

    outPlik.close();

    cout << "Kaucja dla czytelnika o PESEL " << czytelnik.getPesel() << " zostala usunieta." << endl;

    return 1;
}



