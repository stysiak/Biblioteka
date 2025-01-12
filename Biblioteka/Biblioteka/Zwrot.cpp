#include "Zwrot.h"

// Zaktualizowana funkcja zwracaj¹ca ksi¹¿kê
float Zwrot::zwrocKsiazke(const Ksiazka& ksiazka) {
    float kaucja = 0.0f;  // Zmienna do przechowywania kaucji
    string dataZwrotuFile;
    time_t now = time(0);
    tm localTime = {};
    localtime_s(&localTime, &now);
    string currentDate = to_string(1900 + localTime.tm_year) + "-" + to_string(1 + localTime.tm_mon) + "-" + to_string(localTime.tm_mday);

    ifstream plik("baza_ksiazek.txt");
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(plik, line)) {
        stringstream ss(line);
        string id, tytul, autor, rok, stan, dataZwrotuFile;
        getline(ss, id, ',');
        getline(ss, tytul, ',');
        getline(ss, autor, ',');
        getline(ss, rok, ',');
        getline(ss, stan, ',');
        getline(ss, dataZwrotuFile, ',');

        if (stoi(id) == ksiazka.getID() && stan == "niedostepna") {
            found = true;

            // Calculate late fee if applicable
            if (dataZwrotuFile < currentDate) {
                tm dataZwrotu = {};
                istringstream ss(dataZwrotuFile);
                ss >> get_time(&dataZwrotu, "%Y-%m-%d");
                if (ss.fail()) {
                    cerr << "Blad konwersji daty!" << endl;
                    return -1.0f;
                }

                time_t tDataZwrotu = mktime(&dataZwrotu);
                double secondsLate = difftime(now, tDataZwrotu);
                int lateDays = secondsLate / (60 * 60 * 24);
                if (lateDays > 0) {
                    kaucja = lateDays * 2.0f;  // Kaucja = late days * 2zl
                }
            }

            line = id + "," + tytul + "," + autor + "," + rok + ",dostepna,";
        }
        lines.push_back(line);
    }
    plik.close();

    if (!found) {
        cerr << "Blad zwrotu! Egzemplarz o ID " << ksiazka.getID() << " nie byl wypozyczony." << endl;
        return -1.0f;
    }

    // Save updated lines to the file
    ofstream outPlik("baza_ksiazek.txt");
    for (const auto& l : lines) {
        outPlik << l << endl;
    }
    outPlik.close();

    // Output the result of the return
    if (kaucja > 0.0f) {
        cout << "Ksiazka zwrocona po terminie. Naliczenie kaucji: " << kaucja << " zl." << endl;
    }
    else {
        cout << "Ksiazka o ID " << ksiazka.getID() << " zostala zwrocona w terminie." << endl;
    }

    return kaucja;  // Zwracamy wartoœæ kaucji
}