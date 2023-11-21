#define _CRT_SECURE_NO_WARNINGS

#include "LblShape.h"

namespace sdds {
	LblShape::LblShape() : m_label(nullptr) {}

	const char* LblShape::label() const { 
		return m_label;
	}

	LblShape::LblShape(const char* label) : m_label(nullptr) {
        if (label != nullptr) {
            m_label = new char[strlen(label) + 1];
            strcpy(m_label, label);
        }
	}

	LblShape::~LblShape() {
		delete[] m_label;
	}

	void LblShape::getSpecs(std::istream& istr) {
		char buf[50];
		istr.getline(buf, 50, ',');

		delete[] m_label;
		m_label = new char[strlen(buf) + 1];
		strcpy(m_label, buf);
	}
}
