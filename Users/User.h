#pragma once
#include <fstream>
#include "../Utilities/MyString.h"

enum class Property {
	username,
	password,
};

const size_t MIN_LENGTH = 3;
const size_t MAX_LENGTH = 25; 
//used for username, password, first and last name

class User {
protected:
	MyString username;
	MyString firstName;
	MyString lastName;
	size_t passHash = 0;
	double money = 0;
	size_t userId; //make this
	size_t completedOrders; //count completed orders

	void SetPassHash(const MyString& password);

	bool IsUsernameOrPasswordValid(const MyString& username, Property property) const;
	bool IsNameValid(const MyString& name) const;

public:
	User() = default;
	User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money);

	const MyString& GetUsername() const;
	const MyString& GetFirstName() const;
	const MyString& GetLastName() const;
	size_t GetPassHash() const;
	double GetMoney() const;

	void SetUsername(const MyString& username);
	void SetFirstName(const MyString& firstName);
	void SetLastName(const MyString& lastName);
	void SetMoney(double money);

	virtual void PrintData() const;

	virtual void SaveToFile(std::ofstream& file) const;
	virtual void ReadFromFile(std::ifstream& file);
};