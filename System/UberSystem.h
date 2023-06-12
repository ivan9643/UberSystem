#pragma once
#include "../Users/Client.h"
#include "../Users/Driver.h"
#include "../Entities/Order.h"
#include "../Utilities/MyVector.hpp"

const char DATA_FILE_NAME[] = "data.txt";

enum class UserType {
	client,
	driver,
	none,
};

class UberSystem {
	MyVector<SharedPtr<Client>> clients;
	MyVector<SharedPtr<Driver>> drivers;
	MyVector<SharedPtr<Order>> completedOrders;
	MyVector<SharedPtr<Order>> pendingOrders;
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
	void ClientOrder();

	void MakeOrder(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount);
	void SetNearestDriver(SharedPtr<Order>& order);

	void LoggedInDriver();
	void DriverChangeCurrentLocation();
	void DriverCheckPendingOrders();
public:
	UberSystem();

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;

	void NotLoggedIn();
	
	//check if these work after changing the vectors to store pointers
	void SaveDataInFile() const;
	void ReadDataFromFile();

	//~UberSystem(); //save data
};