#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include "CarInventory.h"

namespace sdds {
	void CarInventory::resetInfo() {
		m_type = nullptr;
		m_brand = nullptr;
		m_model = nullptr;
		m_year = 0;
		m_code = 0;
		m_price = 0;
	}

	CarInventory::CarInventory() {
		resetInfo();
	}

	CarInventory::CarInventory(const char* type, const char* brand, const char* model, int year, int code, double price) {
		resetInfo();
		
		m_type  = new char[strlen(type) + 1];
		m_brand = new char[strlen(brand) + 1];
		m_model = new char[strlen(model) + 1];

		strcpy(m_type, type);
		strcpy(m_brand, brand);
		strcpy(m_model, model);
		m_year = year;
		m_code = code;
		m_price = price;
	}

	CarInventory::~CarInventory() {
		delete[] m_type;
		delete[] m_brand;
		delete[] m_model;
	}

	void CarInventory::printInfo() const {
	    std::cout << "| "<<   std::left  << std::setw(10) << m_type
	              << " | "<<  std::left  << std::setw(16) << m_brand
	              << " | "<<  std::left  << std::setw(16) << m_model
	              << " | "<<  std::right << std::setw(4)  << m_year
	              << " | "<<  std::right << std::setw(4)  << m_code
	              << " | "<<  std::fixed << std::setprecision(2) << std::right << std::setw(9) << m_price
	              << " |" <<  std::endl;
	}

	CarInventory& CarInventory::setInfo(const char* type, const char* brand, const char* model, int year, int code, double price) {\
		delete[] m_type;
		delete[] m_brand;
		delete[] m_model;

		resetInfo();
		
		m_type  = new char[strlen(type) + 1];
		m_brand = new char[strlen(brand) + 1];
		m_model = new char[strlen(model) + 1];

		strcpy(m_type, type);
		strcpy(m_brand, brand);
		strcpy(m_model, model);
		m_year = year;
		m_code = code;
		m_price = price;
		
		return *this;
	}

	bool CarInventory::isValid() const {
		return m_type && m_brand && m_model && m_year >= 1990 && m_code > 99 && m_price > 0;
	}

	bool CarInventory::isSimilarTo(const CarInventory& car) const {
		if (isValid()){
			return !strcmp(m_brand, car.m_brand) && !strcmp(m_model, car.m_model) && m_year == car.m_year;
		}
		return false;
	}
	
	int find_similar(CarInventory car[], const int num_cars) {
		for (int i = 0; i < num_cars; i++) {
			for (int j = i+1; j < num_cars; j++) {
				if (car[i].isSimilarTo(car[j])) {
					return i;
				}
			}
		}
		return -1;
	}

	
}