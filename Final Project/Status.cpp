#define _CRT_SECURE_NO_WARNINGS


#include <cstring>
#include "Status.h"

namespace sdds {
	Status::Status(const char* description, int code) : m_code(code) {
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
	}

	Status::Status(const Status& other) : m_code(other.m_code) {
		if (other.m_description) {
			m_description = new char[strlen(other.m_description) + 1];
			strcpy(m_description, other.m_description);
		}
	}

	Status::~Status() {
		clear();
	}

	Status& Status::operator=(const Status& other) {
		if (this != &other) {
			delete[] m_description;
			if (other.m_description) {
				m_description = new char[strlen(other.m_description) + 1];
				strcpy(m_description, other.m_description);
			}
			else {
				m_description = nullptr;
			}
			m_code = other.m_code;
		}
		return *this;
	}

	Status& Status::operator=(const char* description) {
		delete[] m_description;

		if (description) {
			m_description = new char[strlen(description) + 1];
			strcpy(m_description, description);
		}
		else {
			description = nullptr;
		}
		return *this;
	}

	Status& Status::operator=(int code) {
		m_code = code;
		return *this;
	}

	Status& Status::clear() {
		delete[] m_description;
		m_description = nullptr;
		m_code = 0;

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Status& status) {
		if (!status) {
			if (status.m_code != 0) {
				os << "ERR#" << status.m_code << ": ";
			}
			if (status.m_description) {
				os << status.m_description;
			}
		}
		return os;
	}
}