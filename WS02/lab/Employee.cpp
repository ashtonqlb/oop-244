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

namespace sdds
{
	int noOfEmployees;
	Employee* employees;

	void sort()
	{
		int i, j;
		Employee temp;
		for (i = noOfEmployees - 1; i > 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				if (employees[j].m_empNo > employees[j + 1].m_empNo)
				{
					temp = employees[j];
					employees[j] = employees[j + 1];
					employees[j + 1] = temp;
				}
			}
		}
	}

	bool load(Employee new_employee) {
		bool ok = false;
		// return the combined success result of the three read functions. These read 
		// functions should set the properties of the reference argument of the load function
        // to the values read from the file.
		char* name = nullptr;
		int empNo = 0;
		double salary = 0;
		ok = read(name) && read(empNo) && read(salary);

		return ok;
	}

	bool load() {
		bool ok = false;
        int i = 0;
		if (openFile(DATAFILE)) {
			noOfEmployees = noOfRecords();
			employees = new Employee[noOfEmployees];
			for (i = 0; i < noOfEmployees; i++) {
				load(employees[i]);
			}
			if (i != noOfEmployees) {
				cout << "Error: incorrect number of records read; the data is possibly corrupted" << endl;
			}
			else {
				ok = true;
			}
			closeFile();
		}
		else {
			cout << "Could not open data file: " << DATAFILE << endl;
		}
		return ok;
	}

	void display(const Employee& emp) {
		ostream& os = cout;
		os << emp.m_empNo << ": " << emp.m_name << ", " << emp.m_salary << endl;
	}

	void display()
	{
		sort();
		ostream& os = cout;
		os << "Employee Salary report, sorted by employee number" << endl;
		os << "no- Empno, Name, Salary" << endl;
		os << "------------------------------------------------" << endl;

		for (int i = 0; i < noOfEmployees; i++)
		{
			os << i + 1 << "- ";
			display(employees[i]);
		}	
	}

	void deallocateMemory() {
		for (int i = 0; i < noOfEmployees; i++) {
			delete[] employees[i].m_name;
		}

		delete[] employees;
	}
}
