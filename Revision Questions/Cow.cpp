#include "Cow.h"

namespace sdds {
	Cow::~Cow() {
		Animal::~Animal();
	}

	const char* Cow::makeSound() {
		return "Moo!";
	}
}
