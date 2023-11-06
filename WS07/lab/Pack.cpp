// OOP244 Workshop 07 
// Ashton Lunken 
// Student ID: 134128214
// No stealsies. This is my own work. I think.

#include "Pack.h"

namespace sdds {
	Pack::Pack(const char* content, int size, int unit_size, int num_of_units) : Container(content, size * unit_size, num_of_units * unit_size), m_unit_size(unit_size > 0 ? unit_size : 0) {
		if (unit_size <= 0) {
			Container::setEmpty();
		}
	}

	int Pack::operator+=(int units_to_add) {
		int amount_to_add = units_to_add * m_unit_size;
		int added_cc = Container::operator+=(amount_to_add);

		return added_cc / m_unit_size;
	}
	int Pack::operator-=(int units_to_remove) {
		int amount_to_remove = units_to_remove * m_unit_size;
		int removed_cc = Container::operator-=(amount_to_remove);

		return removed_cc / m_unit_size;
	}

	int Pack::unit() const {
		return m_unit_size;
	}

	int Pack::no_of_units() const {
		return volume() / m_unit_size;
	}

	int Pack::size() const {
		return capacity() / m_unit_size;
	}

	void Pack::clear(int size, int unit_size, const char* content) {
		if (unit_size > 0) {
			m_unit_size = unit_size;
			Container::clear(size * unit_size, content);
		}
		else Container::setEmpty();
	}

	std::ostream& Pack::print(std::ostream& ostr) const {
		if (*this) {
			Container::print(ostr);
			ostr << ", " << no_of_units() << " in a pack of " << size();
		}
		return ostr;
	}

	std::istream& Pack::read(std::istream& istr) {
		if (!(*this)) {
			std::cout << "Broken Container, adding aborted! Press <ENTER> to continue...." << std::endl;
			istr.ignore(1000, '\n');
			return istr;
		}
		
		int missing_units = size() - no_of_units();

		if (missing_units > 0) {

			std::cout << "Add to ";
			print(std::cout);
			std::cout << "\n> ";

			int units_to_add;

			while (!(istr >> units_to_add) || units_to_add < 1 || units_to_add > missing_units) {
				istr.clear();
				istr.ignore(1000, '\n');
				if (units_to_add > missing_units) {
					std::cout << "Value out of range [1<=val<=" << missing_units << "]: ";
				}
			}

			int added_units = *this += units_to_add;
			std::cout << "Added " << added_units << std::endl;
		} else {
			std::cout << "Pack is full!, Press <ENTER> to continue...." << std::endl;
			istr.ignore(1000, '\n');
		}

		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Pack& pack) {
		return pack.print(ostr);
	}

	std::istream& operator>>(std::istream& istr, Pack& pack) {
		return pack.read(istr);
	}
}
