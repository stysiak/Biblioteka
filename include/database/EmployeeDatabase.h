#pragma once
#include "../../header.h"
#include "../models/Employee.h"
#include "../core/Administrator.h"
#include "BookDatabase.h"

class EmployeeDatabase {
private:
    vector<Employee> employeeList;

public:
    static bool validatePesel(const string &pesel);

    EmployeeDatabase();

    pair<string, string> login();

    pair<string, string> logowanie();

    int addEmployee(const Employee & employee);

    int removeEmployee(const Employee & employee);

    void showEmployeeList() const;

    static string nazwaPliku;

    static string fileName;
};