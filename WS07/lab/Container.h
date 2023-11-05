#ifndef SDDS_CONTAINER_H
#define SDDS_CONTAINER_H

constexpr short MAX_CONTENT_SIZE = 50;

#include <iostream>

namespace sdds {
	class Container {
		char m_content[MAX_CONTENT_SIZE];
		int m_capacity;
		int m_volume;

	protected:
		void setEmpty();
		int capacity() const;
		int volume() const;
	public:
		Container(const char* content = nullptr, int capacity = 0, int volume = 0);
		int operator+=(int value);
		int operator-=(int value);
		operator bool() const;
		void clear(int capacity, const char* content);

		std::ostream& print(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);

		friend std::ostream& operator<<(std::ostream& ostr, const Container& C);
		friend std::istream& operator>>(std::istream& istr, Container& C);
	};
}

#endif