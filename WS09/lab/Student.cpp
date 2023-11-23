#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Student.h"

namespace sdds {
	Student::Student(const char * name, int age) {
	}

	Student::Student(const Student& other) {
		if (other.m_name != nullptr) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        }
		else {
            m_name = nullptr;
        }
        m_name = other.m_name;
	}

	Student& Student::operator=(const Student& other) {
	if (this != &other) {
            delete[] m_name;
            if (other.m_name != nullptr) {
                m_name = new char[strlen(other.m_name) + 1];
                strcpy(m_name, other.m_name);
            }
			else {
                m_name = nullptr;
            }
            m_name = other.m_name;
        }
        return *this;
	}

	void Student::display() const {
		std::cout << "Name: " << (m_name ? m_name : "N/A") << "\nAge: " << m_age << std::endl;
	}
}
