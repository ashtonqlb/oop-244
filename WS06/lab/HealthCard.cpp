/* ------------------------------------------------------
No stealsies! I love Academic Integrity so much and I have as much integrity as a rock!

Workshop 6 part 1
Name: Ashton Lunken
Student Num: 134128214
Section: NBB
Email: abennet@myseneca.ca
Date: 03/11/2023
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>

#include "HealthCard.h"

namespace sdds {

    bool HealthCard::validID(const char* name, long long number, const char vCode[], const char sNumber[]) const {
        return (name != nullptr       &&
                strlen(name) > 0         &&
                number > HEALTH_CARD_MIN &&
                number < HEALTH_CARD_MAX &&
                strlen(vCode) == 2       &&
                strlen(sNumber) == 9);
    }

    void HealthCard::setEmpty() {
        delete[] m_name;
        m_name = nullptr;
        m_number = 0;
        m_vCode[0] = '\0';
        m_sNumber[0] = '\0';
    }

    void HealthCard::allocateAndCopy(const char* name) {
        if (name) {
            delete[] m_name;
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
        }
    }

    void HealthCard::extractChar(std::istream& istr, char ch) const {
        if (!istr.fail()) {
            char next_char = istr.peek();
            if (next_char == ch) istr.ignore();
            else {
                istr.ignore(1000, ch);
                istr.setstate(std::ios::failbit);
            }
        }
    }

    std::ostream& HealthCard::printIDInfo(std::ostream& ostr) const {
        ostr << m_number << "-" << m_vCode << ", " << m_sNumber;
        return ostr;
    }

    void HealthCard::set(const char* name, long long number, const char vCode[], const char sNumber[]) {
        if (validID(name, number, vCode, sNumber)) {
            allocateAndCopy(name);
            m_number = number;
            strcpy(m_vCode, vCode);
            strcpy(m_sNumber, sNumber);
        }
        else {
            setEmpty();
        }
    }

    HealthCard::HealthCard() {
        setEmpty();
    }

    HealthCard::HealthCard(const char* name, long long number, const char vCode[], const char sNumber[]) {
        set(name, number, vCode, sNumber);
    }

    HealthCard::HealthCard(const HealthCard& hc) {
        if (validID(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber)) {
            set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
        }
        else {
            setEmpty();
        }
    }

    HealthCard& HealthCard::operator=(const HealthCard& hc) {
        if (this != &hc) {
            if (hc) {
                set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
            }
            else {
                setEmpty();
            }
        }
        return *this;
    }

    HealthCard::~HealthCard() {
        delete[] m_name;
    }

    HealthCard::operator bool() const {
        return !(m_name == nullptr);
    }

    std::ostream& HealthCard::print(std::ostream& ostr, bool toFile) const {
        if (*this) {
            if (toFile) {
                ostr << m_name << "," << m_number << "-" << m_vCode << ", " << m_sNumber << std::endl; // Add newline for each record
            }
            else {
                ostr << std::left << std::setw(50) << std::setfill('.') << m_name;
                printIDInfo(ostr);
            }
        }
        return ostr;
    }

    std::istream& HealthCard::read(std::istream& istr) {
        char name[MAX_NAME_LENGTH + 1];
        long long number;
        char vCode[3], sNumber[10];

        istr.get(name, MAX_NAME_LENGTH + 1, ',');
        extractChar(istr, ',');

        istr >> number;
        extractChar(istr, '-');

        istr.get(vCode, 3, ',');
        extractChar(istr, ',');

        istr.get(sNumber, 10, '\n');

        if (istr) {
            set(name, number, vCode, sNumber);
        }

        istr.clear();
        istr.ignore(1000, '\n');

        return istr;
    }

    std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc) {
        if (hc) {
            hc.print(ostr, false);
        }
        else {
            ostr << "Invalid Health Card Record";
        }
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, HealthCard& hc) {
        return hc.read(istr);
    }
} 