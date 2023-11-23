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
		m_description = nullptr;
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
			return m_quantity_available -= qty;
		else 
			return 0;
	}

	int Item::operator+=(int qty) {
		if (qty > 0) 
			return m_quantity_available += qty;
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
	    if (m_status) {
	        if (m_display_type) {
				ostr << std::setfill(' ');
	            char small_desc[MAX_DESC_LENGTH + 1] = {};
	            std::strncpy(small_desc, m_description, MAX_DESC_LENGTH);

	            ostr << std::left << std::setw(6) << m_sku << "| " << std::setw(35) << small_desc << " | " << std::right << std::setw(4) << m_quantity_available << " | " << std::setw(4) << m_quantity_needed << " |" << std::setw(8) << std::fixed << std::setprecision(2) << m_price << " | ";
	        }

		    else {
	            ostr << std::left << "AMA Item:" << std::endl
		    		 << m_sku << ": " << m_description << std::endl
	                 << "Quantity Needed: " << m_quantity_needed << std::endl
	                 << "Quantity Available: " << m_quantity_available << std::endl
				     << "Unit Price: $" << m_price << std::endl
	                 << "Needed Purchase Fund: $"
	                 << std::fixed << std::setprecision(2) << m_price * (m_quantity_needed - m_quantity_available) << std::endl;
	        }
	    }
		else {
	        ostr << m_status;
	    }
		return ostr;
	}


	std::ifstream& Item::load(std::ifstream& ifstr) {
	    delete[] m_description;
	    m_description = nullptr;

	    int sku, qty_available, qty_needed;
	    double price;

	    ifstr.clear();

	    ifstr >> sku;
	    ifstr.ignore(1000, '\t');

		char* temp = ut.get_cstring(ifstr, READ_ITEM_ERR_MSG, '\t');
	    if (temp == nullptr || ifstr.fail()) {
	        m_status = "Input file stream read failed!";
	        delete[] temp;
	        return ifstr;
	    }

	    ifstr >> qty_available;
	    ifstr.ignore(1000, '\t');

	    ifstr >> qty_needed;
	    ifstr.ignore(1000, '\t');

	    ifstr >> price;
	    ifstr.ignore(1000, '\n');

	    m_description = new char[std::strlen(temp) + 1];
	    strcpy(const_cast<char*>(m_description), temp);
	    delete[] temp;

	    m_sku                = sku;
	    m_quantity_available = qty_available;
	    m_quantity_needed    = qty_needed;
	    m_price              = price;
	    clear();

	    return ifstr;
	}


	std::istream& Item::read(std::istream& istr) {
		clear();

		std::cout << "AMA Item:" << std::endl;
		m_sku = readSku(istr);

	    delete[] m_description;
	    m_description = nullptr;

		istr.clear();
		istr.ignore(1000, '\n');
		char* temp = ut.get_cstring("Description: ");

	    if (temp != nullptr) {
			m_description = new char[std::strlen(temp) + 1];
			strcpy(const_cast<char*>(m_description), temp);
			delete[] temp; 
	    }
		std::cout << "Quantity Needed: ";
		m_quantity_needed = ut.get_int(1, MAX_ITEMS_NEEDED);
		std::cout << "Quantity On Hand: ";
		m_quantity_available = ut.get_int(0, m_quantity_needed);
		std::cout << "Unit Price: $";
		m_price = ut.get_double(0, 9999.00);

		return istr;
	}

	int Item::readSku(std::istream& istr) {
		std::cout << "SKU: ";
		return ut.get_int(40000, 99999);
	}

	std::ostream& operator<<(std::ostream& ostr, const Item& item) {
		return item.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, Item& item) {
		return item.read(istr);
	}

}
