#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "Date.h"
#include "Item.h"
#include "Perishable.h"

#include "Utils.h"

namespace sdds {
	Perishable::Perishable(const Perishable& other) : Item((other)) {
		m_handling_instructions = nullptr;
		if(other.operator bool() && other.m_handling_instructions != nullptr) {
			delete[] m_handling_instructions;
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
	    if (this != &other) {
	        Item::operator=(other);
	        delete[] m_handling_instructions;
	        if (other.operator bool() && other.m_handling_instructions != nullptr) {
	            m_handling_instructions = new char[strlen(other.m_handling_instructions) + 1];
	            strcpy(const_cast<char*>(m_handling_instructions), other.m_handling_instructions);
	        } else {
	            m_handling_instructions = nullptr;
	        }
	        m_expiry_date = other.m_expiry_date;
	    }
	    return *this;
	}

	Perishable::operator bool() const {
		return m_expiry_date;
	}

	sdds::Perishable::~Perishable() {
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
			else {
				ofstr << "\t\t";
			}

			Date temp = m_expiry_date;
			temp.formatted(false);

			ofstr << "\t" << temp;
		}

		return ofstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
	    if (m_status) {
	        if (linear()) {				
					Item::display(ostr);
					if (m_handling_instructions != nullptr && std::strlen(m_handling_instructions) > 0 && std::strcmp(m_handling_instructions, "\n") != 0) {
						ostr << '*';
					} else {
						ostr << ' ';
					}

					ostr << m_expiry_date;
	        }
	        else {
	            std::cout << "Perishable ";
	            Item::display(ostr);
	            ostr << "Expiry date: " << m_expiry_date << std::endl;
	            if (m_handling_instructions != nullptr && std::strlen(m_handling_instructions) > 0 && std::strcmp(m_handling_instructions, "\n") != 0) {
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

	    ifstr.ignore(1000, '\t');

	    int temp_date_value;

	    delete[] m_handling_instructions;
	    m_handling_instructions = nullptr;

	    const char* temp = ut.get_cstring(ifstr, READ_ITEM_ERR_MSG, '\t');
	    if (ifstr.fail()) {
	        m_status = "Input file stream read failed!";
	        delete[] temp;
	        return ifstr;
	    }

	    if (temp != nullptr) {
	        m_handling_instructions = new char[std::strlen(temp) + 1];
	        strcpy(const_cast<char*>(m_handling_instructions), temp);
	        delete[] temp;
	    } else {
	        m_handling_instructions = nullptr;
	    }

	    clear();

	    ifstr >> temp_date_value;
	    m_expiry_date = temp_date_value;

	    ifstr.ignore(1000, '\n');

	    return ifstr;
	}


	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);

		delete[] m_handling_instructions;
	    m_handling_instructions = nullptr;

		std::cout << "Expiry date (YYMMDD): ";
		std::cin >> m_expiry_date;

		if (istr.fail()) {
			m_status = "Date read failed!";
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
