#ifndef SDDS_COW_H
#define SDDS_COW_H
#include "Animal.h"

namespace sdds {
	class Cow : public Animal {
	public:
		Cow() : Animal(4, "Cow") {}
		~Cow() override;
		const char* makeSound() override;
	};
}

#endif