#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "iProduct.h"
#include "Menu.h"

constexpr static auto sdds_max_num_items = 100;

namespace sdds {
	class AidMan {
		char* m_filename = nullptr;
		int m_products_stored = 0;
		Menu m_main_menu;
		iProduct* m_products[sdds_max_num_items] {};

		unsigned int menu();
	public:
		AidMan();
		AidMan(const char* filename);
		~AidMan();
		AidMan(const AidMan& other) = delete;
		AidMan& operator=(const AidMan& other) = delete;

		bool load();
		int list(const char* sub_desc = nullptr) const;
		int search(int sku) const;
		void sort();
		void remove(int index);
		void create_shipping_order();
		void run();
		void save() const;
		void deallocate();

	};
}

#endif 