namespace sdds {

	template <typename arrayType, typename keyType>
	int* select(const arrayType array[], keyType key, size_t size) {
	    int* indices = new int[size + 1];
	    int count = 0;
	    for (size_t i = 0; i < size; ++i) {
	        if (array[i] == key) {
	            indices[count++] = static_cast<int>(i);
	        }
	    }
	    indices[count] = -1; // Terminator
	    return indices;
	}

	template <typename arrayType>
	void csvDisplaySelection(const char* title, const arrayType array[], const int* indices) {
	    std::cout << title;
	    if (indices == nullptr || indices[0] == -1) {
	        std::cout << "Empty Selection" << std::endl;
	        return;
	    }
	    for (int i = 0; indices[i] != -1; ++i) {
	        if (i > 0) std::cout << ", ";
	        std::cout << array[indices[i]];
	    }
	    std::cout << std::endl;
	}
} 
