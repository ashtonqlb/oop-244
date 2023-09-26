/***********************************************************************
// OOP244 Workshop #2 lab (part 1)
//
// File  Employee.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//    To be completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#include <iostream>
#include "Employee.h"
#include "File.h"
using namespace std;
namespace sdds {

    int noOfEmployees;
    Employee* employees;


    void sort() {
        int i, j;
        Employee temp;
        for (i = noOfEmployees - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (employees[j].m_empNo > employees[j + 1].m_empNo) {
                    temp = employees[j];
                    employees[j] = employees[j + 1];
                    employees[j + 1] = temp;
                }
            }
        }
    }

    // TODO: Finish the implementation of the 1 arg load function which
    // reads one employee record from the file and loads it into the employee reference
    // argument

    bool load(Employee& emp) {
        bool ok = read(emp.m_empNo) &&
            read(emp.m_salary) &&
            read(emp.m_name);;
        return ok;
    }

    // TODO: Finish the implementation of the 0 arg load function 
    bool load() {
        bool ok = false;
        int i{};
        if (openFile("employees.csv")) {
            noOfEmployees = noOfRecords();
            employees = new Employee[noOfEmployees];

            do ok = load(employees[i++]);
            while (ok && i < noOfEmployees);
            if (i != noOfEmployees)
                cout << "Error: incorrect number of records read; the data is possibly corrupted" << endl;
        }
        else cout << "Could not open data file: employees.csv" << endl;
        closeFile();
        return ok;
    }

    // TODO: Implementation for the display functions go here
    void display(const Employee& emp) {
        ostream& os = cout;
        os << emp.m_empNo << ": " << emp.m_name << ", $" << emp.m_salary << endl;
    }

    void display() {
        sort();
        ostream& os = cout;
        os << "Employee Salary report, sorted by employee number" << endl;
        os << "no- Empno, Name, Salary" << endl;
        os << "------------------------------------------------" << endl;

        for (int i = 0; i < noOfEmployees; i++) {
            os << i + 1 << "- ";
            display(employees[i]);
        }
    }

    // TODO: Implementation for the deallocateMemory function goes here

    void deallocateMemory() {
        for (int i = 0; i < noOfEmployees; i++) {
            delete[] employees[i].m_name;
        }

        delete[] employees;
    }
}