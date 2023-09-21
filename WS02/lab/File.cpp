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

	void closeFile() { if (fptr) fclose(fptr); }


	bool read(char* &name) {
		name = nullptr;

		char nameStr[128];

		if (fscanf(fptr, "%[^\n]\n)", nameStr) == 1) { // this reads the whole line
			name = new char[strlen(nameStr) + 1];

			if (strcpy_s(name, strlen(nameStr) + 1, nameStr) == 0) {
				return true; 
			}
			delete[] name;
			name = nullptr;
		}
		return false;
	}

	bool read(int &employeeNumber) {
		return fscanf(fptr, "%d,", &employeeNumber) == 1;
	}

	bool read(double &salary) {
		return fscanf(fptr, "%lf,", &salary) == 1;
	}
}
