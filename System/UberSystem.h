#pragma once
#include "../Users/Client.h"
#include "../Users/Driver.h"
#include "../Entities/Order.h"
#include "../Utilities/MyVector.hpp"

enum class UserType {
	client,
	driver,
	none,
};

class UberSystem {
	MyVector<SharedPtr<Client>> clients;
	MyVector<SharedPtr<Driver>> drivers;
	MyVector<SharedPtr<Order>> pendingOrders;
	MyVector<SharedPtr<Order>> cancelledOrders;
	MyVector<SharedPtr<Order>> completedOrders;
	SharedPtr<Client> loggedClient;
	SharedPtr<Driver> loggedDriver;
	UserType loggedUserType = UserType::none;

	int IndexByUsername(const MyString& username, UserType& type) const;
	bool UsernameInUse(const MyString& username) const;

	void ReadGeneralUserData(MyString& username, MyString& password, MyString& firstName, MyString& lastName) const;
	void ReadAdditionalDriverData(MyString& carNumber, size_t& carPassengersCountCapacity, MyString& phoneNumber,
		MyString& addressName, int& x, int& y) const;
	void ReadAddressData(const MyString& prompt, MyString& addressName, int& x, int& y) const;
	void ReadAddressDataWithDetails(const MyString& prompt, MyString& addressName, int& x, int& y, MyString& details) const;
	void AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName,
		const MyString& lastName, const MyString& carNumber = MyString(), size_t carPassengersCountCapacity = 0, 
		const MyString& phoneNumber = MyString(), const MyString& addressName = MyString(), int x = 0, int y = 0);

	void Register();
	void Login();
	void Logout();
	void CheckForLoggedUser() const;
	void CheckForLoggedClient() const;
	void CheckForLoggedDriver() const;

	void LoggedInClient();
	void ClientAddMoney();
	void ClientMakeOrder();
	void ClientCheckOrders() const;
	void ClientCancelOrder();
	void ClientPayOrder();
	void ClientRateDriver();

	void MakeOrder(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount);
	void SetNearestDriver(SharedPtr<Order>& order);
	void ClientPrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const;

	void LoggedInDriver();
	void DriverChangeCurrentLocation();
	void DriverCheckOrders() const;
	void DriverAcceptOrder();
	void DriverFinishOrder();
	void DriverDeclineOrder();

	void DriverPrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const;

	void ViewUsers() const;
	void ViewOrders() const;
	void PrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const;
	void ViewTotalMoney() const;
public:
	UberSystem() = default;

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;

	void NotLoggedIn();
};