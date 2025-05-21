#include "../../include/core/Administrator.h"

Administrator::Administrator() : Employee("", "", "", "", "", "") {
}

Administrator::Administrator(const string& pesel, const string& imie, const string& nazwisko, const string& login, const string& haslo, const string& funkcja)
    : Employee(pesel, imie, nazwisko, login, haslo, funkcja) {
}

void Administrator::addBook(BookDatabase& database, const Book& book) noexcept {
    int id = database.updateStateAdd(book);
    if (id != -1) {
        cout << "Book '" << book.getTitle() << "' was added with ID: " << book.getID() << endl;
    }
}

void Administrator::removeBook(BookDatabase& database, const Book& book) noexcept {
    int id = database.updateStateRemove(book);
    if (id != -1) {
        cout << "Book with ID " << book.getID() << " was removed." << endl;
    }
}

void Administrator::addEmployee(EmployeeDatabase& database, const Employee& employee) noexcept {
    int id = database.addEmployee(employee);
    if (id != -1) {
        cout << "Employee with PESEL " << employee.getPesel() << " was added to the database." << endl;
    }
}

void Administrator::removeEmployee(EmployeeDatabase& database, const Employee& employee) noexcept {
    int id = database.removeEmployee(employee);
    if (id != -1) {
        cout << "Employee with PESEL " << employee.getPesel() << " was removed from the database." << endl;
    }
}

void Administrator::showEmployeeList(const EmployeeDatabase& database) const noexcept {
    database.showEmployeeList();
}