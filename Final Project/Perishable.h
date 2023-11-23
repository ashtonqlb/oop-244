#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H


#include <iostream>
#include <fstream>
#include <cstring>

#include "Date.h"
#include "Item.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expiry_date;
		const char* m_handling_instructions;
	public:
		Perishable() : Item(), m_expiry_date(0, 0, 0), m_handling_instructions(nullptr){};
		Perishable(Perishable& other);

		const Date& expiry ();

		Perishable& operator=(const Perishable& other);
		operator bool() const override;

		~Perishable() override;

		int readSku(std::istream& istr) override;

		std::ofstream& save(std::ofstream& ofstr) const override;
		std::ostream& display(std::ostream& ostr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
		std::istream& read(std::istream& istr) override;

		friend std::ostream& operator<<(std::ostream& ostr, const Perishable& perishable_item) { return perishable_item.display(ostr); };
		friend std::istream& operator>>(std::istream& istr, Perishable& perishable_item) { return perishable_item.read(istr); }; 
	};
}

#endif SDDS_PERISHABLE_H