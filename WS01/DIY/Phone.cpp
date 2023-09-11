#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Phone.h"
#include "cStrTools.h"

using namespace std;

namespace sdds {

	void phoneDir(const char* programTitle, const char* fileName) {

		char userInput;

		cout << programTitle << "phone direcotry search" << endl <<
			 "-------------------------------------------------------" << endl;

		ifstream file(fileName);

		if (!file) {
			cerr << fileName << "file not found!" << endl << "Thank you for using " << programTitle << "directory";
			return;
		}

		do {
			cout << "Enter a partial name to search (no spaces) or enter '!' to exit\n>";
			cin >> userInput;

			if (userInput == '!'){
				cout << "Thank you for using " << programTitle << "directory";
				return;
			}

			search(userInput);

		} while (true);
	}

	Contact search(char token) {
		char search_string = toLower(token);
		return {};
	}
}