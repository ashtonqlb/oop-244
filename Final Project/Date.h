#ifndef SDDS_DATE_H
#define SDDS_DATE_H

constexpr int MAX_YEAR_VALUE = 2030;
constexpr int MAX_MONTH_VALUE = 12;
constexpr int MIN_VALUE = 1;

#include "Status.h"

namespace sdds {
	class Date {
		int m_year = 0;
		int m_month = 0;
		int m_day = 0;
		Status m_state;
		bool m_format = true;

		bool isSet = false;

		bool validate();
		int unique_date_value() const;
	public:
		Date();
		Date(int date_value);
		Date(int year, int month, int day);
		bool operator==(Date& other) const;
		bool operator!=(const Date& other) const;
		bool operator<(Date& other) const;
		bool operator>(Date& other) const;
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;

		operator bool() const;

		const Status& state() const;

		Date& formatted(bool f);

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ifstream& load(std::ifstream& ifstr);

		friend std::ostream& operator<<(std::ostream& ostr, const Date& date);
		friend std::istream& operator>>(std::istream& istr, Date& date);
	};
}

#endif 