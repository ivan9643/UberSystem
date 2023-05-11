#pragma once
#include <fstream>
#include "User.h"
#include "Address.h"
#include "Vector.h"

struct Order;

const size_t MIN_CAR_NUMBER_LENGTH = 3;
const size_t MAX_CAR_NUMBER_LENGTH = 10;
const size_t PHONE_NUMBER_LENGTH = 10;

struct Rating {
	double value = 0;
	size_t votesCount = 0;
	
	void AddVote(double value);
};

class Driver : public User {
	String carNumber;
	String phoneNumber;
	Address currentLocation;
	Rating rating;
	Vector<Order*> pendingOrders; //make functions for orders ...

	bool IsCarNumberValid(const String& carNumber);
	bool IsPhoneNumberValid(const String& phoneNumber);

public:
	Driver() = default;
	Driver(const String& username, const String& password, const String& firstName,
		const String& lastName, double money, const String& carNumber, const String& phoneNumber,
		const Address& currentLocation);

	const String& GetCarNumber() const;
	const String& GetPhoneNumber() const;
	const Address& GetCurrentLocation() const;

	void SetCarNumber(const String& carNumber);
	void SetPhoneNumber(const String& phoneNumber);
	void SetCurrentLocation(const Address& currentLocation);

	void Rate(double value);

	void SaveToFile(std::ofstream& file) const override;
	void ReadFromFile(std::ifstream& file) override;
};