#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>

#include "Date.h"
#include "Item.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expiry_date;
		char* m_handling_instructions = nullptr;
	public:
		Perishable() : m_expiry_date() {}
		Perishable(const Perishable& other);

		const Date& expiry() override;
		const char* handling_instructions() override;

		Perishable& operator=(const Perishable& other);
		operator bool() const override;

		~Perishable() override;

		int readSku(std::istream& istr) override;

		std::ofstream& save(std::ofstream& ofstr) override;
		std::ostream& display(std::ostream& ostr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
		std::istream& read(std::istream& istr) override;

		friend std::ostream& operator<<(std::ostream& ostr, const Perishable& perishable_item) { return perishable_item.display(ostr); };
		friend std::istream& operator>>(std::istream& istr, Perishable& perishable_item) { return perishable_item.read(istr); }; 
	};
}

#endif //SDDS_PERISHABLE_H
