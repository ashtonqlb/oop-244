#include <iostream>
#include <iomanip>
#include <cstring>

#include "Rectangle.h"

namespace sdds {
    Rectangle::Rectangle() : LblShape(), m_width(0), m_height(0) {}
	Rectangle::Rectangle(const char* label, unsigned int width, unsigned int height) : LblShape(label), m_width(width), m_height(height) {}

	void Rectangle::getSpecs(std::istream& istr) {
		LblShape::getSpecs(istr);
        istr >> m_width;
        istr.ignore(1000, ',');
        istr >> m_height;
        istr.ignore(1000, '\n');
	}

	void Rectangle::draw(std::ostream& ostr) const {
        if (m_width > 2 && m_height > 2) {
            ostr << '+';
            for (unsigned int i = 0; i < m_width - 2; i++) {
                ostr << '-';
            }
            ostr << '+' << std::endl;

            ostr << '|';
            const char* lbl = LblShape::label();
            if (lbl != nullptr) {
                ostr.write(lbl, std::min(static_cast<size_t>(m_width - 2), strlen(lbl)));
                for (unsigned int i = strlen(lbl); i < m_width - 2; i++) {
                    ostr << ' ';
                }
            }
            ostr << '|' << std::endl;

            for (unsigned int i = 0; i < m_height - 3; i++) {
                ostr << '|';
                for (unsigned int j = 0; j < m_width - 2; j++) {
                    ostr << ' ';
                }
                ostr << '|' << std::endl;
            }

            ostr << '+';
            for (unsigned int i = 0; i < m_width - 2; i++) {
                ostr << '-';
            }
            ostr << '+';
        }
	}
}