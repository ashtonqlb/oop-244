#ifndef SDDS_HEALTHCARD_H
#define SDDS_HEALTHCARD_H

#define MAX_NAME_LENGTH 55

#include <iostream>

namespace sdds {
    class HealthCard {
        char* m_name{};
        long long m_number;
        char m_vCode[3];
        char m_sNumber[10];
       
        //Private methods
        bool validID(const char* name, long long number, const char vCode[], const char sNumber[]) const;
        void setEmpty();
        void allocateAndCopy(const char* name);
        void HealthCard::extractChar(std::istream& istr, char ch) const;
        std::ostream& printIDInfo(std::ostream& ostr)const;
        void set(const char* name, long long number, const char vCode[], const char sNumber[]);
        
        //Rule of three
        HealthCard(const HealthCard& hc);
        HealthCard& operator=(const HealthCard& hc);
        ~HealthCard();

    public:
        operator bool();
        std::ostream& print(std::ostream& ostr, bool toFile = true) const;
        std::istream& read(std::istream& istr);
        friend std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc);
        friend std::istream& operator>>(std::istream& istr, HealthCard& hc);
    };
}
#endif // !SDDS_HealthCard_H