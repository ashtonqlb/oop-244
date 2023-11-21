#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include "templates.cpp"

char increment_character(const char c) {
    unsigned int convert = static_cast<unsigned int>(c);
    convert++;
    return static_cast<char>(convert);
}

void increment_string(char* string_to_convert) {
    auto length = strlen(string_to_convert);
    for (unsigned int i = 0; i < length; i++) {
        string_to_convert[i] = increment_character(string_to_convert[i]);
    }
}

int main() {
	char* string_test = nullptr;

	double var1 = 5;
	double var2 = 4.3;

	int var3 = 4;
	int var4 = 6;

	std::cout.precision(2);

	std::cout << sum(var1, var2) << std::endl;
	std::cout << sum(var3, var4) << std::endl;
	// You cannot mix types without casting
	std::cout << sum(var1, static_cast<double>(var3)) << std::endl;
	// In this case, you can either cast int->double or double->int
	std::cout << sum(static_cast<int>(var2), var4) << std::endl;

	std::cout << divide_by_two(var1) << std::endl;
	std::cout << divide_by_two(var4) << std::endl;

	string_test = new char[strlen("Hello World") + 1];
	strcpy(string_test, "Hello World");

	std::cout << string_test << std::endl;

	increment_string(string_test);

	std::cout << string_test << std::endl << "Loop test!\n";

	for (unsigned int i = 0; i < 10; i++) {
		increment_string(string_test);
		std::cout << string_test << std::endl;
	}
}