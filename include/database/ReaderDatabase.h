#pragma once

#include "../models/ReaderAccount.h"
#include "../../header.h"

class ReaderDatabase {
private:
    std::unordered_map<int, std::shared_ptr<ReaderAccount>> czytelnicy;

public:
    static std::string fileName;

    ReaderDatabase();

    bool walidujPesel(const std::string& pesel);

    nlohmann::json wczytajBaze() const;


    void zapiszBaze(const nlohmann::json &j);

    int tworzenieKonta(const ReaderAccount& kontoCzytelnika);
    int usuniecieKonta(const ReaderAccount& kontoCzytelnika);

    void wyswietlListeCzytelnikow() const;
    void sprawdzenieKonta(const ReaderAccount& czytelnik);

    int podepnijWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID);
    int usunWypozyczenie(const ReaderAccount& czytelnik, int egzemplarzID);

    bool czyMoznaWypozyczyc(const ReaderAccount& czytelnik);

    int naliczKaucje(ReaderAccount& czytelnik, float kaucja);
    int usunKaucje(ReaderAccount& czytelnik);
    void zapiszBaze(const std::string& sciezkaPliku) const;

};
