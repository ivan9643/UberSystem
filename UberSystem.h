#pragma once
#include "Client.h"
#include "Driver.h"
#include "Order.h"
#include "Vector.h"

const char DATA_FILE_NAME[] = "data.txt";

enum class UserType {
	client,
	driver,
	none,
};

class UberSystem {
	Vector<Client> clients;
	Vector<Driver> drivers;
	Vector<Order> orders;
	// check if it is needed to save completed orders

	int IndexByUsername(const String& username, UserType& type) const;
	void CheckIfUsernameInUse(const String& username) const;
public:
	UberSystem();

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;

	void NotLoggedIn();
	
	void SaveDataInFile() const;
	void ReadDataFromFile();
};