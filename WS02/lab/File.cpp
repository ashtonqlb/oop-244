/***********************************************************************
// OOP244 Workshop #2 lab (part 1)
//
// File  File.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//    To be completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include "File.h"

namespace sdds {
    FILE* fptr;

    bool openFile(const char filename[]) {
        fptr = fopen(filename, "r");
        return fptr != NULL;
    }

    int noOfRecords() {
        int noOfRecs = 0;
        char ch;
        while (fscanf(fptr, "%c", &ch) == 1) {
            noOfRecs += (ch == '\n');
        }
        rewind(fptr);
        return noOfRecs;
    }

    void closeFile() {
        if (fptr) fclose(fptr);
    }

    bool read(char*& name) {
        char str[128]{};
        if (fscanf(fptr, "%127[^\n]\n", str)) {
            name != nullptr ? delete[] name : void();
            name = new char[strlen(str) + 1];
            int j = 0;
            for (int i = 0; str[i]; i++) {
                if (str[i] != ',') {
                    name[j++] = str[i];
                }
            }
            name[j] = '\0';
        }
        return name[0] != '\0';
    }

    bool read(int& employeeNumber) {
        return fscanf(fptr, "%d,", &employeeNumber);
    }

    bool read(double& salary) {
        return fscanf(fptr, "%lf\n", &salary);
    }
}