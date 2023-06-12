#pragma once
#include <fstream>
#include "User.h"
#include "../Entities/Address.h"
#include "../Utilities/MyVector.hpp"
#include "../SmartPointers/SharedPtr.hpp"

class Order;

const size_t MIN_CAR_NUMBER_LENGTH = 3;
const size_t MAX_CAR_NUMBER_LENGTH = 10;
const size_t PHONE_NUMBER_LENGTH = 10;

struct Rating {
	double value = 0;
	size_t votesCount = 0;
	
	void AddVote(double value);
};

class Driver : public User {
	MyString carNumber;
	MyString phoneNumber;
	Address currentLocation;
	Rating rating; //getter for rating
	size_t carPassengersCountCapacity;
	MyVector<SharedPtr<Order>> completedOrders; //make functions for orders ...
	MyVector<SharedPtr<Order>> pendingOrders; //make functions for orders ...

	bool IsCarNumberValid(const MyString& carNumber);
	bool IsPhoneNumberValid(const MyString& phoneNumber);

public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password, const MyString& firstName,
		const MyString& lastName, double money, const MyString& carNumber, size_t carPassengersCountCapacity, const MyString& phoneNumber,
		const Address& currentLocation);

	const MyString& GetCarNumber() const;
	const MyString& GetPhoneNumber() const;
	const Address& GetCurrentLocation() const;
	size_t GetCarPassengersCountCapacity() const;
	const MyVector<SharedPtr<Order>>& GetPendingOrders() const;

	void SetCarNumber(const MyString& carNumber);
	void SetPhoneNumber(const MyString& phoneNumber);
	void SetCurrentLocation(const Address& currentLocation);
	void SetCarPassengersCountCapacity(size_t carPassengersCountCapacity);
	void AddOrder(SharedPtr<Order>& order);

	void PrintData() const override;
	void Rate(double value);

	void SaveToFile(std::ofstream& file) const override;
	void ReadFromFile(std::ifstream& file) override;
};