/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
   Ashton Lunken        03/11/2023      I dunno I just felt like it I guess.
***********************************************************************/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include "Item.h"

constexpr auto INITIAL_BUFFER_SIZE = 360;

namespace sdds {
   const int sdds_testYear = 2023;
   const int sdds_testMon = 12;
   const int sdds_testDay = 9;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);

      void alocpy(char*& destination, const char* source);

      int get_int(const char* prompt = "\0");
      int get_int(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      int get_int(std::istream& file);

      double get_double(const char* prompt = "\0");
      double get_double(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);

   	  char* get_cstring(std::istream& input, const char* errMes = nullptr, char delimiter = '\n');
      char* get_cstring(const char* prompt = "\0", const char* errMes = nullptr, char delimiter = '\n');
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
