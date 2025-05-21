#include "../../include/database/ReaderDatabase.h"

string ReaderDatabase::fileName = "../../data/readers_database.json";

ReaderDatabase::ReaderDatabase() {}

bool ReaderDatabase::validatePesel(const string& pesel) {
    if (pesel.length() != 11 || !std::all_of(pesel.begin(), pesel.end(), ::isdigit)) {
        cerr << "Invalid PESEL: " << pesel << endl;
        return false;
    }
    return true;
}

json ReaderDatabase::loadDatabase() const {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening JSON file!" << endl;
        return {};
    }
    json j;
    file >> j;
    return j;
}

void ReaderDatabase::saveDatabase(const json& j) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error saving JSON file!" << endl;
        return;
    }
    file << j.dump(4);
}

int ReaderDatabase::createAccount(const ReaderAccount& reader) {
    string pesel = reader.getPesel();
    if (!validatePesel(pesel)) return -1;

    json db = loadDatabase();
    if (db.contains(pesel)) {
        cerr << "Reader with PESEL " << pesel << " already exists." << endl;
        return -1;
    }

    db[pesel] = {
        {"firstName", reader.getFirstName()},
        {"lastName", reader.getLastName()},
        {"deposit", reader.getDeposit()},
        {"bookCount", reader.getBooksCount()},
        {"borrowed", json::array()}
    };

    saveDatabase(db);
    cout << "Reader account with PESEL " << pesel << " has been created." << endl;
    return 1;
}

int ReaderDatabase::deleteAccount(const ReaderAccount& reader) {
    string pesel = reader.getPesel();
    if (!validatePesel(pesel)) return -1;

    json db = loadDatabase();
    if (!db.contains(pesel)) {
        cerr << "Reader not found." << endl;
        return -1;
    }

    db.erase(pesel);
    saveDatabase(db);
    cout << "Account deleted." << endl;
    return 1;
}

void ReaderDatabase::showReaderList() const {
    json db = loadDatabase();
    for (auto& [pesel, data] : db.items()) {
        cout << "PESEL: " << pesel
             << ", First name: " << data["firstName"]
             << ", Last name: " << data["lastName"]
             << ", Deposit: " << data["deposit"]
             << ", Book count: " << data["bookCount"];

        if (!data["borrowed"].empty()) {
            cout << ", Borrowed: ";
            for (const auto& id : data["borrowed"]) cout << id << ", ";
        }
        cout << endl;
    }
}

int ReaderDatabase::addBorrow(const ReaderAccount& reader, int bookID) {
    json db = loadDatabase();
    string pesel = reader.getPesel();

    if (!db.contains(pesel)) return -1;

    auto& data = db[pesel];
    data["bookCount"] = int(data["bookCount"]) + 1;
    data["borrowed"].push_back(bookID);

    saveDatabase(db);
    return bookID;
}

int ReaderDatabase::removeBorrow(const ReaderAccount& reader, int bookID) {
    json db = loadDatabase();
    string pesel = reader.getPesel();
    if (!db.contains(pesel)) return -1;

    auto& data = db[pesel];
    auto& borrowed = data["borrowed"];

    auto it = std::find(borrowed.begin(), borrowed.end(), bookID);
    if (it != borrowed.end()) {
        borrowed.erase(it);
        data["bookCount"] = int(data["bookCount"]) - 1;
        saveDatabase(db);
        return bookID;
    }

    return -1;
}

bool ReaderDatabase::canBorrow(const ReaderAccount& reader) {
    json db = loadDatabase();
    string pesel = reader.getPesel();
    if (!db.contains(pesel)) return false;

    return int(db[pesel]["bookCount"]) < 5;
}

void ReaderDatabase::checkAccount(const ReaderAccount& reader) {
    json db = loadDatabase();
    string pesel = reader.getPesel();

    if (!db.contains(pesel)) {
        cerr << "Reader not found." << endl;
        return;
    }

    auto& d = db[pesel];
    cout << "\n--- Reader data ---" << endl;
    cout << "PESEL: " << pesel << endl;
    cout << "First name: " << d["firstName"] << endl;
    cout << "Last name: " << d["lastName"] << endl;
    cout << "Deposit: " << d["deposit"] << endl;
    cout << "Book count: " << d["bookCount"] << endl;
    cout << "Borrowed: ";
    for (const auto& id : d["borrowed"]) cout << id << ", ";
    cout << endl;
}

int ReaderDatabase::setDeposit(ReaderAccount& reader, float deposit) {
    json db = loadDatabase();
    string pesel = reader.getPesel();
    if (!db.contains(pesel)) return -1;

    db[pesel]["deposit"] = deposit;
    saveDatabase(db);
    return 1;
}

int ReaderDatabase::removeDeposit(ReaderAccount& reader) {
    return setDeposit(reader, 0);
}