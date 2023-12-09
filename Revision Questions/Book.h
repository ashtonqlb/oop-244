#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <iostream>

namespace sdds {
	class Book {
	public:
		Book() {
			std::cout << "Book created\n";
		}

		~Book() {
			std::cout << "Book destroyed\n";
		}
	};
}

#endif