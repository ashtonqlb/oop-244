#ifndef SDDS_LABELSHAPE_H
#define SDDS_LABELSHAPE_H

#include <iostream>
#include <cstring>
#include "Shape.h"

namespace sdds {
	class LblShape : public Shape {
		char* m_label;
	public:
		LblShape();
		LblShape(const char* label);
		virtual ~LblShape();
		void getSpecs(std::istream& istr) override;
		const char* label() const;

		LblShape(const LblShape&) = delete;
		LblShape& operator=(const LblShape&) = delete;
		void draw(std::ostream& ostr) const override = 0;
	};
}
#endif 