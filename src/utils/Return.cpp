#include "../../include/utils/Return.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

string Return::fileName = "../../data/books_database.json";

float Return::returnBook(const Book& book) {
    float deposit = 0.0f;
    time_t now = time(0);
    tm localTime = {};
    localtime_s(&localTime, &now);
    ostringstream oss;
    oss << put_time(&localTime, "%Y-%m-%d");
    string currentDate = oss.str();

    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Cannot open JSON file!" << endl;
        return -1.0f;
    }

    json books;
    inFile >> books;
    inFile.close();

    bool found = false;

    for (auto& b : books) {
        if (b["id"] == book.getID() && b["status"] == "unavailable") {
            found = true;

            // Check if return date exists
            if (b.contains("returnDate")) {
                string returnDateStr = b["returnDate"];

                tm returnDate = {};
                istringstream ss(returnDateStr);
                ss >> get_time(&returnDate, "%Y-%m-%d");
                if (ss.fail()) {
                    cerr << "Date conversion error!" << endl;
                    return -1.0f;
                }

                time_t tReturnDate = mktime(&returnDate);
                double secondsLate = difftime(now, tReturnDate);
                int lateDays = secondsLate / (60 * 60 * 24);
                if (lateDays > 0) {
                    deposit = lateDays * 2.0f;
                }
            }

            // Update status and remove return date
            b["status"] = "available";
            b.erase("returnDate");
            break;
        }
    }

    if (!found) {
        cerr << "Return error! Book with ID " << book.getID() << " was not borrowed." << endl;
        return -1.0f;
    }

    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Cannot save JSON file!" << endl;
        return -1.0f;
    }

    outFile << setw(4) << books << endl;
    outFile.close();

    // Final info
    if (deposit > 0.0f) {
        cout << "Book returned late. Deposit charged: " << deposit << " PLN." << endl;
    } else {
        cout << "Book with ID " << book.getID() << " was returned on time." << endl;
    }

    return deposit;
}