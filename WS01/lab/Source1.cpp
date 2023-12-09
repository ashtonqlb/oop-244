#include <iostream>
#include "Header1.h"


int main() {
    int intInput1 = 5;
    int intInput2 = 3;

    float floatInput1 = 3.5f;
    float floatInput2 = 5.3f;

    sdds::SolidCalculator<int> intCalculator(intInput1, intInput2);
    const int intResult = intCalculator.CalculateSquareArea(intInput1, intInput2);

    sdds::SolidCalculator<float> floatCalculator(floatInput1, floatInput2);
    const float floatResult = floatCalculator.CalculateSquareArea(floatInput1, floatInput2);

    std::cout << intResult << std::endl << floatResult;

    return 0;
}