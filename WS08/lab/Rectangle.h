#ifndef SDDS_RECTANGLE_H
#define SDDS_RECTANGLE_H

#include "LblShape.h"

namespace sdds {
	class Rectangle : public LblShape {
		unsigned int m_width;
		unsigned int m_height;
	public:
		Rectangle();
		Rectangle(const char* label, unsigned int height, unsigned int width);
		void getSpecs(std::istream& istr) override;
		void draw(std::ostream& ostr) const override;
	};
}
#endif