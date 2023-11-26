#define _CRT_SECURE_NO_WARNINGS

#include "Graduate.h"

namespace sdds {
	Graduate::Graduate(const char* name, int age, const char* thesisTitle, const char* supervisorName): Student(name, age) {
		this->thesisTitle = new char[strlen(thesisTitle) + 1];
		strcpy(this->thesisTitle, thesisTitle);
		this->supervisorName = new char[strlen(supervisorName) + 1];
		strcpy(this->supervisorName, supervisorName);
	}

	Graduate::Graduate(const Graduate& other): Student(other) {
		thesisTitle = new char[strlen(other.thesisTitle) + 1];
		strcpy(thesisTitle, other.thesisTitle);
		supervisorName = new char[strlen(other.supervisorName) + 1];
		strcpy(supervisorName, other.supervisorName);
	}

	Graduate& Graduate::operator=(const Graduate& other) {
		if (this != &other) {
			Student::operator=(other);
			delete[] thesisTitle;
			delete[] supervisorName;
			thesisTitle = new char[strlen(other.thesisTitle) + 1];
			strcpy(thesisTitle, other.thesisTitle);
			supervisorName = new char[strlen(other.supervisorName) + 1];
			strcpy(supervisorName, other.supervisorName);
		}
		return *this;
	}

	void Graduate::display() const {
		Student::display();
		std::cout << "Thesis Title: " << thesisTitle << "\nSupervisor: " << supervisorName << std::endl << "---------------------------------------------" << std::endl;
	}
}
