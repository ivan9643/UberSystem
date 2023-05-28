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
	MyVector<Client> clients;
	MyVector<Driver> drivers;
	MyVector<Order> orders;
	User* loggedUser;
	UserType loggedUserType = UserType::none;
	// check if it is needed to save completed orders


	int IndexByUsername(const MyString& username, UserType& type) const;
	bool UsernameInUse(const MyString& username) const;

	void ReadGeneralUserData(MyString& username, MyString& password, MyString& firstName, MyString& lastName) const;
	void ReadAdditionalDriverData(MyString& carNumber, MyString& phoneNumber, MyString& addressName, int& x, int& y) const;

	void AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName,
		const MyString& lastName, const MyString& carNumber = MyString(), const MyString& phoneNumber = MyString(), 
		const MyString& addressName = MyString(), int x = 0, int y = 0);

	void WelcomeUser() const;

	void LoggedInClient();
	void LoggedInDriver();

	void PrintLoggedUserData() const;
public:
	UberSystem();

	UberSystem(const UberSystem&) = delete;
	void operator=(const UberSystem&) = delete;

	void NotLoggedIn();
	
	void SaveDataInFile() const;
	void ReadDataFromFile();

	//~UberSystem(); //save data
};