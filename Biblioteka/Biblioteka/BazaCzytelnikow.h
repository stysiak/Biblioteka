#pragma once
#include "KontoCzytelnika.h"
#include "header.h"

using namespace std; 

class BazaCzytelnikow {
private:
    vector<KontoCzytelnika> listaCzytelnikow;
public:
    BazaCzytelnikow();
    void tworzenieKonta(KontoCzytelnika czytelnik);
    void usuniecieKonta(KontoCzytelnika czytelnik);
    bool sprawdzenieKonta(KontoCzytelnika czytelnik);
};
