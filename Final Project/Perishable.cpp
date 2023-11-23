#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "Date.h"
#include "Item.h"
#include "Perishable.h"

namespace sdds {
	Perishable::Perishable(Perishable& other) : Item::Item( other) {
		if(other.operator bool()) {
			m_handling_instructions = new char[strlen(other.m_handling_instructions) + 1];
			strcpy(const_cast<char*>(m_handling_instructions), other.m_handling_instructions);

			m_expiry_date = other.m_expiry_date;
		}
		else {
			m_handling_instructions = nullptr;
		}
	}

	const Date& Perishable::expiry() {
		return m_expiry_date;
	}

	Perishable& Perishable::operator=(const Perishable& other) {
		if (this == &other) {
	        return *this;
	    }

		if (other.operator bool()) {
	        m_handling_instructions = new char[strlen(other.m_handling_instructions) + 1];
	        strcpy(const_cast<char*>(m_handling_instructions), other.m_handling_instructions);

	        m_expiry_date = other.m_expiry_date;
	    }
	    else {
	        m_handling_instructions = nullptr;
	    }
		
		return *this;
	}

	Perishable::operator bool() const { 
		return Item::operator bool() && m_expiry_date && m_status;
	}

	sdds::Perishable::~Perishable() {
		Item::~Item();
		delete[] m_handling_instructions;
		m_handling_instructions = nullptr;
	}

	int Perishable::readSku(std::istream& istr) {
		std::cout << "SKU: ";
		return ut.get_int(10000 , 39999);
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		ofstr << '\n';
		Item::save(ofstr);

		if (operator bool()) {
			if (m_handling_instructions != nullptr){
				ofstr << '\t' << m_handling_instructions;
			}
			 ofstr << "\t\t" << m_expiry_date;
		}

		return ofstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
		Item::display(ostr);


		if (m_status) {
	        if (Item::linear()) {
				ostr << std::setfill(' ');
				ostr << m_expiry_date;
	        }
		    else {
	            ostr << "Expiry date: " << m_expiry_date << std::endl;
				if (m_handling_instructions != nullptr) {
					ostr << "Handling Instructions: " << m_handling_instructions << std::endl;
				}
	        }
	    }
		else {
	        ostr << m_status;
	    }

		return ostr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr);

		delete[] m_handling_instructions;
	    m_handling_instructions = nullptr;

		const char* temp = ut.get_cstring(ifstr, READ_ITEM_ERR_MSG, '\t');
		if (ifstr.fail()) {
	        m_status = "Input file stream read failed!";
	        delete[] temp;
	    }

		m_handling_instructions = new char[std::strlen(temp) + 1];
	    strcpy(const_cast<char*>(m_handling_instructions), temp);
	    delete[] temp;
		clear();

		m_expiry_date.read(ifstr);

		return ifstr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);

		delete[] m_handling_instructions;
	    m_handling_instructions = nullptr;

		std::cout << "Expiry Date (YYMMDD): ";
		std::cin >> m_expiry_date;

		if (istr.fail()) {
			m_status = "Date read failed!";
			m_expiry_date = 0;
		}

		std::cin.ignore(1000, '\n');

		std::cout << "Handling Instructions, ENTER to skip: ";
		const char* temp = ut.get_cstring("", READ_ITEM_ERR_MSG, '\n');
		if (istr.fail()) {
	        m_status = "Input file stream read failed!";
	        delete[] temp;
	    }

		m_handling_instructions = new char[std::strlen(temp) + 1];
	    strcpy(const_cast<char*>(m_handling_instructions), temp);
	    delete[] temp;
		clear();

		return istr;
	}
}
