#pragma once
#include "../Users/Client.h"
#include "Address.h"

class Driver;

struct Order {
	static size_t nextId;
	Address currentLocation;
	Address destination;
	size_t passengersCount = 0;
	size_t id = GetNextId(); //make it work when reading orders from file
	Client* client = nullptr;
	Driver* driver = nullptr;
	bool isAccepted = false;
	
	static size_t GetNextId();

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};