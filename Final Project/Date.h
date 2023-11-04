#ifndef SDDS_DATE_H
#define SDDS_DATE_H

constexpr int MAX_YEAR_VALUE = 2030;
constexpr int MAX_MONTH_VALUE = 12;
constexpr int MIN_VALUE = 1;

#include <iostream>

#include "Utils.h"
#include "Status.h"

namespace sdds {
	class Date {
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_format;

		bool validate();
		int unique_date_value();
	public:
		Date(int year = 0, int month = 0, int day = 0);

		bool operator==(Date& other);
		bool operator!=(const Date& other) const;
		bool operator<(Date& other);
		bool operator>(Date& other);
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;

		operator bool() const;

		const Status& state() const;

		Date& formatted(bool f);

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);

		friend std::ostream& operator<<(std::ostream& ostr, const Date& date);
		friend std::istream& operator>>(std::istream& istr, Date& date);
	};
}

#endif 