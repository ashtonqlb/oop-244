#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

constexpr auto READ_ITEM_ERR_MSG = "Console entry failed!";
constexpr auto MAX_ITEMS_NEEDED = 9999;
constexpr auto MAX_DESC_LENGTH = 35;

#include <iostream>
#include <fstream>
#include <cstring>

#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		const char* m_description = nullptr;
		bool m_display_type = false;
		double m_price = 0.00;
		int m_quantity_available = 0;
		int m_quantity_needed = 0;
	protected:
		Status m_status;
		int m_sku = 0;

		bool linear() const { return m_display_type; };

	public:
		Item() : m_description(nullptr), m_display_type(false), m_price(0.0), m_quantity_available(0), m_quantity_needed(0), m_sku(0) {};	
		Item(const Item& other);
		Item& operator=(const Item& other);
		virtual ~Item();

		int qtyNeeded() const override;
		int qty() const override;
		operator double() const override;
		operator bool() const override;
		int operator-=(int qty) override;
		int operator+=(int qty) override;
		void linear(bool display_type) override;

		void clear();

		bool operator==(int sku) const override;
		bool operator==(const char* description) const override;

		std::ofstream& save(std::ofstream& ofstr) const override;
		std::ostream& display(std::ostream& ostr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
		std::istream& read(std::istream& istr) override;

		int readSku(std::istream& istr) override;

		friend std::ostream& operator<<(std::ostream& ostr, const Item& item);
        friend std::istream& operator>>(std::istream& istr, Item& item);
	};
}

#endif 