#include "../../include/utils/Return.h"


string Return::fileName = "../../data/books_database.json";

float Return::zwrocKsiazke(const Book& ksiazka) {
    float kaucja = 0.0f;
    time_t now = time(0);
    tm localTime = {};
    localtime_s(&localTime, &now);
    ostringstream oss;
    oss << put_time(&localTime, "%Y-%m-%d");
    string currentDate = oss.str();

    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Nie mozna otworzyc pliku JSON!" << endl;
        return -1.0f;
    }

    json books;
    inFile >> books;
    inFile.close();

    bool found = false;

    for (auto& book : books) {
        if (book["id"] == ksiazka.getID() && book["status"] == "niedostepna") {
            found = true;

            // Sprawdź, czy istnieje data zwrotu
            if (book.contains("data_zwrotu")) {
                string dataZwrotuStr = book["data_zwrotu"];

                tm dataZwrotu = {};
                istringstream ss(dataZwrotuStr);
                ss >> get_time(&dataZwrotu, "%Y-%m-%d");
                if (ss.fail()) {
                    cerr << "Blad konwersji daty!" << endl;
                    return -1.0f;
                }

                time_t tDataZwrotu = mktime(&dataZwrotu);
                double secondsLate = difftime(now, tDataZwrotu);
                int lateDays = secondsLate / (60 * 60 * 24);
                if (lateDays > 0) {
                    kaucja = lateDays * 2.0f;
                }
            }

            // Aktualizuj status i usuń datę zwrotu
            book["status"] = "dostepna";
            book.erase("data_zwrotu");
            break;
        }
    }

    if (!found) {
        cerr << "Blad zwrotu! Egzemplarz o ID " << ksiazka.getID() << " nie byl wypozyczony." << endl;
        return -1.0f;
    }

    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Nie mozna zapisac pliku JSON!" << endl;
        return -1.0f;
    }

    outFile << setw(4) << books << endl;
    outFile.close();

    // Informacja końcowa
    if (kaucja > 0.0f) {
        cout << "Book zwrocona po terminie. Naliczenie kaucji: " << kaucja << " zl." << endl;
    } else {
        cout << "Book o ID " << ksiazka.getID() << " zostala zwrocona w terminie." << endl;
    }

    return kaucja;
}
