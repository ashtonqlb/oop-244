#ifndef SDDS_ANIMAL_H
#define SDDS_ANIMAL_H
namespace sdds {
	class Animal {
	protected:
		const char* m_name;
		int m_legs;
	public:
		Animal(int legs, const char* name);
		virtual ~Animal();
		virtual const char* makeSound() = 0;
	};

	inline Animal::Animal(int legs, const char* name) : m_name(name), m_legs(legs) {}

	inline Animal::~Animal() {
		if(m_name != nullptr) {
			delete[] m_name;
		}
	}
}

#endif