#include "BazaCzytelnikow.h"
#include "header.h"

using namespace std;

void BazaCzytelnikow::tworzenieKonta(KontoCzytelnika czytelnik) {
    if (!sprawdzenieKonta(czytelnik)) {
        ofstream plik("BazaCzytelnikow.txt", ios::app);
        plik << czytelnik.imie << " " << czytelnik.nazwisko << " " << czytelnik.pesel << " " << czytelnik.kaucja << " " << czytelnik.iloscKsiazek << " " << czytelnik.przekroczonoLimit << endl;
        plik.close();
        cout << "Utworzono konto czytelnika\n";
    }
    else {
        cout << "Konto czytelnika juz istnieje\n";
    }
}

void BazaCzytelnikow::usuniecieKonta(KontoCzytelnika czytelnik) {
    ifstream plikIn("BazaCzytelnikow.txt");
    ofstream plikOut("temp.txt");
    string linia;
    bool usunieto = false;

    while (getline(plikIn, linia)) {
        stringstream ss(linia);
        string imie, nazwisko;
        int pesel, iloscKsiazek;
        float kaucja;
        bool przekroczonoLimit;

        ss >> imie >> nazwisko >> pesel >> kaucja >> iloscKsiazek >> przekroczonoLimit;

        if (pesel != czytelnik.pesel) {
            plikOut << linia << endl;
        }
        else {
            usunieto = true;
        }
    }

    plikIn.close();
    plikOut.close();
    remove("BazaCzytelnikow.txt");
    rename("temp.txt", "BazaCzytelnikow.txt");

    if (usunieto) {
        cout << "Usunieto konto czytelnika\n";
    }
    else {
        cout << "Nie ma takiego konta\n";
    }
}

bool BazaCzytelnikow::sprawdzenieKonta(KontoCzytelnika czytelnik) {
    ifstream plik("BazaCzytelnikow.txt");
    string linia;

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string imie, nazwisko;
        int pesel, iloscKsiazek;
        float kaucja;
        bool przekroczonoLimit;

        ss >> imie >> nazwisko >> pesel >> kaucja >> iloscKsiazek >> przekroczonoLimit;

        if (pesel == czytelnik.pesel) {
            return true;
        }
    }

    return false;
}
