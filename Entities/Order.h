#pragma once
#include "Address.h"
#include "../SmartPointers/SharedPtr.hpp"
#include "../Utilities/MyVector.hpp"
#include "../Users/Client.h"
#include "../Users/Driver.h"

using std::cout;
using std::endl;

enum OrderStatus {
	waitingToBeAccepted,
	accepted,
	cancelled,
	waitingPayment,
	completed,
};

class Order {
	Address clientCurrentLocation;
	Address destination;
	size_t passengersCount;
	size_t id = GetNextId(); //make it work when reading orders from file
	OrderStatus status = waitingToBeAccepted;

	size_t minutes = 0;
	double price = 0;

	SharedPtr<Client> client;
	SharedPtr<Driver> driver = nullptr;
	MyVector<SharedPtr<Driver>> declinedBy;

	static size_t nextId;
	static size_t GetNextId();

public:
	Order() = default;
	Order(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount,
		const SharedPtr<Client>& client);

	const Address& GetClientCurrentLocation() const;
	const Address& GetDestination() const;
	size_t GetPassengersCount() const;
	size_t GetId() const;
	OrderStatus GetStatus() const;
	double GetPrice() const;
	SharedPtr<Client>& GetClient();
	SharedPtr<Driver>& GetDriver();
	const MyVector<SharedPtr<Driver>>& GetDeclinedBy() const;

	void SetDriver(const SharedPtr<Driver>& driver);
	void Accept(size_t minutes);
	void WaitingPayment(double price);
	void Complete();
	void Decline(const SharedPtr<Driver>& driver);
	void Cancel();
	
	void PrintStatus() const;
	void PrintDataDriverView() const;
	void PrintDataClientView() const;
	void PrintData() const;
};