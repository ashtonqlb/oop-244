#ifndef SDDS_LARGESTOBJ_H
#define SDDS_LARGESTOBJ_H

#include <iostream>
#include <algorithm>

namespace sdds {
    template <class T, int N, char C>
    class largestObj {
        T array[N];
        char errorCode = C;
    public:
		void setArray(const T* values) {
	        for (int i = 0; i < N; i++) {
	            array[i] = values[i];
	        }
	    }

        T returnLargestObject() {
            if (N <= 0) {
                std::cerr << errorCode << std::endl;
            }

            const int n = sizeof(array) / sizeof(array[0]);

            if (N > n) {
                std::cerr << "Invalid array size (N > actual size)." << std::endl;
            }

            std::sort(array, array + N);

            return array[N - 1];
        }
    };
}

#endif
