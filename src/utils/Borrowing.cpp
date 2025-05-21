#include "../../include/utils/Borrowing.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

string Borrowing::fileName = "../../data/books_database.json";

int Borrowing::borrowBook(const Book& book) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Cannot open JSON file!" << endl;
        return -1;
    }

    json books;
    inFile >> books;
    inFile.close();

    bool found = false;
    time_t now = time(0);
    tm ltm = {};
    localtime_s(&ltm, &now);
    ltm.tm_mday += 30;  // Add 30 days
    mktime(&ltm);
    ostringstream oss;
    oss << put_time(&ltm, "%Y-%m-%d");
    string returnDate = oss.str();

    for (auto& b : books) {
        if (b["id"] == book.getID() && b["status"] == "available") {
            b["status"] = "unavailable";
            b["returnDate"] = returnDate;
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Book with ID " << book.getID() << " is unavailable or does not exist!" << endl;
        return -1;
    }

    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Cannot save JSON file!" << endl;
        return -1;
    }
    outFile << setw(4) << books << endl;
    outFile.close();

    cout << "Book with ID " << book.getID() << " has been borrowed. Return date: " << returnDate << endl;
    return book.getID();
}