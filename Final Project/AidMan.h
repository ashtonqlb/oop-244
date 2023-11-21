#include "Menu.h"
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

namespace sdds {
	class AidMan {
		char* m_filename;
		Menu m_main_menu;

		unsigned int menu();
	public:
		AidMan(const char* filename);
		~AidMan();

		AidMan(const AidMan& other) = delete;
		AidMan& operator=(const AidMan& other) = delete;

		void run();
	};
}

#endif 