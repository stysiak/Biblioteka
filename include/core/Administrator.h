#pragma once
#include "../models/Employee.h"
#include "../database/BookDatabase.h"
#include "../database/EmployeeDatabase.h"

class Administrator : public Employee {
public:
    Administrator();
    Administrator(const string& pesel, const string& imie, const string& nazwisko,
                 const string& login, const string& haslo, const string& funkcja);

    void addBook(BookDatabase &database, const Book &book) noexcept;

    void removeBook(BookDatabase &database, const Book &book) noexcept;

    void addEmployee(EmployeeDatabase &database, const Employee &employee) noexcept;

    void removeEmployee(EmployeeDatabase &database, const Employee &employee) noexcept;

    void showEmployeeList(const EmployeeDatabase &database) const noexcept;

    virtual ~Administrator() = default;
};
