#include <iostream>
#include "HealthCard.h"
using namespace std;
namespace sdds {

	bool HealthCard::validID(const char* name, long long number, const char vCode[], const char sNumber[]) const {
		return false;
	}

	void HealthCard::setEmpty() {
		char* m_name = nullptr;
		m_number = 0;
		strcpy(m_vCode, "/0");
		strcpy(m_sNumber, "/0");
	}

	void HealthCard::allocateAndCopy(const char* name) {
	}

	void HealthCard::extractChar(std::istream& istr, char ch) const {
	}

	std::ostream& HealthCard::printIDInfo(std::ostream& ostr) const {
		// TODO: insert return statement here
	}

	void HealthCard::set(const char* name, long long number, const char vCode[], const char sNumber[]) {
	}

	HealthCard& HealthCard::operator=(const HealthCard& hc) {
		// TODO: insert return statement here
	}

	HealthCard::~HealthCard() {
	}

	HealthCard::operator bool() {
	}

	std::ostream& HealthCard::print(std::ostream& ostr, bool toFile) const {
		// TODO: insert return statement here
	}

	std::istream& HealthCard::read(std::istream& istr) {
		// TODO: insert return statement here
	}

	std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc) {
		// TODO: insert return statement here
	}

	std::istream& operator>>(std::istream& istr, HealthCard& hc) {
		// TODO: insert return statement here
	}
}