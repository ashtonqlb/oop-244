/***********************************************************************
// OOP244 Workshop #2 DIY (part 2):
//
// File  Population.h
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//   To completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#ifndef SDDS_POPULATION_H_
#define SDDS_POPULATION_H_

#define DATAFILE "PCpopulations.csv"

namespace sdds {

	struct Postcode {
		char* m_token = nullptr;
		unsigned int m_population = 0;
	};

	bool startsWith(const char* cString, const char* subString);

	bool load(const char* filename);
	bool load(Postcode& postcode);

	void display();
	void display(const Postcode &pc);

	void deallocateMemory();

}
#endif // SDDS_POPULATION_H_