#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <ostream>

namespace sdds {
	class Status {
		char* m_description;
		int m_code;
	public:
		Status(const char* description = "\0", int code = 0);
		Status(const Status& other);
		~Status();

		Status& operator=(const Status& other);
		Status& operator=(const char* description);
		Status& operator=(int status);

		Status& clear();

		operator int() const { return m_code; }
		operator const char* () const { return m_description; }
		operator bool() const { return m_description == nullptr || m_description == "\0"; }

		friend std::ostream& operator<<(std::ostream& os, const Status& status);
	};
}

#endif 