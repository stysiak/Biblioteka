#pragma once
#include "../models/ReaderAccount.h"
#include "../../header.h"

class ReaderDatabase {
private:
    unordered_map<int, shared_ptr<ReaderAccount>> czytelnicy;
public:
    static string fileName;

    ReaderDatabase();
    bool walidujPesel(const string& pesel);
    int tworzenieKonta(const ReaderAccount& kontoCzytelnika);
    int usuniecieKonta(const ReaderAccount& kontoCzytelnika);
    void wyswietlListeCzytelnikow() const;
    void sprawdzenieKonta(const ReaderAccount& czytelnik);
    int podepnijWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID);
    int usunWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID);
    bool czyMoznaWypozyczyc(const ReaderAccount& czytelnik);
    int naliczKaucje(ReaderAccount& czytelnik, float kaucja);
    int usunKaucje(ReaderAccount& czytelnik);
};
