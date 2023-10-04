#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>	
#include "CarInventory.h"

namespace sdds {
	void CarInventory::resetInfo() {
		m_type = nullptr;
		m_brand = nullptr;
		m_model = nullptr;
		m_year = NULL;
		m_code = NULL;
		m_price = NULL;
	}

	CarInventory::CarInventory() {
		resetInfo();
	}

	CarInventory::CarInventory(const char* type, const char* brand, const char* model, int year, int code, double price) {
		resetInfo();

		m_type = new char[sizeof(type)];
		m_brand = new char[sizeof(brand)];
		m_model = new char[sizeof(model)];

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

	void CarInventory::printInfo() const { //TODO: Make this print all nicely. Right now it just needs to get the information out.
		std::cout << m_type << " " << m_brand << " " << m_model << " " << m_year << " " << " " << m_code << " " << std::setprecision(2) << m_price << std::endl;;
	}

	CarInventory& CarInventory::setInfo(const char* type, const char* brand, const char* model, int year, int code, double price) {
		resetInfo();

		m_type = new char[sizeof(type)];
		m_brand = new char[sizeof(brand)];
		m_model = new char[sizeof(model)];

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
		return car.m_type == m_type && car.m_brand == m_brand && car.m_model == m_model;
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