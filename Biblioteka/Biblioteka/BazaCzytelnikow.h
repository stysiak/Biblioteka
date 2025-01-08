#pragma once
#include "KontoCzytelnika.h"
#include "header.h"

class BazaCzytelnikow {
private:
    unordered_map<int, shared_ptr<KontoCzytelnika>> czytelnicy;
public:
    BazaCzytelnikow();

    int tworzenieKonta(const KontoCzytelnika& kontoCzytelnika);
    int usuniecieKonta(const KontoCzytelnika& kontoCzytelnika);
    void wyswietlListeCzytelnikow() const;
    void sprawdzenieKonta(const KontoCzytelnika& czytelnik);
};
