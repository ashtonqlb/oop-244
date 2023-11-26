#include <iostream>
#include <iomanip>

#include "Date.h"
#include "Utils.h"

namespace sdds {
	bool Date::validate() {
		int current_year;

		ut.getSystemDate(&current_year);

		if (m_year == -1 || m_month == -1 || m_day == -1) {
			isSet = false;
			std::cout << "Invalid date value";
			return false;
		}

		if (m_year < current_year|| m_year > MAX_YEAR_VALUE) {
			isSet = false;
			m_state = "Invalid year in date";
			m_state = 1;
			return false;
		}
		
		if (m_month < MIN_VALUE || m_month > MAX_MONTH_VALUE) {
			isSet = false;
			m_state = "Invalid month in date";
			m_state = 2;
			return false;
		}

		if (m_day < MIN_VALUE || m_day > ut.daysOfMon(m_month, m_year)) {
			isSet = false;
			m_state = "Invalid day in date";
			m_state = 3;
			return false;
		}

		isSet = true;
		m_state.clear();
		return true;
	}

	int Date::unique_date_value() const {
		return m_year * 372 + m_month * 31 + m_day;
	}

	Date::Date() {
		int year, month, day;

		ut.getSystemDate(&year, &month, &day);

		m_year = year;
		m_month = month;
		m_day = day;
	}

	Date::Date(int date_value) {
		int current_year;
		ut.getSystemDate(&current_year);

	    if (date_value >= 10000000) {  // 8 digits, e.g., 20230101 for January 1, 2023
	        m_year = date_value / 10000; // Extracts YYYY part
	        m_month = (date_value / 100) % 100; // Extracts MM part
	        m_day = date_value % 100; // Extracts DD part
			isSet = true;
	    }

	    else if (date_value >= 10000) {  // 6 digits, e.g., 230101 for January 1, 2023
	        m_year = 2000 + (date_value / 10000); // Assumes 2000s, extracts YY part
	        m_month = (date_value / 100) % 100; // Extracts MM part
	        m_day = date_value % 100; // Extracts DD part
			isSet = true;
	    }

	    else if (date_value >= 101) { // 4 digits, e.g., 0101 for January 1
	        m_year = current_year;
	        m_month = date_value / 100; // Extracts MM part
	        m_day = date_value % 100; // Extracts DD part
			isSet = true;
	    }
		else {
			int year, month, day;
			ut.getSystemDate(&year, &month, &day);

			m_year = year;
			m_month = month;
			m_day = day;
			isSet = false;
		}
	}

	Date::Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day) {
		validate();
	}

	bool Date::operator==(Date& other) const {
		return unique_date_value() == other.unique_date_value();
	}

	bool Date::operator!=(const Date& other) const {
		return !(*this == other);
	}

	bool Date::operator<(Date& other) const {
		return unique_date_value() < other.unique_date_value();
	}

	bool Date::operator>(Date& other) const {
		return unique_date_value() > other.unique_date_value();
	}

	bool Date::operator<=(const Date& other) const {
		return !(*this > other);
	}

	bool Date::operator>=(const Date& other) const {
		return !(*this < other);
	}

	Date::operator bool() const {
		return state() && isSet;
	}

	const Status& Date::state() const {
		return m_state;
	}

	Date& Date::formatted(bool f) {
		m_format = f;
		return *this;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		if (m_format) 
			ostr << std::setfill('0') << std::setw(4) << m_year << "/" << std::setw(2) << std::right << m_month << "/" << std::setw(2) << m_day;
		else 
			ostr << std::setfill('0') << std::setw(2) << m_year % 100  << std::setw(2) << m_month << std::setw(2) << m_day;
		return ostr;
	}

	std::istream& Date::read(std::istream& istr) {
		const int date_value = ut.get_int();

		const Date temp(date_value);

	    if (temp) {
	        *this = temp;
	    } else {
	        istr.setstate(std::ios::failbit);
	        m_state = "Invalid date format";
	    }

		return istr;
	}

	std::ifstream& Date::load(std::ifstream& ifstr) {
	    int date_value, current_year;

	    ut.getSystemDate(&current_year);

		ifstr.ignore(1000, '\t');
		ifstr.ignore(1000, '\t');
		ifstr.ignore(1000, '\t');
		ifstr.ignore(1000, '\t');
		ifstr.ignore(1000, '\t');

	    ifstr >> date_value;

	    if (ifstr.fail()) {
	        m_state = "Error reading date from file";
	        ifstr.setstate(std::ios::failbit);
	    } else {
	        if (date_value < 10000) {
	            m_year = current_year;
	            m_month = date_value / 100;
	            m_day = date_value % 100;
				isSet = true;
	        } else {
	            m_year = date_value / 10000;
	            m_month = (date_value / 100) % 100;
	            m_day = date_value % 100;
				isSet = true;
	        }

	        if (!validate()) {
	            ifstr.setstate(std::ios::failbit);
	        }
	    }

	    return ifstr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		return date.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Date& date) {
		return date.read(istr);
	}
}