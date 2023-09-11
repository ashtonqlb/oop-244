#ifndef SDDS_PHONE_H
#define SDDS_PHONE_H

namespace sdds {
	class Contact {
		char name[50];

		int areaCode;
		int prefix;
		int number;
	};

	void phoneDir(const char* programTitle, const char* fileName);
	Contact search(char token); //Take in user inputted token, return phone record, otherwise, return nowt
}

#endif 