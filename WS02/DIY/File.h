/***********************************************************************
// OOP244 Workshop #2 DIY (part 2):
//
// File  File.h
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//   To completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#ifndef SDDS_FILE_H_
#define SDDS_FILE_H_
namespace sdds {
	bool openFile(const char filename[]);

	bool read(char* &postalCode);
	bool read(unsigned int &population);

	void rewindFile();

	int sizeOfList(); // dynamic memory that stores the size of the csv

	void closeFile();
}
#endif // !SDDS_FILE_H_
