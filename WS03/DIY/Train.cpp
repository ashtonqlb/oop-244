#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Train.h"

using namespace sdds;

void Train::initialize() {
	if (m_name != nullptr) {
			delete[] m_name;
			m_name = nullptr;
	}

	m_passengers = 0;
	m_departure_time = 0;
}

bool Train::validTime(int value) const {
    if (value >= MIN_TIME && value <= MAX_TIME) {
        int minutes = value % 100;

        return (minutes <= 59);
    }
	return false;
}


bool Train::validNoOfPassengers(int value) const {
	bool ok = false;

	if (value >= 0 && value <= MAX_NO_OF_PASSENGERS) {
		ok = true;
	}

	return ok;
}

bool Train::isInvalid() const {
	return (m_name == nullptr || m_name[0] == '\0' || m_passengers <= 0 || m_departure_time <= 0);
}

void Train::set(const char* name) {
	delete[] m_name;
	m_name = nullptr;

	if (name != nullptr && name[0] != '\0') {
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

void Train::set(int passengers, int departure_time) {
	if (validNoOfPassengers(passengers)) {
		m_passengers = passengers;
	}
	else m_passengers = -1;
	

	if (validTime(departure_time)) {
		m_departure_time = departure_time;
	}
	else m_departure_time = -1;
}

void Train::set(const char* name, int passengers, int departure_time) {
	set(name);
	set(passengers, departure_time);
}

void Train::finalize() {
	delete[] m_name;
	m_name = nullptr;
}

int Train::noOfPassengers() const {
	return m_passengers;
}

int Train::getDepartureTime() const {
	return m_departure_time;
}

const char* Train::getName() const {
	return m_name;
}

void Train::display() const {
	if (!isInvalid()){
		std::cout << "NAME OF THE TRAIN:    "     << getName()          << std::endl
	              << "NUMBER OF PASSENGERS: " << noOfPassengers()   << std::endl
                  << "DEPARTURE TIME:       " << getDepartureTime() << std::endl;
	}
	else std::cout << "Train in an invalid State!" << std::endl;
}

bool Train::load(int& unboarded_passengers) { // All I have to do is rewrite this single function so that if the reference argument has a value, pass it in, else use my existing logic. That's all.
	std::cout << "Enter number of passengers boarding:\n> ";
	int value {};

	if (std::cin >> value) {

		if (value > 0 && value + m_passengers < MAX_NO_OF_PASSENGERS) {
			m_passengers += value;
			unboarded_passengers = 0;
			return true;
		}
		else {
			unboarded_passengers = (value + m_passengers) - MAX_NO_OF_PASSENGERS;
			m_passengers = MAX_NO_OF_PASSENGERS;
			return false;
		}
	}
	return false;
}

bool Train::updateDepartureTime() {
	std::cout << "Enter new departure time:\n> ";

	if (std::cin >> m_departure_time) {
		if (validTime(m_departure_time)) {
			return true;
		}
		m_departure_time = -1;
	}

	return false;
}

bool Train::transfer(const Train& otherTrain) {
	int unboardedPassengers{};

	if (isInvalid() || otherTrain.isInvalid()) {
		return false;
	}

	const size_t combinedNameLength = strlen(m_name) + strlen(", ") + strlen(otherTrain.m_name) + 1;

	char* combinedName = new char[combinedNameLength];

	strcpy(combinedName, m_name);
	strcat(combinedName, ", ");
	strcat(combinedName, otherTrain.m_name);

	unboardedPassengers = otherTrain.noOfPassengers();

	set(combinedName);
	delete[] combinedName;

	if (transferPassengers(unboardedPassengers)) {
		return true;
	}

	std::cout << "Train is full; " << unboardedPassengers << " passengers of " << otherTrain.m_name << " could not be boarded!" << std::endl;
	return true;
}

bool Train::transferPassengers(int& passengers_to_transfer) {
	const int value = passengers_to_transfer;

	if (validNoOfPassengers(value)) {

		if (value > 0 && value + m_passengers < MAX_NO_OF_PASSENGERS) {
			m_passengers += value;
			passengers_to_transfer = 0;
			return true;
		}
		else {
			passengers_to_transfer = (value + m_passengers) - MAX_NO_OF_PASSENGERS;
			m_passengers = MAX_NO_OF_PASSENGERS;
			return false;
		}
	}
	return false;
}