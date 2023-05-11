#pragma once
#include "Driver.h"

struct Order {
	static size_t nextId;
	Address currentLocation;
	Address destination;
	size_t passengersCount = 0;
	size_t id;
	Driver* driver = nullptr;
	bool isAccepted = false;

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};