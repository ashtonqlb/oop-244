#include "Line.h"

namespace sdds {
	Line::Line() : LblShape(), m_length(0) {}

	Line::Line(const char* label, unsigned int length) : LblShape(label), m_length(length) {}

	void Line::getSpecs(std::istream& istr) {
		LblShape::getSpecs(istr);
		istr >> m_length;
		istr.ignore(1000, '\n');
	}

	void Line::draw(std::ostream& ostr) const {
		if (m_length > 0 && label() != nullptr) {
			ostr << label() << std::endl;
			for (unsigned int i = 0; i < m_length; i++) {
				ostr << '=';
			}
		}
	}
}