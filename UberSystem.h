#pragma once
#include "Client.h"
#include "Driver.h"
#include "Order.h"
#include "Vector.h"

const char DATA_FILE_NAME[] = "data.txt";

class UberSystem {
	Vector<Client> clients;
	Vector<Driver> drivers;
	Vector<Order> orders;
	// check if it is needed to save completed orders

public:
	UberSystem();

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;
	
	void SaveDataInFile();
	void ReadDataFromFile();
};