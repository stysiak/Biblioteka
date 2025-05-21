#include "../../include/database/BookDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

string BookDatabase::fileName = "../../data/books_database.json";

BookDatabase::BookDatabase() {
    cout << "Trying to open file: " << fileName << endl;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open books_database.json file :(" << endl;
        return;
    }
    json j;
    file >> j;
    file.close();

    cout << "Loaded JSON data. Number of books: " << j.size() << endl;

    for (const auto& book : j) {
        int id = book["id"];
        string title = book["title"];
        string author = book["author"];
        int year = book["year"];
        string status = book["status"];
        string returnDate = "";

        if (book.contains("returnDate") && !book["returnDate"].is_null()) {
            returnDate = book["returnDate"];
        }

        cout << "Loaded book: " << id << " - " << title << " (" << status << ")" << endl;

        Book newBook(id, title, author, year, status);
        books[id] = make_shared<Book>(newBook);
    }
}

int BookDatabase::updateStateAdd(const Book& book) {
    int bID = book.getID();

    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Cannot open books_database.json file for reading!" << endl;
        return -2;
    }

    try {
        json booksJson;
        readFile >> booksJson;
        readFile.close();

        for (const auto& b : booksJson) {
            if (b["id"] == bID) {
                cerr << "Book with ID " << bID << " already exists." << endl;
                return -1;
            }
        }

        Book newBook(bID, book.getTitle(), book.getAuthorSurname(), book.getYearOfPublication(), "available");
        books[bID] = make_shared<Book>(newBook);

        json newBookJson;
        newBookJson["id"] = newBook.getID();
        newBookJson["title"] = newBook.getTitle();
        newBookJson["author"] = newBook.getAuthorSurname();
        newBookJson["year"] = newBook.getYearOfPublication();
        newBookJson["status"] = newBook.getStatus();

        booksJson.push_back(newBookJson);

        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << booksJson << endl;
            writeFile.close();
            return bID;
        }
        else {
            cerr << "Cannot open file for writing!" << endl;
            return -3;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return -4;
    }
}

int BookDatabase::updateStateRemove(const Book& book) {
    int bID = book.getID();

    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return -1;
    }

    try {
        json booksJson;
        readFile >> booksJson;
        readFile.close();

        bool found = false;
        json newBooksJson = json::array();

        for (const auto& b : booksJson) {
            if (b["id"] != bID) {
                newBooksJson.push_back(b);
            } else {
                found = true;
            }
        }

        if (!found) {
            cout << "Book with ID " << bID << " not found" << endl;
            return -1;
        }

        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << newBooksJson << endl;
            writeFile.close();

            books.erase(bID);
            return bID;
        }
        else {
            cerr << "Error opening file for writing!" << endl;
            return -1;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return -1;
    }
}

void BookDatabase::showBookList() const {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Cannot open books_database.json file" << endl;
        return;
    }

    try {
        json booksJson;
        file >> booksJson;
        file.close();

        cout << "\n--- Book list ---" << endl;

        for (const auto& book : booksJson) {
            cout << "ID: " << book["id"]
                 << ", Title: " << book["title"]
                 << ", Author: " << book["author"]
                 << ", Year: " << book["year"]
                 << ", Status: " << book["status"];

            if (book.contains("returnDate") && !book["returnDate"].is_null()) {
                cout << ", Return date: " << book["returnDate"];
            }

            cout << endl;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }
}

bool BookDatabase::borrowBook(int id, const string& returnDate) {
    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Cannot open books_database.json file for reading!" << endl;
        return false;
    }

    try {
        json booksJson;
        readFile >> booksJson;
        readFile.close();

        bool found = false;

        for (auto& book : booksJson) {
            if (book["id"] == id) {
                if (book["status"] == "unavailable") {
                    cerr << "Book with ID " << id << " is already borrowed!" << endl;
                    return false;
                }

                book["status"] = "unavailable";
                book["returnDate"] = returnDate;
                found = true;

                if (books.find(id) != books.end()) {
                    books[id]->setStatus("unavailable");
                    books[id]->setReturnDate(returnDate);
                }

                break;
            }
        }

        if (!found) {
            cerr << "Book with ID " << id << " not found" << endl;
            return false;
        }

        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << booksJson << endl;
            writeFile.close();
            return true;
        }
        else {
            cerr << "Cannot open file for writing!" << endl;
            return false;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return false;
    }
}

bool BookDatabase::returnBook(int id) {
    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Cannot open books_database.json file for reading!" << endl;
        return false;
    }

    try {
        json booksJson;
        readFile >> booksJson;
        readFile.close();

        bool found = false;

        for (auto& book : booksJson) {
            if (book["id"] == id) {
                if (book["status"] == "available") {
                    cerr << "Book with ID " << id << " is already available!" << endl;
                    return false;
                }

                book["status"] = "available";
                if (book.contains("returnDate")) {
                    book.erase("returnDate");
                }
                found = true;

                if (books.find(id) != books.end()) {
                    books[id]->setStatus("available");
                    books[id]->setReturnDate("");
                }

                break;
            }
        }

        if (!found) {
            cerr << "Book with ID " << id << " not found" << endl;
            return false;
        }

        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << booksJson << endl;
            writeFile.close();
            return true;
        }
        else {
            cerr << "Cannot open file for writing!" << endl;
            return false;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return false;
    }
}