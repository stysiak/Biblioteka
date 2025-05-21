#include "../header.h"
#include "../include/database/ReaderDatabase.h"
#include "../include/database/BookDatabase.h"
#include "../include/models/ReaderAccount.h"
#include "../include/models/Book.h"
#include "../include/models/Employee.h"
#include "../include/database/EmployeeDatabase.h"
#include "../include/utils/Borrowing.h"
#include "../include/utils/Return.h"

using namespace std;

int main() {
    EmployeeDatabase employeeDatabase;
    ReaderDatabase readerDatabase;
    BookDatabase bookDatabase;
    string login, role;
    int choice;

    system("cls"); // clear screen
    cout << "=====================================" << endl;
    cout << "      WELCOME TO THE LIBRARY SYSTEM  " << endl;
    cout << "=====================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Exit" << endl;
    cout << "=====================================" << endl;
    cout << "Choose an option: ";
    cin >> choice;

    switch (choice) {
    case 1:
        tie(login, role) = employeeDatabase.login();
        if (!login.empty() && !role.empty()) {
            if (role == "admin") {
                Administrator admin;
                do {
                    cout << "\n--- Administrator Menu ---\n";
                    cout << "1. Add book\n";
                    cout << "2. Remove book\n";
                    cout << "3. Add employee\n";
                    cout << "4. Remove employee\n";
                    cout << "5. Add reader\n";
                    cout << "6. Remove reader\n";
                    cout << "7. Show books from database\n";
                    cout << "8. Show readers from database\n";
                    cout << "9. Show employees from database\n";
                    cout << "10. Exit program\n";
                    cout << "Choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: {
                        // add book
                        string title, author, status;
                        int year, ID;

                        cout << "Enter book title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter book author: ";
                        getline(cin, author);
                        cout << "Enter year of publication: ";
                        cin >> year;
                        cout << "Assign book ID: ";
                        cin >> ID;
                        Book newBook(ID, title, author, year, status);
                        admin.addBook(bookDatabase, newBook);
                        break;
                    }
                    case 2: {
                        // remove book
                        int bookID;
                        cout << "Enter book ID to remove: ";
                        cin >> bookID;
                        Book bookToRemove(bookID);
                        admin.removeBook(bookDatabase, bookToRemove);
                        break;
                    }
                    case 3: {
                        // add employee
                        string pesel, firstName, lastName, login, password, role;
                        cout << "Enter first name: ";
                        cin >> firstName;
                        cout << "Enter last name: ";
                        cin >> lastName;
                        cout << "Enter login: ";
                        cin >> login;
                        cout << "Enter password: ";
                        cin >> password;
                        cout << "Enter pesel: ";
                        cin >> pesel;
                        cout << "Enter role (admin/employee): ";
                        cin >> role;
                        Employee newEmployee(pesel, firstName, lastName, login, password, role);
                        admin.addEmployee(employeeDatabase, newEmployee);
                        break;
                    }
                    case 4: {
                        // remove employee
                        string pesel;
                        cout << "Enter pesel: ";
                        cin >> pesel;
                        Employee employeeToRemove(pesel);
                        admin.removeEmployee(employeeDatabase, employeeToRemove);
                        break;
                    }
                    case 5: {
                        // add reader
                        string pesel, firstName, lastName;

                        cout << "Enter first name: ";
                        cin >> firstName;
                        cout << "Enter last name: ";
                        cin >> lastName;
                        cout << "Enter pesel: ";
                        cin >> pesel;

                        ReaderAccount newReader(pesel, firstName, lastName);
                        admin.addReader(readerDatabase, newReader);
                        break;
                    }
                    case 6: {
                        // remove reader
                        string pesel;
                        cout << "Enter pesel of reader to remove: ";
                        cin >> pesel;
                        ReaderAccount readerToRemove(pesel);
                        admin.removeReader(readerDatabase, readerToRemove);
                        break;
                    }
                    case 7: {
                        // show books
                        admin.showBookList(bookDatabase);
                        break;
                    }
                    case 8: {
                        // show readers
                        admin.showReaderList(readerDatabase);
                        break;
                    }
                    case 9: {
                        // show employees
                        admin.showEmployeeList(employeeDatabase);
                        break;
                    }
                    case 10: {
                        cout << "Closing program..." << endl;
                        exit(0);
                        break;
                    }
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                } while (true);
            }
            else if (role == "employee") {
                Employee employee;
                do {
                    cout << "\n--- Employee Menu ---\n";
                    cout << "1. Check reader account\n";
                    cout << "2. Create reader account\n";
                    cout << "3. Remove reader account\n";
                    cout << "4. Return book\n";
                    cout << "5. Borrow book\n";
                    cout << "6. Accept deposit\n";
                    cout << "7. Show books from database\n";
                    cout << "8. Show reader list\n";
                    cout << "9. Exit program\n";
                    cout << "Choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: {
                        // check reader account
                        string pesel;
                        cout << "Enter pesel: ";
                        cin >> pesel;
                        ReaderAccount reader(pesel);
                        employee.checkAccount(readerDatabase, reader);
                        break;
                    }
                    case 2: {
                        // create reader account
                        string pesel, firstName, lastName;

                        cout << "Enter first name: ";
                        cin >> firstName;
                        cout << "Enter last name: ";
                        cin >> lastName;
                        cout << "Enter pesel: ";
                        cin >> pesel;

                        ReaderAccount newReader(pesel, firstName, lastName);
                        employee.addReader(readerDatabase, newReader);
                        break;
                    }
                    case 3: {
                        // remove reader account
                        string pesel;
                        cout << "Enter pesel of reader to remove: ";
                        cin >> pesel;
                        ReaderAccount readerToRemove(pesel);
                        employee.removeReader(readerDatabase, readerToRemove);
                        break;
                    }
                    case 4: {
                        int bookID;
                        string pesel;
                        cout << "Enter book ID: ";
                        cin >> bookID;
                        cout << "Enter reader pesel: ";
                        cin >> pesel;
                        ReaderAccount reader(pesel);
                        employee.returnBook(bookDatabase, readerDatabase, bookID, reader);
                        break;
                    }
                    case 5: {
                        int bookID;
                        string pesel;
                        cout << "Enter book ID: ";
                        cin >> bookID;
                        cout << "Enter reader pesel: ";
                        cin >> pesel;
                        ReaderAccount reader(pesel);
                        employee.borrowBook(bookDatabase, readerDatabase, bookID, reader);
                        break;
                    }
                    case 6: {
                        // accept deposit
                        string pesel;
                        cout << "Enter reader pesel: ";
                        cin >> pesel;
                        ReaderAccount reader(pesel);
                        employee.acceptDeposit(readerDatabase, reader);
                        break;
                    }
                    case 7: {
                        // show books
                        employee.showBookList(bookDatabase);
                        break;
                    }
                    case 8: {
                        employee.showReaderList(readerDatabase);
                        break;
                    }
                    case 9: {
                        cout << "Closing program..." << endl;
                        exit(0);
                        break;
                    }
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                } while (true);
            }
        }
        else {
            cout << "Incorrect login data!" << endl;
        }
        break;
    case 2:
        cout << "Exiting program" << endl;
        break;
    default:
        cout << "Invalid option. Try again." << endl;
        system("pause");
        break;
    }

    return 0;
}