#include "../../include/database/EmployeeDatabase.h"

string EmployeeDatabase::fileName = "../../data/employees_database.json";

bool EmployeeDatabase::validatePesel(const string& pesel) {
    if (pesel.length() != 11) {
        cerr << "Invalid PESEL: " << pesel << ". PESEL should have 11 digits." << endl;
        return false;
    }

    if (!std::all_of(pesel.begin(), pesel.end(), ::isdigit)) {
        cerr << "PESEL must contain only digits!" << endl;
        return false;
    }

    return true;
}

// Default constructor; loads employee data from JSON file and initializes the employee list
EmployeeDatabase::EmployeeDatabase() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open employees_database.json file :(" << endl;
        return;
    }

    try {
        json j;
        file >> j;

        for (const auto& employee : j) {
            string pesel = employee["pesel"];
            string firstName = employee["firstName"];
            string lastName = employee["lastName"];
            string login = employee["login"];
            string password = employee["password"];
            string role = employee["role"];

            // Check employee role
            if (role != "admin" && role != "employee") {
                cerr << "Invalid role: " << role << ". Skipping entry." << endl;
                continue;
            }

            // Add employee to the list
            Employee e(firstName, lastName, login, password, pesel, role);
            employeeList.push_back(e);
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }

    file.close();
}

pair<string, string> EmployeeDatabase::login() {
    string enteredLogin, enteredPassword;
    cout << "Enter login: ";
    cin >> enteredLogin;
    cout << "Enter password: ";
    cin >> enteredPassword;

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open employees_database.json file :-" << endl;
        return { "", "" };
    }

    try {
        json j;
        file >> j;

        for (const auto& employee : j) {
            string login = employee["login"];
            string password = employee["password"];
            string role = employee["role"];

            // Check login and password
            if (login == enteredLogin && password == enteredPassword) {
                cout << "Login successful. Welcome " << login << " (" << role << ")!" << endl;
                return { login, role };
            }
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }

    file.close();

    // If no match found
    return { "", "" };
}

// Function to add a new employee to the database and save their data to the JSON file
int EmployeeDatabase::addEmployee(const Employee& employee) {
    string peselStr = employee.getPesel();

    if (!validatePesel(peselStr)) {
        return -1;
    }

    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Cannot open employees_database.json file ;O" << endl;
        return -1;
    }

    json employees;
    try {
        readFile >> employees;
        readFile.close();

        // Check if an employee with the same PESEL already exists
        for (const auto& e : employees) {
            if (e["pesel"] == peselStr) {
                cerr << "Employee with this PESEL already exists!" << endl;
                return -1;
            }
        }

        // Check employee role
        if (employee.getRole() != "admin" && employee.getRole() != "employee") {
            cerr << "Invalid role: " << employee.getRole() << ". Employee was not added." << endl;
            return -1;
        }

        // Add employee to the list
        employeeList.push_back(employee);

        // Create new JSON object for the employee
        json newEmployee;
        newEmployee["pesel"] = employee.getPesel();
        newEmployee["firstName"] = employee.getFirstName();
        newEmployee["lastName"] = employee.getLastName();
        newEmployee["login"] = employee.getLogin();
        newEmployee["password"] = employee.getPassword();
        newEmployee["role"] = employee.getRole();

        // Add new employee to the JSON array
        employees.push_back(newEmployee);

        // Save updated array to file
        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << employees << endl;
            writeFile.close();
            return 1;
        }
        else {
            cerr << "Cannot open file for writing!\n";
            return -1;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return -1;
    }
}

// Function to remove an employee from the database by their PESEL number
int EmployeeDatabase::removeEmployee(const Employee& employee) {
    string pesel = employee.getPesel();

    if (!validatePesel(pesel)) {
        return -1;
    }

    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return -1;
    }

    json employees;
    bool found = false;

    try {
        readFile >> employees;
        readFile.close();

        // Create a new array without the employee with the given PESEL
        json newEmployees = json::array();

        for (const auto& e : employees) {
            if (e["pesel"] != pesel) {
                newEmployees.push_back(e);
            } else {
                found = true;
            }
        }

        if (!found) {
            cout << "Employee with PESEL " << pesel << " not found" << endl;
            return -1;
        }

        // Save updated array to file
        ofstream writeFile(fileName);
        if (writeFile.is_open()) {
            writeFile << setw(2) << newEmployees << endl;
            writeFile.close();
            return 1;
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

// Function to display the list of all employees in the database
void EmployeeDatabase::showEmployeeList() const {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Cannot open employees_database.json file ;E" << endl;
        return;
    }

    try {
        json j;
        file >> j;

        cout << "\n--- Employee list ---" << endl;

        for (const auto& employee : j) {
            cout << "Pesel: " << employee["pesel"]
                 << ", First name: " << employee["firstName"]
                 << ", Last name: " << employee["lastName"]
                 << ", Login: " << employee["login"]
                 << ", Password: " << employee["password"]
                 << ", Role: " << employee["role"] << endl;
        }
    }
    catch (json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }

    file.close();
}