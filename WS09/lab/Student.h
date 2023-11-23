z#ifndef SDDS_STUDENT_H
#define SDDS_STUDENT_H

#include <iostream>
#include <cstring>

namespace sdds {
	class Student {
	char* name;
	int age;

	public:
	    // Default constructor
	    Student() : name(nullptr), age(0) {}

	    // Parameterized constructor
	    Student(const char* studentName, int studentAge) {
	        name = new char[strlen(studentName) + 1];
	        strcpy(name, studentName);
	        age = studentAge;
	    }

	    // Copy constructor
	    Student(const Student& other) {
	        if (other.name != nullptr) {
	            name = new char[strlen(other.name) + 1];
	            strcpy(name, other.name);
	        } else {
	            name = nullptr;
	        }
	        age = other.age;
	    }

	    // Copy assignment operator
	    Student& operator=(const Student& other) {
	        if (this != &other) {
	            delete[] name;
	            if (other.name != nullptr) {
	                name = new char[strlen(other.name) + 1];
	                strcpy(name, other.name);
	            } else {
	                name = nullptr;
	            }
	            age = other.age;
	        }
	        return *this;
	    }

	    // Destructor
	    virtual ~Student() {
	        delete[] name;
	    }

	    // Display method
	    void display() const {
	        std::cout << "Name: " << (name ? name : "N/A") << ", Age: " << age << std::endl;
	    }
	};
}

#endif