#define _CRT_SECURE_NO_WARNINGS

/***********************************************************************
// OOP244 Workshop # 9: tester program
//
// File: main.cpp
// Version 1.1
// Date: 11/20/2022	
// Author: Ashton Lunken
// Description: This program demonstrates the concept of Polymorphism
// No stealsies I swear. Following the Academic Integrity guidelines is my favourite hobby.
// Student ID: 134128214
*/

#include "Student.h"

namespace sdds {
	Student::Student(const char* name, int age): age(age) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	Student::Student(const Student& other): age(other.age) {
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
	}

	Student& Student::operator=(const Student& other) {
		if (this != &other) {
			delete[] name;
			name = new char[strlen(other.name) + 1];
			strcpy(name, other.name);
			age = other.age;
		}
		return *this;
	}

	void Student::display() const {
		std::cout << "Name: " << name << "\nAge: " << age << std::endl;
	}
}
