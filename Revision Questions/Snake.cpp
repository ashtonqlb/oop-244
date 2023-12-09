#include "Snake.h"

namespace sdds {
	Snake::~Snake() {
		Animal::~Animal();
	}

	const char* Snake::makeSound() {
		return "Hiss";
	}
}
