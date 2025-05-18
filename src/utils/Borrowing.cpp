#include "../../include/utils/Borrowing.h"

string Borrowing::fileName = "../../data/books_database.txt";
// Zaktualizowana funkcja wypo�yczaj�ca ksi��k�
int Borrowing::wypozyczKsiazke(const Book& ksiazka) {
    ifstream plik(fileName);
    vector<string> lines;
    string line;
    bool found = false;

    time_t now = time(0);
    tm ltm = {};
    localtime_s(&ltm, &now);
    ltm.tm_mday += 30;  // Dodajemy 30 dni do bie��cej daty
    mktime(&ltm);
    ostringstream oss;
    oss << put_time(&ltm, "%Y-%m-%d");
    string dataZwrotu = oss.str();

    while (getline(plik, line)) {
        stringstream ss(line);
        string id, tytul, autor, rok, stan, dataZwrotuFile;
        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');
        getline(ss, stan, ',');
        getline(ss, dataZwrotuFile, ',');

        if (stoi(id) == ksiazka.getID() && stan == "dostepna") {
            line = id + "," + tytul + "," + autor + "," + rok + ",niedostepna," + dataZwrotu;
            found = true;
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Book o ID " << ksiazka.getID() << " jest niedostepna lub nie istnieje!" << endl;
        return -1;
    }

    ofstream outPlik(fileName);
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    cout << "Book o ID " << ksiazka.getID() << " zostala wypozyczona. Data zwrotu: " << dataZwrotu << endl;
    return ksiazka.getID();
}