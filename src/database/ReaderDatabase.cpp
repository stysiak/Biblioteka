#include "../../include/database/ReaderDatabase.h"

string ReaderDatabase::fileName = "../../data/readers_database.json";

ReaderDatabase::ReaderDatabase() {}

bool ReaderDatabase::walidujPesel(const string& pesel) {
    if (pesel.length() != 11 || !std::all_of(pesel.begin(), pesel.end(), ::isdigit)) {
        cerr << "Nieprawidlowy PESEL: " << pesel << endl;
        return false;
    }
    return true;
}

json ReaderDatabase::wczytajBaze() const {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Blad otwarcia pliku JSON!" << endl;
        return {};
    }
    json j;
    file >> j;
    return j;
}

void ReaderDatabase::zapiszBaze(const json& j) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Blad zapisu pliku JSON!" << endl;
        return;
    }
    file << j.dump(4);
}

int ReaderDatabase::tworzenieKonta(const ReaderAccount& czytelnik) {
    string pesel = czytelnik.getPesel();
    if (!walidujPesel(pesel)) return -1;

    json baza = wczytajBaze();
    if (baza.contains(pesel)) {
        cerr << "Czytelnik o Peselu " << pesel << " juz istnieje." << endl;
        return -1;
    }

    baza[pesel] = {
        {"imie", czytelnik.getImie()},
        {"nazwisko", czytelnik.getNazwisko()},
        {"kaucja", czytelnik.getKaucja()},
        {"iloscKsiazek", czytelnik.getIloscKsiazek()},
        {"wypozyczone", json::array()}
    };

    zapiszBaze(baza);
    cout << "Konto czytelnika o PESEL " << pesel << " zostalo utworzone." << endl;
    return 1;
}

int ReaderDatabase::usuniecieKonta(const ReaderAccount& czytelnik) {
    string pesel = czytelnik.getPesel();
    if (!walidujPesel(pesel)) return -1;

    json baza = wczytajBaze();
    if (!baza.contains(pesel)) {
        cerr << "Nie znaleziono czytelnika." << endl;
        return -1;
    }

    baza.erase(pesel);
    zapiszBaze(baza);
    cout << "Konto usuniete." << endl;
    return 1;
}

void ReaderDatabase::wyswietlListeCzytelnikow() const {
    json baza = wczytajBaze();
    for (auto& [pesel, dane] : baza.items()) {
        cout << "PESEL: " << pesel
             << ", Imie: " << dane["imie"]
             << ", Nazwisko: " << dane["nazwisko"]
             << ", Kaucja: " << dane["kaucja"]
             << ", Ilosc ksiazek: " << dane["iloscKsiazek"];

        if (!dane["wypozyczone"].empty()) {
            cout << ", Wypozyczone: ";
            for (const auto& id : dane["wypozyczone"]) cout << id << ", ";
        }
        cout << endl;
    }
}

int ReaderDatabase::podepnijWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID) {
    json baza = wczytajBaze();
    string pesel = czytelnik.getPesel();

    if (!baza.contains(pesel)) return -1;

    auto& dane = baza[pesel];
    dane["iloscKsiazek"] = int(dane["iloscKsiazek"]) + 1;
    dane["wypozyczone"].push_back(egzemplarzID);

    zapiszBaze(baza);
    return egzemplarzID;
}

int ReaderDatabase::usunWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID) {
    json baza = wczytajBaze();
    string pesel = czytelnik.getPesel();
    if (!baza.contains(pesel)) return -1;

    auto& dane = baza[pesel];
    auto& wyp = dane["wypozyczone"];

    auto it = std::find(wyp.begin(), wyp.end(), egzemplarzID);
    if (it != wyp.end()) {
        wyp.erase(it);
        dane["iloscKsiazek"] = int(dane["iloscKsiazek"]) - 1;
        zapiszBaze(baza);
        return egzemplarzID;
    }

    return -1;
}

bool ReaderDatabase::czyMoznaWypozyczyc(const ReaderAccount& czytelnik) {
    json baza = wczytajBaze();
    string pesel = czytelnik.getPesel();
    if (!baza.contains(pesel)) return false;

    return int(baza[pesel]["iloscKsiazek"]) < 5;
}

void ReaderDatabase::sprawdzenieKonta(const ReaderAccount& czytelnik) {
    json baza = wczytajBaze();
    string pesel = czytelnik.getPesel();

    if (!baza.contains(pesel)) {
        cerr << "Nie znaleziono czytelnika." << endl;
        return;
    }

    auto& d = baza[pesel];
    cout << "\n--- Dane czytelnika ---" << endl;
    cout << "Pesel: " << pesel << endl;
    cout << "Imie: " << d["imie"] << endl;
    cout << "Nazwisko: " << d["nazwisko"] << endl;
    cout << "Kaucja: " << d["kaucja"] << endl;
    cout << "Liczba ksiazek: " << d["iloscKsiazek"] << endl;
    cout << "Wypozyczone: ";
    for (const auto& id : d["wypozyczone"]) cout << id << ", ";
    cout << endl;
}

int ReaderDatabase::naliczKaucje(ReaderAccount& czytelnik, float kaucja) {
    json baza = wczytajBaze();
    string pesel = czytelnik.getPesel();
    if (!baza.contains(pesel)) return -1;

    baza[pesel]["kaucja"] = kaucja;
    zapiszBaze(baza);
    return 1;
}

int ReaderDatabase::usunKaucje(ReaderAccount& czytelnik) {
    return naliczKaucje(czytelnik, 0);
}
