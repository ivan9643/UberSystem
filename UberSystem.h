#pragma once
#include "Client.h"
#include "Driver.h"
#include "Order.h"

const char DATA_FILE_NAME[] = "data.txt";

class UberSystem {
	Client* clients= nullptr;
	Driver* drivers = nullptr;
	Order* orders = nullptr;
	// check if it is needed to save completed orders
	size_t clientsCount = 0;
	size_t driversCount = 0;
	size_t ordersCount = 0;

	void Free();
	
public:
	UberSystem();

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;
	
	void SaveDataInFile();
	void ReadDataFromFile();

	~UberSystem();
};