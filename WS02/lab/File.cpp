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
#define CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include "File.h"


namespace sdds
{
	FILE* fptr;

	bool openFile(const char filename[])
	{
		fptr = fopen(filename, "r");
		return fptr != NULL;
	}

	int noOfRecords()
	{
		int noOfRecs = 0;
		char ch;
		while (fscanf(fptr, "%c", &ch) == 1)
		{
			noOfRecs += (ch == '\n');
		}
		rewind(fptr);
		return noOfRecs;
	}

	void closeFile()
	{
		if (fptr) fclose(fptr);
	}


	bool read(char* &name) //TODO: Figure out why this function does not read the name properly
	{
	    char nameStr[128];
	    bool ok = fscanf(fptr, "%127[^\n]\n", nameStr) == 1;
	    if (ok) {
	        name = new char[strlen(nameStr) + 1];
	        strcpy(name, nameStr);
	        name[strlen(nameStr)] = '\0';
	    }
	    return ok;
	}

	bool read(int& employeeNumber)
	{
		return fscanf(fptr, "%d,", &employeeNumber);
	}

	bool read(double& salary)
	{
		return fscanf(fptr, "%lf,", &salary);
	}
}
