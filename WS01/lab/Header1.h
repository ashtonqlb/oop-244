#ifndef SDDS_SOLIDCALCULATOR_H
#define SDDS_SOLIDCALCULATOR_H

namespace sdds {
    template <typename T>
    class SolidCalculator {
        T& udd1;
        T& udd2;

    public:
        SolidCalculator(T& u1, T& u2) : udd1(u1), udd2(u2) {}

        T CalculateSquareArea(const T& input1, const T& input2) {
            return input1 * input2;
        }

        T CalculateTriangleArea(const T& input1, const T& input2) {
            return (input1 * input2) / 2;
        }
    };
}

#endif SDDS_SOLIDCALCULATOR_H