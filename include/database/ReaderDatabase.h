#pragma once

#include "../models/ReaderAccount.h"
#include "../../header.h"

class ReaderDatabase {
private:
    std::unordered_map<int, std::shared_ptr<ReaderAccount>> czytelnicy;

public:
    static std::string fileName;

    ReaderDatabase();

    bool validatePesel(const string &pesel);

    json loadDatabase() const;

    void saveDatabase(const json &j);

    int createAccount(const ReaderAccount &reader);

    int deleteAccount(const ReaderAccount &reader);

    void showReaderList() const;

    int addBorrow(const ReaderAccount &reader, int bookID);

    int removeBorrow(const ReaderAccount &reader, int bookID);

    bool canBorrow(const ReaderAccount &reader);

    void checkAccount(const ReaderAccount &reader);

    int setDeposit(ReaderAccount &reader, float deposit);

    int removeDeposit(ReaderAccount &reader);

};
