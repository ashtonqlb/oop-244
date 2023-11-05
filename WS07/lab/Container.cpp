#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "Container.h"

namespace sdds {
	void Container::setEmpty() {
		m_content[0] = '\0';
		m_capacity = 0;
		m_volume = 0;
	}

	int Container::capacity() const {
		return m_capacity;
	}

	int Container::volume() const {
		return m_volume;
	}

	Container::Container(const char* content, int capacity, int volume) : m_capacity(capacity), m_volume(volume) {
		if (content != nullptr) {
			std::strncpy(m_content, content, MAX_CONTENT_SIZE);
			m_content[MAX_CONTENT_SIZE - 1] = '\0';
		}
		else setEmpty();
		
		if (volume > capacity) setEmpty();
	}

	int Container::operator+=(int value) {
		if (operator bool()) {
			int space = m_capacity - m_volume;
			int to_add = (value <= space) ? value : space;
			m_volume += to_add;

			return to_add;
		}

		else return 0;
	}

	int Container::operator-=(int value) {
		if (operator bool()) {
			int to_remove = (value <= m_volume) ? value : m_volume;
			m_volume -= to_remove;
			return to_remove;
		}

		else return 0;
	}

	Container::operator bool() const {
		return m_content[0] != '\0' && m_volume <= m_capacity;
	}

	void Container::clear(int capacity, const char* content) {
		if (capacity && content && strlen(content) > 0) {
			this->~Container();
			new (this) Container(content, capacity);
		}
		else setEmpty();
	}

	std::ostream& Container::print(std::ostream& ostr) const {
		if (*this) {
			ostr << m_content << ": (" << m_volume << "cc/" << m_capacity << ")";
		}
		else {
			ostr << "****: (**cc/***)";
		}

		return ostr;
	} 

	std::istream& Container::read(std::istream& istr) {
		if (!(*this)) {
			std::cout << "Broken Container, adding aborted! Press <ENTER> to continue...." << std::endl;
			istr.ignore(1000, '\n');
			return istr;
		}

		print(std::cout);
		std::cout << "\n> ";

		int amount;
		while (!(istr >> amount) || amount < 1) {
			istr.clear();
			istr.ignore(1000, '\n');
			std::cout << "Invalid amount, retry: ";
		}

		int added_amount = *this += amount;
		std::cout << "Added " << added_amount << " CCs" << std::endl;

		return istr;
	}


	std::ostream& operator<<(std::ostream& ostr, Container& C) {
		return C.print(ostr);
	}

	std::istream& operator>>(std::istream& istr, Container& C) {
		return C.read(istr);
	}
}