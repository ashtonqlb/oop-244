#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>

#include "AidMan.h"
#include "Utils.h"

namespace sdds {

	AidMan::AidMan(const char* filename) : m_main_menu ("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		if (filename != nullptr) {
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		} else {
			m_filename = nullptr;
		}
	}

	AidMan::~AidMan() {	
		delete[] m_filename;
	}

	unsigned int AidMan::menu() {
		int year, month, day = 0;
	
		ut.getSystemDate(&year, &month, &day);

		std::cout << "Aid Management System" << std::endl;
		std::cout << "Date: " << std::setw(4) << year << '/' << std::setfill('0') << std::setw(2) << month << '/' << std::setfill('0') << std::setw(2) << day << std::endl;
		std::cout << "Data file: " << (m_filename ? m_filename : "No file") << std::endl << std::endl;

		return m_main_menu.run();
	}

	void AidMan::run() {
		unsigned int selection = 0;
		do {
			selection = menu();

			switch (selection) {
			case 1:
				std::cout << "\n****List Items****\n\n";
				break;
			case 2:
				std::cout << "\n****Add Item****\n\n";
				break;
			case 3:
				std::cout << "\n****Remove Item****\n\n";
				break;
			case 4:
				std::cout << "\n****Update Quantity****\n\n";
				break;
			case 5:
				std::cout << "\n****Sort****\n\n";
				break;
			case 6:
				std::cout << "\n****Ship Items****\n\n";
				break;
			case 7:
				std::cout << "\n****New/Open Aid Database****\n\n";
				break;
			default:
				break;
			}

		} while (selection != 0);

		std::cout << "Exiting Program!\n";
	}
}
