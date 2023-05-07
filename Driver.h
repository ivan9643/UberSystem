#pragma once
#include "User.h"
#include "Address.h"

class Driver :User {
	String carNumber;
	String phoneNumber;
	Address currentLocation;

public:
	const String& GetCarNumber() const;
	const String& GetPhoneNumber() const;

	void SaveToFile(std::ofstream& file);

	void SetCarNumber(const String& carNumber);
	void SetPhoneNumber(const String& phoneNumber);

	Driver(const String& username, const String& password, const String& firstName, const String& lastName, const String& carNumber, const String& phoneNumber);
};