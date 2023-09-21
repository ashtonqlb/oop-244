#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "File.h"

namespace sdds {
    FILE* fptr;

    bool openFile(const char filename[]) {
        fptr = fopen(filename, "r");
        return fptr != NULL;
    }

    void closeFile() {
        if (fptr) fclose(fptr);
    }

    bool read(char*& postalCode) {
        postalCode = new char[4];
        bool result = fscanf(fptr, "%3s, ", postalCode) == 1;

        if (!result) {
            delete[] postalCode;
            postalCode = nullptr;
        }
        return result;
    }

    bool read(unsigned int& population) {
        return fscanf(fptr, "%u, ", &population) == 1;
    }

    void rewindFile() {
        if (fptr) {
            rewind(fptr);
        }
    }

    int sizeOfList() {
        int entries = 0;
        char ch;

        while (fscanf(fptr, "%c", &ch) == 1) {
            entries += (ch == '\n');
        }

        rewind(fptr);
        return entries;
    }
}
