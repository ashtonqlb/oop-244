#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Graduate.h"

namespace sdds {
	Graduate::Graduate(const char* name, int age, const char* title, const char* supervisor) : Student(name, age) {
		m_thesis_title = new char[strlen(title) + 1];
        strcpy(m_thesis_title, title);

        m_supervisor_name = new char[strlen(supervisor) + 1];
        strcpy(m_supervisor_name, supervisor);

        delete[] title;
        delete[] supervisor;
	}

	Graduate::Graduate(const Graduate& other) : Student(other) {
        m_thesis_title = new char[strlen(other.m_thesis_title) + 1];
        strcpy(m_thesis_title, other.m_thesis_title);

        m_supervisor_name = new char[strlen(other.m_supervisor_name) + 1];
        strcpy(m_supervisor_name, other.m_supervisor_name);
    }


	Graduate& Graduate::operator=(const Graduate& other) {
		 if (this != &other) {
            Student::operator=(other);

            delete[] m_thesis_title;
            m_thesis_title = new char[strlen(other.m_thesis_title) + 1];
            strcpy(m_thesis_title, other.m_thesis_title);

            delete[] m_supervisor_name;
            m_supervisor_name = new char[strlen(other.m_supervisor_name) + 1];
            strcpy(m_supervisor_name, other.m_supervisor_name);
        }
        return *this;
	}

	void Graduate::display() const {
        Student::display();
        std::cout << "Thesis Title: " << (m_thesis_title ? m_thesis_title : "N/A") 
                  << "\nSupervisor: " << (m_supervisor_name ? m_supervisor_name : "N/A") << std::endl;
	}
}
