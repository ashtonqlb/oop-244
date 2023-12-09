#ifndef SDDS_SNAKE_H
#define SDDS_SNAKE_H

#include "Animal.h"
namespace sdds {
	class Snake : public Animal {
	public:
		Snake() : Animal(0, "Snake") {}
		~Snake() override;
		const char* makeSound() override;
	};	
}

#endif