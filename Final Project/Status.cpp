#define _CRT_SECURE_NO_WARNINGS

#include "Status.h"

using namespace sdds;

Status::Status(const char* description, int code) : m_code(code) {
	if (description) {
		m_description = new char[strlen(description) + 1];
		strcpy(m_description, description);
	}
	else strcpy(m_description, "\0");
}

sdds::Status::Status(const Status& other) : m_code(other.m_code) {
	if (other.m_description) {
		m_description = new char[strlen(other.m_description) + 1];
		strcpy(m_description, other.m_description);
	}
	else strcpy(m_description, "\0");
}

sdds::Status::~Status() {
	clear();
}

Status& sdds::Status::operator=(const Status& other) {
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

Status& sdds::Status::operator=(const char* description) {
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

Status& sdds::Status::operator=(int code) {
	m_code = code;
	return *this;
}

Status& sdds::Status::clear() {
	delete[] m_description;
	m_description = nullptr;
	m_code = 0;

	return *this;
}

std::ostream& sdds::operator<<(std::ostream& os, const Status& status) {
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