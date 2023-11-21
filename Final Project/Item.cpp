#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include "Utils.h"
#include "Item.h"

namespace sdds {
	Item::Item(const Item& other) {
		if (other.operator bool()) {
			m_description = new char[strlen(other.m_description) + 1];
			strcpy(const_cast<char*>(m_description), other.m_description);

			m_display_type = other.m_display_type;
			m_price = other.m_price;
			m_quantity_available = other. m_quantity_available;
			m_quantity_needed = other.m_quantity_needed;
			m_sku = other.m_sku;
		}
	    else {
	        m_description = nullptr;
	        m_display_type = false;
	        m_price = 0;
	        m_quantity_available = 0;
	        m_quantity_needed = 0;
	        m_sku = 0;
	    }
	}

	Item& Item::operator=(const Item& other) {
	    if (this == &other) {
	        return *this;
	    }

	    delete[] m_description;

	    if (other.operator bool()) {
	        m_description = new char[strlen(other.m_description) + 1];
	        strcpy(const_cast<char*>(m_description), other.m_description);

	        m_display_type = other.m_display_type;
	        m_price = other.m_price;
	        m_quantity_available = other.m_quantity_available;
	        m_quantity_needed = other.m_quantity_needed;
	        m_sku = other.m_sku;
	    }
	    else {
	        m_description = nullptr;
	        m_display_type = false;
	        m_price = 0;
	        m_quantity_available = 0;
	        m_quantity_needed = 0;
	        m_sku = 0;
	    }

	    return *this;
	}


	Item::~Item() {
		delete[] m_description;
	}

	int Item::qtyNeeded() const {
		return m_quantity_needed;
	}

	int Item::qty() const {
		return m_quantity_available;
	}

	Item::operator double() const {
		return m_price;
	}

	Item::operator bool() const {
		return (m_description && m_quantity_available >= 0 && m_quantity_needed >= 0 && m_price > 0 && m_sku > 0);
	}

	int Item::operator-=(int qty) {
		if (qty > 0 && qty < m_quantity_available) 
			return m_quantity_available - qty;
		else 
			return 0;
	}

	int Item::operator+=(int qty) {
		if (qty > 0) 
			return m_quantity_available + qty;
		else 
			return 0;
	}

	void Item::linear(bool display_type) {
		m_display_type = display_type;
	}

	void Item::clear() {
		m_status.clear();
	}

	bool Item::operator==(int sku) const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description) const {
		int M = strlen(description);
		int N = strlen(m_description);
	
		for (int i = 0; i <= N - M; i++) {
			int j;
	
			for (j = 0; j < M; j++)
				if (m_description[i + j] != description[j])
					break;
	
			if (j == M)
				return true;
		}

		return false;
	}	

	std::ofstream& Item::save(std::ofstream& ofstr) const {
		if (operator bool()) {
			ofstr << m_sku << '\t' << m_description << '\t' << m_quantity_available << '\t' << m_quantity_needed  << '\t';
			ofstr.precision(4);
			ofstr << m_price;
		}

		return ofstr;
	}

	std::ostream& Item::display(std::ostream& ostr) const {
		ostr.clear();

		if (m_status) {
			const double purchase_fund = m_price * m_quantity_needed;

			if (m_display_type) {
				char small_desc[37];

				for (int i = 0; i < 30; i++){
					small_desc[i] = m_description[i];
				}

				ostr << m_sku << " | " << small_desc << " |" << m_quantity_available << " |" << m_quantity_needed << " |" << m_price;
			} else {
				ostr << "AMA Item:" << std::endl
					 << m_sku << ": " << m_description << std::endl
					 << "Quantity Needed: " << m_quantity_needed << std::endl
					 << "Quantity Available: " << m_quantity_available << std::endl
					 << "Needed Purchase Fund: $" << ostr.precision(4) << purchase_fund << std::endl;
			}
		} 
		else ostr << m_status;

		return ostr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
	    char temp[MAX_LINEAR_DESCRIPTION_SIZE];

	    delete[] m_description;
	    m_description = nullptr;

	    int sku, qtyAvailable, qtyNeeded;
	    double price;

	    ifstr >> sku;

	    ifstr.getline(temp, MAX_LINEAR_DESCRIPTION_SIZE, '\t');
	    m_description = new char[strlen(temp) + 1];
	    strcpy(const_cast<char*>(m_description), temp);

	    ifstr >> qtyAvailable;
	    ifstr.ignore(1000, '\t');
	    ifstr >> qtyNeeded;
	    ifstr.ignore(1000, '\t');
	    ifstr >> price;
	    ifstr.ignore();

	    if (ifstr.fail()) {
	        m_status = "Input file stream read failed!";
	    } else {
	        m_sku = sku;
	        m_quantity_available = qtyAvailable;
	        m_quantity_needed = qtyNeeded;
	        m_price = price;
			clear();
	    }

	    return ifstr;
	}

	std::istream& Item::read(std::istream& istr) {
		clear();

		std::cout << "AMA Item" << std::endl;
		m_sku = readSku(istr);

	    delete[] m_description;
	    m_description = nullptr;

	    char temp[MAX_LINEAR_DESCRIPTION_SIZE];

	    std::cout << "Description: ";
		istr.clear();
		istr.ignore(1000, '\n');
	    istr.getline(temp, MAX_LINEAR_DESCRIPTION_SIZE);

	    m_description = new char[strlen(temp) + 1];

	    if (m_description) {
	        strncpy(const_cast<char*>(m_description), temp, MAX_LINEAR_DESCRIPTION_SIZE);
	    }

		m_quantity_needed = ut.get_int(1, MAX_ITEMS_NEEDED, "Quantity Needed: ", READ_ITEM_ERR_MSG);
		m_quantity_available = ut.get_int(0, m_quantity_needed, "Quantity On Hand: ", READ_ITEM_ERR_MSG);
		m_price = ut.get_double(0, 9999.00, "Unit Price: $", READ_ITEM_ERR_MSG);

		return istr;
	}

	int Item::readSku(std::istream& istr) {
		return ut.get_int(40000, 99999, "SKU: ");
	}

	std::ostream& operator<<(std::ostream& ostr, const Item& item) {
		return item.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, Item& item) {
		return item.read(istr);
	}

}
