#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
	class Menu {
		char* m_menu_content;
		int m_option_count;

		void print_menu();
		int count_tabs(const char* menu_string);
	public:
		Menu(const char* menu_string);
		~Menu();

		Menu(const Menu& other) = delete;
		Menu& operator=(const Menu& other) = delete;

		unsigned int run();
	};
}

#endif 