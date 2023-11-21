#ifndef SDDS_LINE_H
#define SDDS_LINE_H

#include "LblShape.h"

namespace sdds {
	class Line : public LblShape {
		unsigned int m_length;
	public:
		Line();
		Line(const char* label, unsigned int length);
		void getSpecs(std::istream& istr) override;
		void draw(std::ostream& ostr) const override;
	};
}
#endif