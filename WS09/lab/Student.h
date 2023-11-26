#ifndef SDDS_STUDENT_H
#define SDDS_STUDENT_H

#include <iostream>
#include <cstring>

namespace sdds {
	class Student {
	    char* name;
	    int age;

		public:
	    Student() : name(nullptr), age(0) {}
	    Student(const char* name, int age);
	    Student(const Student& other);
	    Student& operator=(const Student& other);

	    virtual ~Student() {
	        delete[] name;
	    }

	    virtual void display() const;
	};
}

#endif