#include "header.h"
#include "BazaCzytelnikow.h"
#include "BazaKsiazek.h"
#include "Data.h"
#include "Egzemplarz.h"
#include "KontoCzytelnika.h"
#include "Ksiazka.h"
#include "Pracownik.h"
#include "Wypozyczenie.h"
#include "Zwrot.h"
#include "BazaPracownikow.h"

using namespace std;

int main() {

    BazaPracownikow bazaPracownikow;
    Pracownik pracownik;  
    string login, haslo;
    int wybor;

    
    system("cls"); //czyszczenie ekranu
    cout << "=====================================" << endl;
    cout << "  WITAMY W SYSTEMIE BIBLIOTECZNYM    " << endl;
    cout << "=====================================" << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Wyjscie" << endl;
    cout << "=====================================" << endl;
    cout << "Wybierz opcje: ";
    cin >> wybor;

    switch (wybor) {
        case 1:
            if (bazaPracownikow.logowanie()) {
            }
            else {
                cout << "Błędne dane logowania. Sprobuj ponownie." << endl;
            }
            system("pause");
            break;
        case 2:
            cout << "Wyjscie z programu" << endl;
            break;
        default:
            cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
            system("pause");
            break;
    }
    return 0;
}
