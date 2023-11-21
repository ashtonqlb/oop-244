#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

constexpr auto READ_ITEM_ERR_MSG = "Console entry failed!";
constexpr auto MAX_ITEMS_NEEDED = 9999;
constexpr auto MAX_DESC_LENGTH = 35;
constexpr auto MAX_LINEAR_DESCRIPTION_SIZE = 360;

#include <iostream>
#include <fstream>
#include <cstring>

#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		const char* m_description;
		bool m_display_type; // false = Linear | true = Descriptive
		double m_price;
		int m_quantity_available;
		int m_quantity_needed;
	protected:
		Status m_status;
		int m_sku;

		bool linear() { return m_display_type; };

	public:
		Item() : m_description(nullptr), m_display_type(false), m_price(0.0), m_quantity_available(0), m_quantity_needed(0), m_sku(0) {};	
		Item(const Item& other);
		Item& operator=(const Item& other);
		virtual ~Item();

		virtual int qtyNeeded() const override;
		virtual int qty() const override;
		virtual operator double() const override;
		virtual operator bool() const override;
		virtual int operator-=(int qty) override;
		virtual int operator+=(int qty) override;
		virtual void linear(bool display_type) override;

		void clear();

		virtual bool operator==(int sku) const override;
		virtual bool operator==(const char* description) const override;

		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::istream& read(std::istream& istr) override;

		virtual int readSku(std::istream& istr) override;

		friend std::ostream& operator<<(std::ostream& ostr, const Item& item);
        friend std::istream& operator>>(std::istream& istr, Item& item);
	};
}

#endif 