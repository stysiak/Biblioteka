#pragma once
#include "KontoCzytelnika.h"
#include "header.h"

class BazaCzytelnikow {
private:
    unordered_map<int, shared_ptr<KontoCzytelnika>> czytelnicy;
public:
    BazaCzytelnikow();

    double tworzenieKonta(const KontoCzytelnika& kontoCzytelnika);
    double usuniecieKonta(const KontoCzytelnika& kontoCzytelnika);
    void wyswietlListeCzytelnikow() const;
    bool sprawdzenieKonta(const KontoCzytelnika& czytelnik);
};
