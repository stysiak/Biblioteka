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

    int id = czytelnicy.size() + 1;  // Generowanie ID na podstawie wielko�ci mapy
    czytelnicy[id] = make_shared<KontoCzytelnika>(czytelnik);

    ofstream outPlik("baza_czytelnikow.txt", ios::app);
    if (outPlik.is_open()) {
        outPlik << peselStr << "," << czytelnik.getImie() << "," << czytelnik.getNazwisko() << "," << czytelnik.getKaucja() << "," << czytelnik.getIloscKsiazek() << endl;
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
        getline(ss, egzemplarze);  // Teraz ta linia przechowuje egzemplarze ksi��ek

        if (pesel == czytelnik.getPesel()) {
            // Zaktualizuj liczb� ksi��ek
            int currentCount;
            try {
                currentCount = stoi(iloscKsiazek);
            }
            catch (const invalid_argument& e) {
                cerr << "B��d konwersji liczby ksi��ek: " << iloscKsiazek << endl;
                return -1;
            }
            currentCount += 1;

            // Zaktualizuj list� egzemplarzy, dodaj�c nowy egzemplarzID
            if (egzemplarze.empty()) {
                egzemplarze = to_string(egzemplarzID);
            }
            else {
                egzemplarze += "," + to_string(egzemplarzID);
            }

            // Stw�rz now� lini� zaktualizowan�
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

    // Zapisz zmienione dane z powrotem do pliku
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
        getline(ss, egzemplarze);  // Lista egzemplarzy

        if (pesel == czytelnik.getPesel()) {
            // Zaktualizuj liczb� ksi��ek
            int currentCount;
            try {
                currentCount = stoi(iloscKsiazek);
            }
            catch (const invalid_argument& e) {
                cerr << "B��d konwersji liczby ksi��ek: " << iloscKsiazek << endl;
                return -1;
            }

            // Sprawdzenie, czy egzemplarzID znajduje si� w li�cie egzemplarzy
            size_t pos = egzemplarze.find(to_string(egzemplarzID));
            if (pos != string::npos) {
                // Usu� egzemplarzID z listy
                size_t nextPos = egzemplarze.find(",", pos);
                if (nextPos != string::npos) {
                    // Je�li to nie ostatni element, usuwamy go razem z przecinkiem
                    egzemplarze.erase(pos, nextPos - pos + 1);
                }
                else {
                    // Je�li to ostatni element w li�cie, usuwamy tylko numer
                    egzemplarze.erase(pos);
                }

                // Zaktualizuj liczb� ksi��ek
                currentCount -= 1;

                // Stw�rz now� lini�
                line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + to_string(currentCount) + "," + egzemplarze;
                found = true;
                bookReturned = true;
            }
            else {
                cerr << "Nie znaleziono egzemplarza o ID " << egzemplarzID << " w wypo�yczeniach." << endl;
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
        // Zapisz zmienione dane z powrotem do pliku
        ofstream outPlik("baza_czytelnikow.txt");
        if (!outPlik.is_open()) {
            cerr << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return -1;
        }

        for (const auto& l : lines) {
            outPlik << l << endl;
        }

        outPlik.close();

        cout << "Ksiazka o ID " << egzemplarzID << " zostala zwr�cona." << endl;
        return egzemplarzID;
    }

    return -1;  // Je�li nie uda�o si� zwr�ci� ksi��ki
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

