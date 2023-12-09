#include <iostream>

#include "Book.h"
#include "Cow.h"
#include "Snake.h"
#include "LargestObj.h"
#include "Shape.h"

template <typename T>
void swapRight(T& obj1, T& obj2) {
	T tempObj;
	tempObj = obj1;
	obj1 = obj2;
	obj2 =  tempObj;
}

template <typename T>
void swapLeft(T& obj1, T& obj2) {
	T tempObj;
	tempObj = obj2;
	obj2 = obj1;
	obj1 =  tempObj;
}

const std::ostream& swapTester(std::ostream& ostr) {
	float floatTest1 = 5.3f;
	float floatTest2 = 3.5f;

	char charTest1 = 'a';
	char charTest2 = 'b';

	ostr << floatTest1 << ' ' << floatTest2 << std::endl;
    swapLeft<float>(floatTest1, floatTest2); 
	ostr << floatTest1 << ' ' << floatTest2 << std::endl;
	swapRight<float>(floatTest1, floatTest2);
	ostr << floatTest1 << ' ' << floatTest2 << std::endl;

	ostr << charTest1 << ' ' << charTest2 << std::endl;
	swapLeft<char>(charTest1, charTest2);
	ostr << charTest1 << ' ' << charTest2 << std::endl;
	swapRight<char>(charTest1, charTest2);
	ostr << charTest1 << ' ' << charTest2 << std::endl;

	return ostr;
};

using namespace sdds;

int main() {
	Snake newSnake;
	Cow newCow;
	const Circle newCircle(3);
	const Rectangle newRectangle(5, 3);

	swapTester(std::cout);

	std::cout << newSnake.makeSound() << std::endl;
	std::cout << newCow.makeSound() << std::endl;

	largestObj<int, 5, 'i'> largestIntObj;
	largestObj<char, 5, 'c'> largestCharObj;

	constexpr int intArray[5] = {10, 5, 8, 20};
	largestIntObj.setArray(intArray);

	constexpr char charArray[5] = {'h', 'o', 'r', 's', 'e'};
	largestCharObj.setArray(charArray);

	std::cout << "Largest int object is: " << largestIntObj.returnLargestObject() << std::endl;
	std::cout << "Largest char object is: " << largestCharObj.returnLargestObject() << std::endl;

	std::cout << newCircle.area() << ' ' << newCircle.perimeter() << std::endl;
	std::cout << newRectangle.area() << ' ' << newRectangle.perimeter() << std::endl;

	Book newBook;
}