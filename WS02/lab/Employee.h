/***********************************************************************
// OOP244 Workshop #2 lab (part 1)
//
// File Employee.h
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//    To be completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_

#define DATAFILE "employees.csv"

namespace sdds {
   struct Employee {
      char* m_name {};
      int m_empNo  {};
      double m_salary {};
   };

   //sorts the dynamic array of employees based on the GPA of the employees.
   void sort();
   // loads a employee structure with its values from the file
   bool load(Employee &new_employee);
   // allocates the dynamic array of employees and loads all the file
   // records into the array
   bool load();

   void display(const Employee& emp);

   void display();

   void deallocateMemory();
}
#endif // SDDS_EMPLOYEE_H_