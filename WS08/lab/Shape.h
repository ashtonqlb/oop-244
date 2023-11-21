#ifndef SDDS_SHAPE_H
#define SDDS_SHAPE_H

#include <iostream>

namespace sdds {
	class Shape {
	public:
		virtual ~Shape() {};
		virtual void draw(std::ostream& ostr) const = 0;
		virtual void getSpecs(std::istream& istr) = 0;

		friend std::ostream& operator<<(std::ostream& ostr, const Shape& shape) {
			shape.draw(ostr);
			return ostr;
		};
		friend std::istream& operator>>(std::istream& istr, Shape& shape) {
			shape.getSpecs(istr);
			return istr;
		};
	};
}
#endif