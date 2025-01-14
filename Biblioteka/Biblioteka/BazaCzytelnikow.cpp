#include "BazaCzytelnikow.h"

BazaCzytelnikow::BazaCzytelnikow() {}

bool BazaCzytelnikow::walidujPesel(const string& pesel) {
    if (pesel.length() != 11) {
        cerr << "Nieprawidlowy PESEL: " << pesel << ". PESEL powinien miec 11 cyfr." << endl;
        return false;
    }

    if (!std::all_of(pesel.begin(), pesel.end(), ::isdigit)) {
        cerr << "PESEL musi zawierac tylko cyfry!" << endl;
        return false;
    }

    return true;
}

//funkcja tworzy nowe konto czytelnika i zapisuje je w pliku
int BazaCzytelnikow::tworzenieKonta(const KontoCzytelnika& czytelnik) {
    string peselStr = czytelnik.getPesel();

    if (!walidujPesel(peselStr)) {
        return -1;
    }

    ifstream input_file("baza_czytelnikow.txt");

    if (!input_file.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    vector<string> lines;
    string line;

    while (getline(input_file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id == peselStr) {
            cerr << "Czytelnik o Peselu " << peselStr << " juz istnieje." << endl;
            input_file.close();
            return -1;
        }

        lines.push_back(line);
    }

    input_file.close();

    // Dodanie nowego czytelnika do kolekcji w pamiêci
    int id = czytelnicy.size() + 1;
    czytelnicy[id] = make_shared<KontoCzytelnika>(czytelnik);

    // Dodanie nowego czytelnika do listy w celu zapisania do pliku
    string new_record = peselStr + "," + czytelnik.getImie() + "," +
        czytelnik.getNazwisko() + "," + to_string(czytelnik.getKaucja()) +
        "," + to_string(czytelnik.getIloscKsiazek());
    lines.push_back(new_record);

    ofstream output_file("baza_czytelnikow.txt");
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    for (const auto& l : lines) {
        output_file << l << endl;
    }

    output_file.close();

    cout << "Konto czytelnika o Peselu " << peselStr << " zostalo pomyslnie utworzone." << endl;
    return 1;
}


int BazaCzytelnikow::usuniecieKonta(const KontoCzytelnika& czytelnik) {
    string peselStr = czytelnik.getPesel();

    if (!walidujPesel(peselStr)) {
        return -1;
    }


    ifstream input_file("baza_czytelnikow.txt");

    if (!input_file.is_open()) {
        cerr << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool found = false;

    //przeszukiwanie pliku w celu znalezienia czytelnika o podanym PESELu
    while (getline(input_file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id != peselStr) {
            lines.push_back(line); //dodanie linijki do wektora, jeœli nie dotyczy usuwanego czytelnika
        }
        else {
            found = true; //czytelnik znaleziony
        }
    }

    input_file.close();

    if (!found) {
        cout << "Nie znaleziono czytelnika o Peselu " << peselStr << endl;
        return -1;
    }

    //zapisanie zaktualizowanego pliku bez danych usuniêtego czytelnika
    ofstream output_file("baza_czytelnikow.txt");
    if (!output_file.is_open()) {
        cerr << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }
    for (const auto& l : lines) {
        output_file << l << endl;
    }
    output_file.close();

    cout << "Konto czytelnika o Peselu " << peselStr << " zostalo pomyslnie usuniete." << endl;
    return 1;
}

//funkcja wyœwietlaj¹ca wszystkich czytelników zapisanych w pliku
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
        //wyœwietlenie listy wypo¿yczonych ksi¹¿ek, jeœli istniej¹
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

//funkcja przypisuj¹ca wypo¿yczenie ksi¹¿ki do danego czytelnika
int BazaCzytelnikow::podepnijWypozyczenie(const KontoCzytelnika& czytelnik, int egzemplarzID) {
    ifstream plik("baza_czytelnikow.txt");
    vector<string> lines;
    string line;
    bool found = false;

    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return -1;
    }
    //przeszukanie pliku w celu znalezienia czytelnika i aktualizacji jego danych
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
            currentCount += 1;
            //dodanie ID ksi¹¿ki do listy wypo¿yczeñ
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
    //zapisz zaktualizowanych danych do pliku
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


//funkcja usuwaj¹ca wypo¿yczenie ksi¹¿ki przypisanej do danego czytelnika
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
    //przeszukiwanie pliku w celu znalezienia czytelnika i aktualizacji danych
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
                currentCount = stoi(iloscKsiazek); //konwersja string na int
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
                //aktualizacja linii z danymi czytelnika
                line = pesel + "," + imie + "," + nazwisko + "," + kaucja + "," + to_string(currentCount) + "," + egzemplarze;
                found = true;
                bookReturned = true;
            }
            else {
                cerr << "Nie znaleziono egzemplarza o ID " << egzemplarzID << " w wypozyczeniach." << endl;
            }
        }

        lines.push_back(line);
    }

    plik.close();

    if (!found) {
        cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
        return -1;
    }
    //zapis zaktualizowanych danych, jeœli ksi¹¿ka zosta³a zwrócona
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

//funkcja sprawdzaj¹ca, czy czytelnik mo¿e wypo¿yczyæ kolejn¹ ksi¹¿kê
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

            if (currentCount >= 5) { //sprawdzenie limitu wypo¿yczeñ
                cerr << "Czytelnik o PESEL " << pesel << " nie moze wypozyczyc wiecej ksiazek (limit 5)." << endl;
                return false;
            }

            return true;
        }
    }

    cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
    return false;
}

//funkcja wyœwietlaj¹ca dane konta
void BazaCzytelnikow::sprawdzenieKonta(const KontoCzytelnika& czytelnik) {
    ifstream plik("baza_czytelnikow.txt");
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku baza_czytelnikow.txt" << endl;
        return;
    }

    string linia;
    bool found = false;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string pesel, imie, nazwisko, kaucja, iloscKsiazek, wypozyczoneKsiazki;
        getline(ss, pesel, ',');
        getline(ss, imie, ',');
        getline(ss, nazwisko, ',');
        getline(ss, kaucja, ',');
        getline(ss, iloscKsiazek, ',');

        if (pesel == czytelnik.getPesel()) {
            
            found = true;
            cout << "\n--- Dane czytelnika ---" << endl;
            cout << "Pesel: " << pesel << endl;
            cout << "Imie: " << imie << endl;
            cout << "Nazwisko: " << nazwisko << endl;
            cout << "Kaucja: " << kaucja << " zl" << endl;
            cout << "Liczba wypozyczonych ksiazek: " << iloscKsiazek << endl;

            if (getline(ss, wypozyczoneKsiazki)) {
                cout << "Wypozyczone ksiazki (ID): " << wypozyczoneKsiazki << endl;
            }
            else {
                cout << "Brak wypozyczonych ksiazek." << endl;
            }
            break;
        }
    }

    plik.close();

    if (!found) {
        cerr << "Nie znaleziono czytelnika o PESEL " << czytelnik.getPesel() << endl;
    }
}

//funkcja naliczaj¹ca kaucje czytelnikowi
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


//funkcja usuwaj¹ca naliczon¹ kaucjê czytelnikowi
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
            kaucja = "0.0"; //resetowanie kaucji

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



