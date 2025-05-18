#include "../../include/utils/Borrowing.h"

string Borrowing::fileName = "../../data/books_database.json";

int Borrowing::wypozyczKsiazke(const Book& ksiazka) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Nie mozna otworzyc pliku JSON!" << endl;
        return -1;
    }

    json books;
    inFile >> books;
    inFile.close();

    bool found = false;
    time_t now = time(0);
    tm ltm = {};
    localtime_s(&ltm, &now);
    ltm.tm_mday += 30;  // Dodajemy 30 dni
    mktime(&ltm);
    ostringstream oss;
    oss << put_time(&ltm, "%Y-%m-%d");
    string dataZwrotu = oss.str();

    for (auto& book : books) {
        if (book["id"] == ksiazka.getID() && book["status"] == "dostepna") {
            book["status"] = "niedostepna";
            book["data_zwrotu"] = dataZwrotu;
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Book o ID " << ksiazka.getID() << " jest niedostepna lub nie istnieje!" << endl;
        return -1;
    }

    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Nie mozna zapisac pliku JSON!" << endl;
        return -1;
    }
    outFile << setw(4) << books << endl;
    outFile.close();

    cout << "Book o ID " << ksiazka.getID() << " zostala wypozyczona. Data zwrotu: " << dataZwrotu << endl;
    return ksiazka.getID();
}
