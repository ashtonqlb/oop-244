#ifndef SDDS_GRADUATE_H
#define SDDS_GRADUATE_H

#include "Student.h"

namespace sdds {
	class Graduate : public Student {
		char* m_thesis_title;
		char* m_supervisor_name;
	public:
		Graduate() : Student(), m_thesis_title(nullptr), m_supervisor_name(nullptr) {}
		Graduate(const char* name, int age, const char* title = nullptr, const char* supervisor = nullptr);
		Graduate(const Graduate& other);
		Graduate& operator=(const Graduate& other);

		 ~Graduate() override { delete[] m_thesis_title; delete[] m_supervisor_name; }

		void display() const override;
	};
}

#endif