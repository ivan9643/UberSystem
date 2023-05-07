#pragma once
#include "User.h"
#include "Address.h"

const size_t MIN_CAR_NUMBER_LENGTH = 3;
const size_t MAX_CAR_NUMBER_LENGTH = 10;
const size_t PHONE_NUMBER_LENGTH = 10;

class Driver :User {
	String carNumber;
	String phoneNumber;
	Address currentLocation;

	bool IsCarNumberValid(const String& carNumber);
	bool IsPhoneNumberValid(const String& phoneNumber);

public:
	const String& GetCarNumber() const;
	const String& GetPhoneNumber() const;

	void SaveToFile(std::ofstream& file);
	void ReadFromFile(std::ifstream& file);

	void SetCarNumber(const String& carNumber);
	void SetPhoneNumber(const String& phoneNumber);

	Driver(const String& username, const String& password, const String& firstName,
		const String& lastName, const String& carNumber, const String& phoneNumber, double money);
};