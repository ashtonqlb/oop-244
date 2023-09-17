#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Phone.h"

using namespace std;

namespace sdds {

    void phoneDir(const char* programTitle, const char* fileName) {
        ifstream infile(fileName);

        const char* exitMessage = "Thank you for using Star Wars directory"; //make this dynamic later

        cout << programTitle << " phone direcotry search\n-------------------------------------------------------\n";
        
        //If the file is empty, throw an error
        if (!infile) {
            cerr << fileName << " file not found!\n" << exitMessage << endl;
            return;
        }

        while (true) {
            char userInput[128];

            cout << "Enter a partial name to search (no spaces) or enter '!' to exit\n> ";
            cin >> userInput;

            if (userInput[0] == '!') {
                cout << exitMessage;
                break;
            }

            // Search for the query in each line of the file
            bool found = false;

            while (infile) {
                char line[100];
                infile.getline(line, 100);
            	const char* search = strstr(line, userInput); //this only takes in 1 char, not a string (char array)
                if (search != nullptr) {
                    found = true;
                }
            }

            if (!found) {
                cout << "No matches found." << endl;
            }

            // Reset the file pointer to the beginning of the file
            infile.clear();
            infile.seekg(0, ios::beg);
        }
        infile.close();
        return;
    }
}
