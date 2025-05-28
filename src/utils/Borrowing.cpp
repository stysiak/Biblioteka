// Borrowing.cpp
#include "../../include/utils/Borrowing.h"
#include "../../include/utils/Logger.h"
#include <fstream>
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
        Logger::error("Cannot open file: " + fileName);
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

    Logger::debug("Searching for book with ID: " + std::to_string(book.getID()));

    for (auto& b : books) {
        if (b["id"] == book.getID() && b["status"] == "available") {
            b["status"] = "unavailable";
            b["returnDate"] = returnDate;
            found = true;
            Logger::info("Found book with ID: " + std::to_string(book.getID()) +
                        ". Status changed to unavailable");
            break;
        }
    }

    if (!found) {
        Logger::warning("Book with ID " + std::to_string(book.getID()) +
                       " is unavailable or does not exist");
        return -1;
    }

    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        Logger::error("Cannot save to file: " + fileName);
        return -1;
    }

    outFile << setw(4) << books << endl;
    outFile.close();

    Logger::info("Book with ID " + std::to_string(book.getID()) +
                " has been borrowed. Return date: " + returnDate);
    return book.getID();
}