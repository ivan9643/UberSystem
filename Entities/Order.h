#pragma once
#include "../Users/Client.h"
#include "Address.h"
#include "../SmartPointers/SharedPtr.hpp"
#include "../Utilities/MyVector.hpp"

class Driver;

enum OrderStatus {
	waiting,
	accepted,
	canceled,
	finished,
};

class Order {
	static size_t nextId;

	Address clientCurrentLocation;
	Address destination;
	size_t passengersCount = 0;
	size_t id = GetNextId(); //make it work when reading orders from file
	SharedPtr<Client> client = nullptr;
	SharedPtr<Driver> driver = nullptr;
	OrderStatus status = waiting;
	MyVector<SharedPtr<Driver>> declinedBy;

	static size_t GetNextId();

public:
	//Order();
	Order(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount,
		const SharedPtr<Client>& client);

	const Address& GetClientCurrentLocation() const;
	const Address& GetDestination() const;
	size_t GetPassengersCount() const;
	size_t GetId() const;
	const MyVector<SharedPtr<Driver>> GetDeclinedBy() const;

	void SetDriver(const SharedPtr<Driver>& driver);
	
	void PrintData() const;

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};