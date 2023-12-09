#include "Shape.h"

auto constexpr pi = 3.14;

namespace sdds {
	double Circle::area() const {
		return pi * (m_radius * m_radius);
	}

	double Circle::perimeter() const {
		return 2 * pi * m_radius;
	}

	double Rectangle::area() const {
		return m_length * m_width;
	}

	double Rectangle::perimeter() const {
		return 2 * (m_length + m_width);
	}

}
