#ifndef SDDS_GRADUATE_H
#define SDDS_GRADUATE_H

#include "Student.h"

namespace sdds {
	class Graduate : public Student {
    char* thesisTitle;
    char* supervisorName;

	public:
	    Graduate() : Student(), thesisTitle(nullptr), supervisorName(nullptr) {}
	    Graduate(const char* name, int age, const char* thesisTitle, const char* supervisorName);
	    Graduate(const Graduate& other);
	    Graduate& operator=(const Graduate& other);

		~Graduate() override {
			delete[] thesisTitle;
			delete[] supervisorName;
		}

	    void display() const override;
	};
}

#endif