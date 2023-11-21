#include <iostream>
#include <cstring>

template <typename T> T sum(const T a, const T b) {
	return a + b;
}

template <typename T> T divide_by_two(const T a) {
    return a / 2;
}

template <class T, int N>
class Array {
    T a[N];
public:
    T& operator[](int i) { return a[i]; }
};