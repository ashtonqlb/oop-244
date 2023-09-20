/***********************************************************************
// OOP244 Workshop #2 DIY (part 2):
//
// File  Population.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//   To completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#include <iostream>
#include <cstring>
#include "Population.h"
#include "File.h"

#define _CRT_SECURE_NO_WARNINGS

namespace sdds {

	int noOfPostcodes;
	Postcode* postcodes;

	bool startsWith(const char* cstring, const char* subString) {
	  return std::strstr(cstring, subString) == cstring;
	}
	
	bool load(const char* filename) {
		bool ok = false;
        int i = 0;
		if (openFile(DATAFILE)) {
			noOfPostcodes = sizeOfList();
			postcodes = new Postcode[noOfPostcodes];

			for (i = 0; i < noOfPostcodes; i++) {
				load(postcodes[i]);
			}

			if (i != noOfPostcodes) {
				std::cout << "Error: incorrect number of records read; the data is possibly corrupted" << std::endl;
			}

			else ok = true;
			
			closeFile();
		}

		return ok;
	}

	bool load(Postcode& postcode) {
		bool ok = read(postcode.m_token) && read(postcode.m_population);
		return ok;
	}

	void display() {
	    std::cout << "Population Report\n-----------------" << std::endl;

	    if (!postcodes) {
	        if (!load(DATAFILE)) {
	            std::cout << "Could not open data file: " << DATAFILE << std::endl;
	            return;
	        }
	    }

	    while (true) {
	        bool found = false;
	        char userInput[4];

	        std::cout << "Enter postal code:\n> ";
	        std::cin >> userInput;

	        if (userInput[0] == '!') {
	            break;
	        }

	        std::cout << "Postal Code: population" << std::endl << "-------------------------" << std::endl;
	        unsigned int totalPopulation = 0;
	        int displayCount = 1;

	        if (strcmp(userInput, "all") == 0) {
	            for (int i = 0; i < noOfPostcodes; i++) {
	                std::cout << displayCount << "- ";
	                display(postcodes[i]);
	                totalPopulation += postcodes[i].m_population;
	                displayCount++;
	            }
	        } else {
	            while (!found) {
	                for (int i = 0; i < noOfPostcodes; i++) {
	                    if (startsWith(postcodes[i].m_token, userInput)) {
	                        std::cout << displayCount << "- ";
	                        display(postcodes[i]);
	                        totalPopulation += postcodes[i].m_population;
	                        displayCount++;
	                    }
	                }
	                found = true;
	            }
	        }

	        std::cout << "-------------------------" << std::endl << "Population of the listed areas: " << totalPopulation << std::endl;
	    }
}	
	void display(const Postcode& pc) {
		std::cout << pc.m_token << ": " << pc.m_population << std::endl;
	}

	void deallocateMemory() {
	    for (int i = 0; i < noOfPostcodes; i++) {
	        delete[] postcodes[i].m_token;
	    }

	    delete[] postcodes; 
	    postcodes = nullptr;
	}
}
